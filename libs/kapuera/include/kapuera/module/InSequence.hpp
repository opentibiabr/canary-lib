#pragma once
#include <memory>

#include <kapuera/interfaces/IModule.hpp>
#include <kapuera/interfaces/ICombatEngine.hpp>

namespace Kapuera::Module {
    class InSequence final : public IModule, public ICombatEngine {
        std::vector<std::unique_ptr<IModule>> modules;
        using MethodPtr = ModuleResult (IModule::*)(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out);
        ModuleResult dispatch(MethodPtr method, const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) const;

    public:
        explicit InSequence(std::vector<std::unique_ptr<IModule>> modules)
            : modules(std::move(modules)) {}

        ModuleResult prepare(const CombatContext&, ExecutionContext&, CombatOutcome&) override;
        ModuleResult calculate(const CombatContext&, ExecutionContext&, CombatOutcome&) override;
        ModuleResult finalize(const CombatContext&, ExecutionContext&, CombatOutcome&) override;

        [[nodiscard]] CombatOutcome process(const CombatContext &ctx) override;

        template <typename... Mods>
        static InSequence of(Mods&&... mods) {
            std::vector<std::unique_ptr<IModule>> vec;
            (vec.push_back(std::make_unique<std::decay_t<Mods>>(std::forward<Mods>(mods))), ...);
            return InSequence(std::move(vec));
        }
    };
}

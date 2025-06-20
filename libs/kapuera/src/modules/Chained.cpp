#include <kapuera/modules/Chained.hpp>

namespace Kapuera {
    ModuleResult Chained::prepare(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) {
        return dispatch(&IModule::prepare, ctx, exec, out);
    }

    ModuleResult Chained::calculate(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) {
        return dispatch(&IModule::calculate, ctx, exec, out);
    }

    ModuleResult Chained::finalize(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) #pragma once
#include <memory>

#include <kapuera/interfaces/IModule.hpp>

#include "kapuera/interfaces/ICombatEngine.hpp"

namespace Kapuera {
    class Chained final : public IModule, public ICombatEngine {
        std::vector<std::unique_ptr<IModule>> modules;
        using MethodPtr = ModuleResult (IModule::*)(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out);
        ModuleResult dispatch(MethodPtr method, const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) const;

    public:
        explicit Chained(std::vector<std::unique_ptr<IModule>> modules)
            : modules(std::move(modules)) {}

        ModuleResult prepare(const CombatContext&, ExecutionContext&, CombatOutcome&) override;
        ModuleResult calculate(const CombatContext&, ExecutionContext&, CombatOutcome&) override;
        ModuleResult finalize(const CombatContext&, ExecutionContext&, CombatOutcome&) override;

        [[nodiscard]] CombatOutcome process(const CombatContext &ctx) override;

        template <typename... Mods>
        static Chained withModules(Mods&&... mods) {
            std::vector<std::unique_ptr<IModule>> vec;
            (vec.push_back(std::make_unique<std::decay_t<Mods>>(std::forward<Mods>(mods))), ...);
            return Chained(std::move(vec));
        }
    };
}
{
        return dispatch(&IModule::finalize, ctx, exec, out);
    }

    CombatOutcome Chained::process(const CombatContext& ctx) {
        ExecutionContext exec;
        CombatOutcome out;

        if (prepare(ctx, exec, out) == ModuleResult::Interrupt) {
            return out;
        }

        if (calculate(ctx, exec, out) == ModuleResult::Interrupt) {
            return out;
        }

        finalize(ctx, exec, out);
        return out;
    }

    ModuleResult Chained::dispatch(MethodPtr method, const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) const {
        for (const auto& module : modules) {
            if ((module.get()->*method)(ctx, exec, out) == ModuleResult::Interrupt) {
                return ModuleResult::Interrupt;
            }
        }

        return ModuleResult::Continue;
    }
}
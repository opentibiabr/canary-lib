#include <kapuera/module/InSequence.hpp>

namespace Kapuera::Module {
    ModuleResult InSequence::prepare(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) {
        return dispatch(&IModule::prepare, ctx, exec, out);
    }

    ModuleResult InSequence::calculate(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) {
        return dispatch(&IModule::calculate, ctx, exec, out);
    }

    ModuleResult InSequence::finalize(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) {
        return dispatch(&IModule::finalize, ctx, exec, out);
    }

    CombatOutcome InSequence::process(const CombatContext& ctx) {
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

    ModuleResult InSequence::dispatch(MethodPtr method, const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) const {
        for (const auto& module : modules) {
            if ((module.get()->*method)(ctx, exec, out) == ModuleResult::Interrupt) {
                return ModuleResult::Interrupt;
            }
        }

        return ModuleResult::Continue;
    }
}
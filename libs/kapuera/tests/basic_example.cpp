#include <catch.hpp>

#include <iostream>
#include <kapuera.hpp>
#include <kapuera/tibia.hpp>

using namespace Kapuera;

class ManaCheckModule final : public IModule {
public:
    ModuleResult prepare(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome&) override {
        auto ml = ctx.actor.getOr<uint32_t>(Tibia::Actor::KEY_MAGIC_LEVEL, 0);
        if (ml < 10) {
            exec.log("Not enough magic level.");
            return ModuleResult::Interrupt;
        }
        return ModuleResult::Continue;
    }
};

class SimpleDamageModule final : public IModule {
public:
    ModuleResult calculate(const CombatContext& ctx, ExecutionContext& exec, CombatOutcome& out) override {
        const auto base = ctx.trigger.getOr<uint32_t>(Tibia::Trigger::KEY_BASE_DAMAGE, 0);
        const auto type = ctx.trigger.getOr<std::string>(Tibia::Trigger::KEY_COMBAT_TYPE, "physical");
        const auto res = ctx.target.getOr<uint32_t>((std::string("resistance_") + type), 0);
        double dmg = base - (base * res / 100.0);
        out.damageDealt = std::max(40.0, dmg);
        out.type = type;
        return ModuleResult::Continue;
    }
};

class BurnConditionModule final : public IModule {
public:
    ModuleResult calculate(const CombatContext& ctx, ExecutionContext&, CombatOutcome& out) override {
        std::string type = ctx.trigger.getOr<std::string>(Tibia::Trigger::KEY_COMBAT_TYPE, "");
        if (type == "fire" && out.damageDealt > 30) {
            out.flags["burn"] = true;
        }
        return ModuleResult::Continue;
    }
};

class OutputModule final : public IModule {
public:
    ModuleResult finalize(const CombatContext&, ExecutionContext& exec, CombatOutcome& out) override {
        std::cout << "Damage Dealt: " << out.damageDealt << "\n";
        for (const auto& [cond, applied] : out.flags) {
            std::cout << "Applied Condition: " << cond << "\n";
        }
        for (const auto& log : exec.logs) {
            std::cout << "Log: " << log << "\n";
        }
        return ModuleResult::Continue;
    }
};

auto engine = Module::InSequence::of(
    ManaCheckModule(),
    SimpleDamageModule(),
    BurnConditionModule(),
    OutputModule()
);

Tibia::Actor actor(15, 20, 35);
Tibia::Target target(80, 20);
Tibia::Trigger trigger(60.0, "fire", "ml_based");

CombatContext ctx{actor, target, trigger};

TEST_CASE("Single module is executed") {
    auto [damageDealt, type, flags] = engine.process(ctx);

    REQUIRE(damageDealt == 40);
    REQUIRE(type == "fire");
    REQUIRE(flags.size() == 1);
}

TEST_CASE("Kapuera Benchmark") {
    BENCHMARK("Kapuera combat engine stress") {
        return engine.process(ctx);
    };
}

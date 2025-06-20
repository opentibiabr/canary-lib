#pragma once

#include <cstdint>
#include <string>

#include <kapuera/interfaces/ICombatEntity.hpp>

namespace Kapuera::Tibia {
    class Actor : public ICombatEntity {
    public:
        const std::any magicLevel;
        const std::any level;
        const std::any skillSword;

        static constexpr auto KEY_MAGIC_LEVEL = "magic_level";
        static constexpr auto KEY_LEVEL = "level";
        static constexpr auto KEY_SKILL_SWORD = "skill_sword";

        Actor(uint32_t ml, uint32_t lvl, uint32_t sword)
            : magicLevel(ml), level(lvl), skillSword(sword) {}

    protected:
        const std::any* get(const std::string& key) const override {
            if (key == KEY_MAGIC_LEVEL) return &magicLevel;
            if (key == KEY_LEVEL) return &level;
            if (key == KEY_SKILL_SWORD) return &skillSword;

            return nullptr;
        }
    };

    class Target : public ICombatEntity {
    public:
        const std::any health;
        const std::any fireResistance;

        static constexpr auto KEY_HEALTH = "health";
        static constexpr auto KEY_FIRE_RES = "resistance_fire";

        Target(int32_t hp, int fireRes)
            : health(hp), fireResistance(fireRes) {}

    protected:
        const std::any* get(const std::string& key) const override {
            if (key == KEY_HEALTH) return &health;
            if (key == KEY_FIRE_RES) return &fireResistance;
            return nullptr;
        }
    };

    class Trigger : public ICombatEntity {
    public:
        const std::any baseDamage;
        const std::any combatType;
        const std::any formulaType;

        static constexpr auto KEY_BASE_DAMAGE = "base_damage";
        static constexpr auto KEY_COMBAT_TYPE = "combat_type";
        static constexpr auto KEY_FORMULA_TYPE = "formula_type";

        Trigger(double dmg, std::string type, std::string formula)
            : baseDamage(dmg), combatType(std::move(type)), formulaType(std::move(formula)) {}

    protected:
        const std::any* get(const std::string& key) const override {
            if (key == KEY_BASE_DAMAGE) return &baseDamage;
            if (key == KEY_COMBAT_TYPE) return &combatType;
            if (key == KEY_FORMULA_TYPE) return &formulaType;
            return nullptr;
        }
    };
}

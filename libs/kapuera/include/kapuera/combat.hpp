#pragma once
#include <cstdint>
#include <map>
#include <string>

namespace Kapuera {
    std::string hello();

    using CombatType = std::string;
    using ConditionType = std::string;
    using EffectType = std::string;
    using FormulaType = std::string;

    class ICombatActor;
    class ICombatTarget;
    class ICombatTrigger;
    struct CombatContext;
    struct CombatOutcome;

    /**
     * The "Who" - The entity performing the action.
     * Represents any entity that can initiate a combat action.
     */
    class ICombatActor {
    public:
        virtual ~ICombatActor() = default;

        virtual int getHealth() const = 0;
        virtual uint32_t getLevel() const = 0;
        virtual uint32_t getMagicLevel() const = 0;
        virtual uint32_t getSkill(uint8_t skillId) const = 0;
    };


    /**
     * The "Whom" - The entity being targeted.
     * Represents any entity that can be affected by a combat action.
     */
    class ICombatTarget {
    public:
        virtual ~ICombatTarget() = default;

        virtual int32_t getHealth() const = 0;
        virtual int32_t getResistance(const CombatType& type) const = 0;
        virtual bool hasCondition(const ConditionType& type) const = 0;
    };


    /**
     * The "How" - The action that motivates the combat event.
     * Represents the specific ability or action that generates combat.
     */
    class ICombatTrigger {
    public:
        virtual ~ICombatTrigger() = default;

        virtual double getBaseDamage() const = 0;
        virtual CombatType getCombatType() const = 0;
        virtual FormulaType getFormulaType() const = 0;
    };

    struct CombatContext {
        ICombatActor&  actor;
        ICombatTarget& target;
        ICombatTrigger& trigger;
    };

    struct CombatOutcome {
        int damageDealt = 0;
        CombatType type = "Unknown";
        std::map<ConditionType, bool> flags;
    };

    class ICombatEngine {
    public:
        virtual ~ICombatEngine() = default;
        virtual CombatOutcome resolve(const CombatContext& ctx) const = 0;
    };
}

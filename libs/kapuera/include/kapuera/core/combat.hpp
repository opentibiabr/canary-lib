#pragma once
#include <map>
#include <string>

#include <kapuera/interfaces/ICombatEntity.hpp>

namespace Kapuera {
    using CombatType = std::string;
    using ConditionType = std::string;

    struct CombatContext {
        /**
         * The "Who" - The entity performing the action.
         * Represents any entity that can initiate a combat action.
         */
        ICombatEntity&  actor;
        /**
         * The "Whom" - The entity being targeted.
         * Represents any entity that can be affected by a combat action.
         */
        ICombatEntity& target;
        /**
         * The "How" - The action that motivates the combat event.
         * Represents the specific ability or action that generates combat.
         */
        ICombatEntity& trigger;
    };

    struct CombatOutcome {
        int damageDealt = 0;
        CombatType type = "Unknown";
        std::map<ConditionType, bool> flags;
    };
}

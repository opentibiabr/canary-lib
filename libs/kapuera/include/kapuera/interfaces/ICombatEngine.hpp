#pragma once

#include <kapuera/core/combat.hpp>

namespace Kapuera {
    /**
     * Defines the contract for combat engines.
     *
     * The `process` method is currently non-const to allow engines with internal state
     * (e.g. caching, instrumentation). In the future, this may evolve toward
     * a pure, stateless design.
     */
    class ICombatEngine {
    public:
        virtual ~ICombatEngine() = default;
       [[nodiscard]] virtual CombatOutcome process(const CombatContext& ctx) = 0;
    };
}

#pragma once

#include <any>
#include <vector>
#include <unordered_map>

#include <kapuera/core/combat.hpp>

namespace Kapuera {
    class PropertyBag final {
    public:
        template<typename T>
        void set(const std::string& key, T value) {
            data[key] = std::move(value);
        }

        template<typename T>
        T getOr(const std::string& key, T defaultValue) const {
            auto it = data.find(key);

            if (it == data.end()) return defaultValue;

            if (auto casted = std::any_cast<T>(&it->second)) {
                return *casted;
            }

            return defaultValue;
        }

    private:
        std::unordered_map<std::string, std::any> data;
    };

    struct ExecutionContext {
        PropertyBag shared;
        std::vector<std::string> logs;

        void log(const std::string& msg) {
            logs.push_back(msg);
        }
    };

    enum class ModuleResult {
        Continue,
        Interrupt,
    };

    /**
     * Module lifecycle interface.
     *
     * All methods are non-const for now to allow modules to perform
     * contextual setup or cache state inside the CombatContext or engine.
     *
     * In the future, we may refactor this to enforce const correctness
     * and drive a more functional, side-effect-free module pipeline.
     */
    class IModule {
    public:
        virtual ~IModule() = default;
        virtual ModuleResult prepare(const CombatContext&, ExecutionContext&, CombatOutcome&) { return ModuleResult::Continue;}
        virtual ModuleResult calculate(const CombatContext&, ExecutionContext&, CombatOutcome&) { return ModuleResult::Continue; }
        virtual ModuleResult finalize(const CombatContext&, ExecutionContext&, CombatOutcome&) { return ModuleResult::Continue; }
    };
}
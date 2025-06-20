#pragma once

#include <any>

namespace Kapuera {
    /**
     * Generic interface for any combat entity.
     * This interface aims to be flexible enough to represent various entities involved in combat,
     * including actors, targets, and triggers.
     */
    class ICombatEntity {
    public:
        virtual ~ICombatEntity() = default;

    protected:
        [[nodiscard]] virtual const std::any* get(const std::string& key) const = 0;

    public:
        template<typename T>
        T getOr(const std::string& key, const T& defaultValue) const {
            const auto* val = get(key);
            if (!val) return defaultValue;
            auto casted = std::any_cast<T>(val);
            return casted ? *casted : defaultValue;
        }

        [[nodiscard]] bool has(const std::string& key) const {
            return get(key) != nullptr;
        }
    };
}
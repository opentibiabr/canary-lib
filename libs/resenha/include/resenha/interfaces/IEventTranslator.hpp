#pragma once
#include <any>
#include <vector>

namespace Resenha {
    class IEventTranslator {
    public:
        virtual ~IEventTranslator() = default;

        virtual std::vector<std::any> translate(const std::any& gameEvent) const = 0;
    };
}

#pragma once
#include <any>
#include <cstdint>
#include <typeindex>
#include <vector>

namespace Resenha {
    class ICodec {
    public:
        virtual ~ICodec() = default;

        [[nodiscard]] virtual std::vector<uint8_t> encode(const std::any& message) const = 0;
        [[nodiscard]] virtual std::any decode(std::type_index type, const std::vector<uint8_t>& data) const = 0;
    };
}

#pragma once

#include <functional>

#include <resenha/interfaces/ICodec.hpp>

namespace Resenha::Codec {
    class ByTypeMap final : public ICodec {
    public:
        template<typename T>
        void registerType(
            std::function<std::vector<uint8_t>(const T&)> encodeFn,
            std::function<T(const std::vector<uint8_t>&)> decodeFn
        ) {
            const auto key = std::type_index(typeid(T));

            encoders[key] = [encodeFn](const std::any& a) {
                return encodeFn(std::any_cast<const T&>(a));
            };

            decoders[key] = [decodeFn](const std::vector<uint8_t>& data) {
                return std::any(decodeFn(data));
            };
        }

        std::vector<uint8_t> encode(const std::any& message) const override;
        std::any decode(std::type_index type, const std::vector<uint8_t>& data) const override;

    private:
        std::unordered_map<std::type_index, std::function<std::vector<uint8_t>(const std::any&)>> encoders;
        std::unordered_map<std::type_index, std::function<std::any(const std::vector<uint8_t>&)>> decoders;
    };
}

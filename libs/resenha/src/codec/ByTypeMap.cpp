#include <stdexcept>
#include <resenha/codec/ByTypeMap.hpp>

namespace Resenha::Codec {
    std::vector<uint8_t> ByTypeMap::encode(const std::any& message) const {
        const auto key = std::type_index(message.type());
        const auto it = encoders.find(key);

        if (it == encoders.end()) throw std::runtime_error("Unknown type");

        return it->second(message);
    }

    std::any ByTypeMap::decode(const std::type_index type, const std::vector<uint8_t>& data) const {
        const auto it = decoders.find(type);

        if (it == decoders.end()) throw std::runtime_error("Unknown type");

        return it->second(data);
    }
}

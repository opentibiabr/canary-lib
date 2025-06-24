#include <stdexcept>
#include <resenha/codec/WithTranslation.hpp>

namespace Resenha::Codec {
    std::vector<uint8_t> WithTranslation::encode(const std::any& message) const {
        const auto translated = adapter->translate(message);
        std::vector<uint8_t> result;

        for (const auto& evt : translated) {
            auto encoded = codec->encode(evt);
            result.insert(result.end(), encoded.begin(), encoded.end());
        }

        return result;
    }

    std::any WithTranslation::decode(const std::type_index type, const std::vector<uint8_t>& data) const {
            return codec->decode(type, data);
    }
}

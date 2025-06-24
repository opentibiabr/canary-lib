#pragma once

#include <functional>
#include <memory>

#include <resenha/interfaces/ICodec.hpp>
#include <resenha/interfaces/IEventTranslator.hpp>

namespace Resenha::Codec {
    class WithTranslation final : public ICodec {
    public:
        WithTranslation(std::shared_ptr<ICodec> codec, std::shared_ptr<IEventTranslator> adapter)
            : codec(std::move(codec)), adapter(std::move(adapter)) {}

        [[nodiscard]] std::vector<uint8_t> encode(const std::any& message) const override;
        [[nodiscard]] std::any decode(std::type_index type, const std::vector<uint8_t>& data) const override;

    private:
        std::shared_ptr<ICodec> codec;
        std::shared_ptr<IEventTranslator> adapter;
    };
}

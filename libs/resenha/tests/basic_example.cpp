#include <catch.hpp>

#include <iostream>
#include <resenha.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace Resenha;

// === Game Event ===
struct UnitMoved {
    uint32_t unitId;
    uint8_t fromX, fromY;
    uint8_t toX, toY;
};

// === Client Protocol Messages ===
struct CreatureDisappear {
    uint32_t id;
    uint8_t x, y;
};

struct CreatureAppear {
    uint32_t id;
    uint8_t x, y;
    uint8_t outfit = 0x01;
};

class UnitTranslator final : public IEventTranslator {
    [[nodiscard]] std::vector<std::any> translate(const std::any &gameEvent) const override {
        if (gameEvent.type() == typeid(UnitMoved)) {
            const auto&[unitId, fromX, fromY, toX, toY] = std::any_cast<const UnitMoved&>(gameEvent);
            return {
                CreatureDisappear{ unitId, fromX, fromY },
                CreatureAppear{ unitId, toX, toY }
            };
        }

        return {gameEvent};
    }
};


Codec::WithTranslation stubCodec() {
    auto codec = std::make_shared<Codec::ByTypeMap>();
    auto translator = std::make_shared<UnitTranslator>();

    codec->registerType<CreatureDisappear>(
        [](const CreatureDisappear& m) {
            return std::vector<uint8_t>{ 0x6C, m.id >> 24, m.id >> 16, m.id >> 8, m.id, m.x, m.y };
        },
        [](const std::vector<uint8_t>& data) {
            return CreatureDisappear{
                .id = (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4],
                .x = data[5],
                .y = data[6]
            };
        }
    );

    codec->registerType<CreatureAppear>(
        [](const CreatureAppear& m) {
            return std::vector<uint8_t>{ 0x6A, m.id >> 24, m.id >> 16, m.id >> 8, m.id, m.x, m.y, m.outfit };
        },
        [](const std::vector<uint8_t>& data) {
            return CreatureAppear{
                .id = (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4],
                .x = data[5],
                .y = data[6],
                .outfit = data[7]
            };
        }
    );

    return {std::move(codec), std::move(translator)};
}

TEST_CASE("Resenha integration works") {
    UnitMoved event = { 42, 5, 5, 6, 5 };
    auto codec = stubCodec();

    std::vector<uint8_t> payload = codec.encode(event);

    auto anyDisappear = codec.decode(typeid(CreatureDisappear),
        std::vector(payload.begin(), payload.begin() + 7));
    auto anyAppear = codec.decode(typeid(CreatureAppear),
        std::vector(payload.begin() + 7, payload.end()));

    const auto& disappear = std::any_cast<const CreatureDisappear&>(anyDisappear);
    const auto& appear = std::any_cast<const CreatureAppear&>(anyAppear);

    CreatureDisappear expectedDisappear = { 42, 5, 5 };
    CreatureAppear expectedAppear = { 42, 6, 5, 0x01 };

    REQUIRE(disappear.id == expectedDisappear.id);
    REQUIRE(disappear.x == expectedDisappear.x);
    REQUIRE(disappear.y == expectedDisappear.y);

    REQUIRE(appear.id == expectedAppear.id);
    REQUIRE(appear.x == expectedAppear.x);
    REQUIRE(appear.y == expectedAppear.y);
    REQUIRE(appear.outfit == expectedAppear.outfit);
}

TEST_CASE("Resenha Benchmark") {
    UnitMoved event = { 42, 5, 5, 6, 5 };
    const auto codec = stubCodec();

    BENCHMARK("Resenha encode + decode") {
        auto payload = codec.encode(event);
        auto d1 = codec.decode(typeid(CreatureDisappear), {payload.begin(), payload.begin() + 7});
        const auto d2 = codec.decode(typeid(CreatureAppear), {payload.begin() + 7, payload.end()});
        return std::any_cast<CreatureAppear>(d2).x;
    };
}

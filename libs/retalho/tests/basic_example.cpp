#include <catch.hpp>
#include <iostream>
#include <retalho.hpp>

TEST_CASE("Retalho integration works") {
    REQUIRE(Retalho::hello() == "Hello, from Retalho!");
}

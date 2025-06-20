#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <resenha.hpp>

TEST_CASE("Resenha integration works") {
    REQUIRE(Resenha::hello() == "Hello, from Resenha!");
}

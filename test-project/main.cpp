#include <protocol/message.hpp>
#include <kapuera/combat.hpp>
#include <iostream>

int main() {
    std::cout << Kapuera::hello() << std::endl;
    std::cout << protocol::hello() << std::endl;
    return 0;
}

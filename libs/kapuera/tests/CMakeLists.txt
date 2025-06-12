find_package(Catch2 CONFIG REQUIRED)

add_executable(kapuera_tests
        test_main.cpp
        test_damage.cpp
)

target_link_libraries(kapuera_tests
        PRIVATE
        kapuera
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(kapuera_tests)

find_package(Catch2 CONFIG REQUIRED)

add_executable(retalho_tests
        test_main.cpp
        basic_example.cpp
)

target_link_libraries(retalho_tests
        PRIVATE
        retalho
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(retalho_tests)

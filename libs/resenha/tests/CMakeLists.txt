find_package(Catch2 CONFIG REQUIRED)

add_executable(resenha_tests
        test_main.cpp
        basic_example.cpp
)

target_link_libraries(resenha_tests
        PRIVATE
        resenha
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(resenha_tests)

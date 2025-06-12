cmake_minimum_required(VERSION 3.15)
project(test-project)

find_package(protocol CONFIG REQUIRED)
find_package(kapuera CONFIG REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE protocol::protocol kapuera::kapuera)

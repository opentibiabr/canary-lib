cmake_minimum_required(VERSION 3.15)
project(retalho)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/CanaryLib.cmake)

canary_add_library(retalho)

# Only add tests if explicitly requested
option(BUILD_TESTS "Build tests" OFF)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

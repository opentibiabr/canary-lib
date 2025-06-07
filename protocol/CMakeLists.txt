cmake_minimum_required(VERSION 3.15)
project(protocol)

# Automatically gather source and header files
file(GLOB_RECURSE PROTOCOL_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE PROTOCOL_HEADERS CONFIGURE_DEPENDS include/*.hpp)

add_library(protocol ${PROTOCOL_SOURCES})

target_include_directories(protocol
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install header files into include/protocol/
install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
)

# Install library target and its metadata
install(TARGETS protocol
        EXPORT protocolTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# Export CMake package config
install(EXPORT protocolTargets
        FILE protocolTargets.cmake
        NAMESPACE protocol::
        DESTINATION share/protocol
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/protocolConfigVersion.cmake"
        VERSION 1.0.0
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/protocolConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/protocolConfig.cmake"
        INSTALL_DESTINATION share/protocol
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/protocolConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/protocolConfigVersion.cmake"
        DESTINATION share/protocol
)

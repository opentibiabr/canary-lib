# CanaryLibrary.cmake
function(canary_add_library LIB_NAME)
    file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
    file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS include/*.hpp)

    add_library(${LIB_NAME} ${LIB_SOURCES})

    target_include_directories(${LIB_NAME}
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )

    install(
            DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
            DESTINATION include/${LIB_NAME}
            FILES_MATCHING PATTERN "*.hpp"
    )

    install(TARGETS ${LIB_NAME}
            EXPORT ${LIB_NAME}Targets
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
    )

    install(EXPORT ${LIB_NAME}Targets
            FILE ${LIB_NAME}Targets.cmake
            NAMESPACE ${LIB_NAME}::
            DESTINATION share/${LIB_NAME}
    )

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}ConfigVersion.cmake"
            VERSION 1.0.0
            COMPATIBILITY SameMajorVersion
    )

    configure_package_config_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}Config.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
            INSTALL_DESTINATION share/${LIB_NAME}
    )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}ConfigVersion.cmake"
            DESTINATION share/${LIB_NAME}
    )
endfunction()

vcpkg_cmake_configure(
        SOURCE_PATH ${CURRENT_PORT_DIR}/../../protocol
        PREFER_NINJA
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
        PACKAGE_NAME protocol
        CONFIG_PATH share/protocol
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL ${CMAKE_CURRENT_LIST_DIR}/copyright DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT})
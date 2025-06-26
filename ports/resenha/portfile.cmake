vcpkg_from_git(
        OUT_SOURCE_PATH SOURCE_PATH
        URL https://github.com/opentibiabr/canary-lib.git
        REF f29a03131609ca589dae93877dd5ae8bc2e4cb79
        SOURCE_SUBPATH libs/resenha
)


vcpkg_cmake_configure(
        SOURCE_PATH ${SOURCE_PATH}/libs/resenha
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
        PACKAGE_NAME resenha
        CONFIG_PATH share/resenha
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL ${CMAKE_CURRENT_LIST_DIR}/copyright DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT})

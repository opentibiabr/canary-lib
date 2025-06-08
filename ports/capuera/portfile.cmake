vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO opentibiabr/canary-lib
        REF d1a5b400687beb4a500160a647e379e0a6e7c895
        SHA512 cdba654e2d543203151a86fce9cfde17e43150cc0effdcb9e90b4b896072bb9e86c31652ab1bfc967a47d0da5d920ee2afc41a8fd58058bf72cb7b88b10df563
        HEAD_REF main
        SOURCE_SUBPATH libs/capuera
)

vcpkg_cmake_configure(
        SOURCE_PATH ${SOURCE_PATH}/libs/capuera
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
        PACKAGE_NAME capuera
        CONFIG_PATH share/capuera
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL ${CMAKE_CURRENT_LIST_DIR}/copyright DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT})

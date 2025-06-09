vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO opentibiabr/canary-lib
        REF b4ff01f637759dceaf31c35e412469cf4b4da32d
        SHA512 a8e11caa20e31f60999174830664bc702193a9ef0d2dbaa3c1734ece1802d170b111a89d161be1fcad35a2b159227a152e0bb2d196ceb46a0879adf125fb52ec
        HEAD_REF main
        SOURCE_SUBPATH libs/protocol
)

vcpkg_cmake_configure(
        SOURCE_PATH ${SOURCE_PATH}/libs/protocol
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
        PACKAGE_NAME protocol
        CONFIG_PATH share/protocol
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(INSTALL ${CMAKE_CURRENT_LIST_DIR}/copyright DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT})
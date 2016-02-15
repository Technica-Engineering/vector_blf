cmake_minimum_required(VERSION 2.8)

project(Vector_BLF)

# build types: None, Debug, Release, RelWithDebInfo, MinSizeRel
set(CMAKE_BUILD_TYPE Release)

# source code documentation
option(OPTION_RUN_DOXYGEN "Run Doxygen" ON)

# static code analysis
option(OPTION_RUN_CCCC "Run CCCC" OFF)
option(OPTION_RUN_CPPCHECK "Run Cppcheck" OFF)

# dynamic tests
option(OPTION_RUN_EXAMPLES "Run examples" OFF)
option(OPTION_RUN_TESTS "Run tests" OFF)
option(OPTION_USE_GCOV_LCOV "Use gcov and run lcov" OFF)

# directories
include(GNUInstallDirs)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
set(CMAKE_INSTALL_PREFIX /)

# package
set(CPACK_PACKAGE_CONTACT "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_PACKAGE_VENDOR "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_PACKAGE_VERSION 1.0.0)
set(CPACK_VERSION_MAJOR 1)
set(CPACK_VERSION_MINOR 1)
set(CPACK_VERSION_PATCH 1)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.GPL)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_NSIS_CONTACT "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico)
set(CPACK_NSIS_MUI_UNICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico)

include(CTest)
include(CPack)

add_subdirectory(src)

install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/README.md
        ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.GPL
    DESTINATION ${CMAKE_INSTALL_DOCDIR})

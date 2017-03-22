cmake_minimum_required(VERSION 3.0)

project(Vector_BLF VERSION 1.1.0)

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
set(CMAKE_INSTALL_PREFIX /usr)

# dependencies
find_package(ZLIB REQUIRED)
if(OPTION_RUN_TESTS)
    find_package(Boost 1.55 COMPONENTS system filesystem unit_test_framework REQUIRED)
    if(OPTION_USE_GCOV_LCOV)
        find_package(LCOV REQUIRED)
    endif()
endif()

# package
set(CPACK_PACKAGE_CONTACT "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_PACKAGE_VENDOR "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.GPL-3.0)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_NSIS_MUI_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico)
set(CPACK_NSIS_MUI_UNICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico)
set(CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT})
include(CPack)

add_subdirectory(src)

install(
    FILES
        CHANGELOG.md
        LICENSE.GPL-3.0
        README.md
    DESTINATION ${CMAKE_INSTALL_DOCDIR})

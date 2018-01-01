cmake_minimum_required(VERSION 3.9)

project(Vector_BLF
    VERSION 1.2.1
    DESCRIPTION "Vector Binary Log File support library")

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

# dependencies
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
if(OPTION_RUN_DOXYGEN)
    find_package(Doxygen REQUIRED)
    find_package(Graphviz)
    if(WIN32)
        find_package(HTMLHelp REQUIRED)
    endif()
endif()
if(OPTION_RUN_CCCC)
    find_package(CCCC REQUIRED)
endif()
if(OPTION_RUN_CPPCHECK)
    find_package(Cppcheck REQUIRED)
endif()
if(OPTION_RUN_TESTS)
    enable_testing()
    find_package(Boost 1.55 COMPONENTS system filesystem unit_test_framework REQUIRED)
endif()
if(OPTION_USE_GCOV_LCOV)
    find_package(LCOV REQUIRED)
endif()

# package
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT "Tobias Lorenz <tobias.lorenz@gmx.net>")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.GPL-3.0)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
include(CPack)

# install
install(
    FILES
        CHANGELOG.md
        README.md
        LICENSE.GPL-3.0
    DESTINATION ${CMAKE_INSTALL_DOCDIR})

# sub directories
add_subdirectory(src)

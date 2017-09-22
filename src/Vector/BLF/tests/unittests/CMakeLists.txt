# combines: targets, sources/headers, compiler/linker settings, tests
function(add_boost_test test_name exec_name)
    # targets
    add_executable(${exec_name} "")

    # sources/headers
    target_sources(${exec_name} PRIVATE ${ARGN})

    # compiler/linker settings
    target_link_libraries(${exec_name}
        PRIVATE
            ${PROJECT_NAME}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    if(OPTION_USE_GCOV_LCOV)
        target_link_libraries(${exec_name} PRIVATE gcov)
    endif()

    # tests
    add_test(${test_name} COMMAND ${exec_name})
endfunction()

# search paths
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR})
link_directories(
    ${Boost_LIBRARY_DIRS})

# compiler/linker settings
add_definitions(
    -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

# tests
include(CTest)
enable_testing()
add_boost_test(AllEvents test_AllEvents test_AllEvents.cpp)
add_boost_test(AllLogfiles test_AllLogfiles test_AllLogfiles.cpp)
add_boost_test(Events test_Events test_Events.cpp)

# coverage
if(OPTION_USE_GCOV_LCOV)
    add_custom_target(lcov_capture ALL
        COMMAND ${LCOV_EXECUTABLE}
            --capture
            --directory ${PROJECT_BINARY_DIR}
            --output-file coverage.info || true
        DEPENDS
            test_AllEvents
            test_AllLogfiles
            test_Events)

    add_custom_target(lcov_genhtml ALL
        COMMAND ${LCOV_GENHTML_EXECUTABLE}
            coverage.info
            --output-directory lcov || true
        DEPENDS lcov_capture)

    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lcov
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()

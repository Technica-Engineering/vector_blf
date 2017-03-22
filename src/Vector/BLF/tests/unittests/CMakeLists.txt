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

# targets
add_executable(test_AllEvents test_AllEvents.cpp)
add_executable(test_AllLogfiles test_AllLogfiles.cpp)
add_executable(test_Events test_Events.cpp)

target_link_libraries(test_AllEvents
    ${PROJECT_NAME}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(test_AllLogfiles
    ${PROJECT_NAME}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(test_Events
    ${PROJECT_NAME}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# tests
include(CTest)
enable_testing()
add_test(AllEvents test_AllEvents)
add_test(AllLogfile test_AllLogfile)
add_test(Events test_Events)

# coverage
if(OPTION_USE_GCOV_LCOV)
    target_link_libraries(test_AllEvents gcov)
    target_link_libraries(test_AllLogfiles gcov)
    target_link_libraries(test_Events gcov)

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

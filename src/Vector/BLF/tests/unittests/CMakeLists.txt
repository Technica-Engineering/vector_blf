include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(Boost 1.55 COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_definitions(
    -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

add_executable(test_AllEvents test_AllEvents.cpp)
add_executable(test_AllLogfiles test_AllLogfiles.cpp)
add_executable(test_Events test_Events.cpp)

if(OPTION_USE_GCOV_LCOV)
    add_definitions(-g -O0 -fprofile-arcs -ftest-coverage)
    target_link_libraries(test_AllEvents gcov)
    target_link_libraries(test_AllLogfiles gcov)
    target_link_libraries(test_Events gcov)
endif()

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

enable_testing()

add_test(AllEvents test_AllEvents)
add_test(AllLogfile test_AllLogfile)
add_test(Events test_Events)

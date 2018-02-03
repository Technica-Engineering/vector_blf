if(OPTION_RUN_CCCC)
    add_subdirectory(cccc)
endif()

if(OPTION_RUN_CPPCHECK)
    add_subdirectory(cppcheck)
endif()

if(OPTION_BUILD_TESTS)
    add_subdirectory(unittests)
endif()

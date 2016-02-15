if(OPTION_RUN_CCCC)
    add_subdirectory(cccc)
endif()

if(OPTION_RUN_CPPCHECK)
    add_subdirectory(cppcheck)
endif()

if(OPTION_RUN_TESTS)
    add_subdirectory(unittests)

    if(OPTION_USE_GCOV_LCOV)
        add_subdirectory(lcov)
    endif()
endif()

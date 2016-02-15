include_directories(${PROJECT_SOURCE_DIR}/src)

if(OPTION_RUN_EXAMPLES)
    add_definitions(
        -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
        -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

    set(CMAKE_STATIC_LIBRARY_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
    set(CMAKE_SHARED_LIBRARY_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

    if(WIN32)
        add_custom_target(Vector_DLL-Copy ALL
            ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_BINARY_DIR}/src/Vector/BLF/${PROJECT_NAME}.dll"
            "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Copy ${PROJECT_BINARY_DIR}/src/Vector/BLF/${PROJECT_NAME}.dll to ${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    add_executable(example_Parser Parser.cpp)

    target_link_libraries(example_Parser ${PROJECT_NAME})
endif()

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
    DESTINATION ${CMAKE_INSTALL_DOCDIR}/examples)

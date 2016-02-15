find_package(Cppcheck)

if(CPPCHECK_FOUND)
    foreach(source_file ${source_files})
        list(APPEND source_files_with_path
            "${PROJECT_SOURCE_DIR}/src/Vector/BLF/${source_file}")
    endforeach()

    add_custom_target(cppcheck ALL
        ${CPPCHECK_EXECUTABLE}
        --enable=all
        --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/suppressions.txt
        --xml --xml-version=2
        ${source_files_with_path}
        -I "${PROJECT_BINARY_DIR}/src/Vector/BLF"
        > cppcheck-out.txt 2> cppcheck-err.xml)

    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/cppcheck-out.txt
            ${CMAKE_CURRENT_BINARY_DIR}/cppcheck-err.xml
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/cppcheck)
endif()

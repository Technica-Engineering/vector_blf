find_package(CCCC)

if(CCCC_FOUND)
    foreach(source_file ${source_files})
        list(APPEND source_files_with_path
            "${PROJECT_SOURCE_DIR}/src/Vector/BLF/${source_file}")
    endforeach()

    add_custom_target(cccc ALL
        ${CCCC_EXECUTABLE}
        ${source_files_with_path}
        --opt_infile=${CMAKE_CURRENT_SOURCE_DIR}/cccc.opt
        --outdir=${CMAKE_CURRENT_BINARY_DIR}/cccc
        --html_outfile=${CMAKE_CURRENT_BINARY_DIR}/cccc/index.html
        > cccc-out.txt 2> cccc-err.txt)

    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cccc
        DESTINATION ${CMAKE_INSTALL_DOCDIR})

    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/cccc-out.txt
            ${CMAKE_CURRENT_BINARY_DIR}/cccc-err.txt
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/cccc)
endif()

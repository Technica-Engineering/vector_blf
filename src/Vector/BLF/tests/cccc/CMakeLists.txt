# SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later

get_target_property(sources ${PROJECT_NAME} SOURCES)

add_custom_target(cccc ALL
    ${CCCC_EXECUTABLE}
    ${sources}
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

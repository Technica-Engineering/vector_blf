# SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later

get_target_property(sources ${PROJECT_NAME} SOURCES)

add_custom_target(cppcheck ALL
    ${CPPCHECK_EXECUTABLE}
    --enable=all
    --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/suppressions.txt
    --xml --xml-version=2
    ${sources}
    -I "${PROJECT_BINARY_DIR}/src/Vector/BLF"
    > cppcheck-out.txt 2> cppcheck-err.xml)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/cppcheck-out.txt
        ${CMAKE_CURRENT_BINARY_DIR}/cppcheck-err.xml
    DESTINATION ${CMAKE_INSTALL_DOCDIR}/cppcheck)

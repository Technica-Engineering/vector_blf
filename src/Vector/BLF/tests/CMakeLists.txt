# SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
#
# SPDX-License-Identifier: GPL-3.0-or-later

if(OPTION_RUN_CCCC)
    add_subdirectory(cccc)
endif()

if(OPTION_RUN_CPPCHECK)
    add_subdirectory(cppcheck)
endif()

if(OPTION_BUILD_TESTS)
    add_subdirectory(unittests)
endif()

/*
 * Copyright (C) 2013 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#pragma once

#include "config.h"

/* GCC */
#ifdef __GNUC__

#pragma GCC diagnostic warning "-Wall"
#pragma GCC diagnostic warning "-Wextra"

#endif

/* Visual Studio */
#ifdef _MSC_VER

/* '...' : class '...' needs to have dll-interface to be used by clients of class '..' */
#pragma warning (disable: 4251)

/* elements of array '...' will be default initialized */
#pragma warning (disable: 4351)

/* nonstandard extension used: enum '...' used in qualified name */
#pragma warning (disable: 4482)

#endif

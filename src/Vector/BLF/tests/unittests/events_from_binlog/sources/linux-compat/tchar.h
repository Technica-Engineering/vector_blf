// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

using LPSTR = char *;
using LPCSTR = const char *;
using LPWSTR = wchar_t *;
using LPCWSTR = const wchar_t *;

#ifdef _UNICODE
using LPTSTR = wchar_t *;
using LPCTSTR = const wchar_t *;
#else
using LPTSTR = char *;
using LPCTSTR = const char *;
#endif

#define _T(x) (x)

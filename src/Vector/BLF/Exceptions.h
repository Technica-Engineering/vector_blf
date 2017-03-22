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

#include "platform.h"

#include <stdexcept>

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * This exception is thrown when a file is opened and the file signature doesn't match.
 */
class VECTOR_BLF_EXPORT FileSignatureMismatch : public std::runtime_error
{
public:
    explicit FileSignatureMismatch() : std::runtime_error("File signature doesn't match.") { }
};

/**
 * This exception is thrown when an object is read and the object signature doesn't match.
 */
class VECTOR_BLF_EXPORT ObjectSignatureMismatch : public std::runtime_error
{
public:
    explicit ObjectSignatureMismatch() : std::runtime_error("Object signature doesn't match.") { }
};

}
}

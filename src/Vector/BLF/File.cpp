/*
 * Copyright (C) 2013-2020 Tobias Lorenz.
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

#include <Vector/BLF/File.h>

#include <cstring>

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/Unknown115.h>

namespace Vector {
namespace BLF {

File::File() :
    m_structuredCompressedFile(m_rawCompressedFile),
    m_rawUncompressedFile(m_structuredCompressedFile),
    m_structuredUncompressedFile(m_rawUncompressedFile)
{
}

File::~File() {
    close();
}

void File::open(const char * filename, const std::ios_base::openmode mode) {
    m_structuredUncompressedFile.open(filename, mode);
}

void File::open(const std::string & filename, std::ios_base::openmode mode) {
    open(filename.c_str(), mode);
}

bool File::is_open() const {
    return m_structuredUncompressedFile.is_open();
}

ObjectHeaderBase * File::read() {
    return m_structuredUncompressedFile.read();
}

bool File::write(ObjectHeaderBase * ohb) {
    return m_structuredUncompressedFile.write(ohb);
}

void File::close() {
    m_structuredUncompressedFile.close();
}

FileStatistics File::statistics() const {
    return m_rawCompressedFile.statistics();
}

void File::setStatistics(const FileStatistics & statistics) {
    m_rawCompressedFile.setStatistics(statistics);
}

DWORD File::defaultLogContainerSize() const {
    return m_rawUncompressedFile.defaultLogContainerSize();
}

void File::setDefaultLogContainerSize(DWORD defaultLogContainerSize) {
    m_rawUncompressedFile.setDefaultLogContainerSize(defaultLogContainerSize);
}

}
}

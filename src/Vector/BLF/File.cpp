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

/* StructuredUncompressedFile methods */

void File::open(const char * filename, const std::ios_base::openmode mode) {
    m_structuredUncompressedFile.open(filename, mode);
}

void File::open(const std::string & filename, std::ios_base::openmode mode) {
    open(filename.c_str(), mode);
}

bool File::is_open() const {
    return m_structuredUncompressedFile.is_open();
}

void File::close() {
    m_structuredUncompressedFile.close();
}

StructuredUncompressedFile::streamsize File::read(ObjectHeaderBase ** objectHeaderBase) {
    return m_structuredUncompressedFile.read(objectHeaderBase);
}

ObjectHeaderBase * File::read() {
    ObjectHeaderBase * objectHeaderBase;
    read(&objectHeaderBase);
    return objectHeaderBase;
}

StructuredUncompressedFile::streampos File::tellg() {
    return m_structuredUncompressedFile.tellg();
}

void File::seekg(const StructuredUncompressedFile::streampos pos) {
    m_structuredUncompressedFile.seekg(pos);
}

void File::seekg(const StructuredUncompressedFile::streamoff off, const std::ios_base::seekdir way) {
    m_structuredUncompressedFile.seekg(off, way);
}

bool File::write(ObjectHeaderBase * ohb) {
    return m_structuredUncompressedFile.write(ohb);
}

StructuredUncompressedFile::streampos File::tellp() {
    return m_structuredUncompressedFile.tellp();
}

StructuredUncompressedFile::streamsize File::size() const {
    return m_structuredUncompressedFile.size();
}

/* RawUncompressedFile methods */

RawUncompressedFile::streamsize File::rawUncompressedFileSize() const {
    return m_rawUncompressedFile.size();
}

RawUncompressedFile::streamsize File::rawUncompressedFileStatisticsSize() const {
    return m_rawUncompressedFile.statisticsSize();
}

DWORD File::defaultLogContainerSize() const {
    return m_rawUncompressedFile.defaultLogContainerSize();
}

void File::setDefaultLogContainerSize(DWORD defaultLogContainerSize) {
    m_rawUncompressedFile.setDefaultLogContainerSize(defaultLogContainerSize);
}

/* StructuredCompressedFile methods */

StructuredCompressedFile::streamsize File::structuredCompressedFileSize() const {
    return m_structuredCompressedFile.size();
}

/* RawCompressedFile methods */

RawCompressedFile::streamsize File::rawCompressedFileSize() const {
    return m_rawCompressedFile.size();
}

FileStatistics File::statistics() const {
    return m_rawCompressedFile.statistics();
}

}
}

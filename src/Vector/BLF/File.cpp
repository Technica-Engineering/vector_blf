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

File::~File() {
    close();
}

void File::open(const std::string & filename, std::ios_base::openmode mode) {
    open(filename.c_str(), mode);
}


/* StructuredUncompressedFile pass-thru methods */

void File::open(const char * filename, const std::ios_base::openmode mode) {
    m_structuredUncompressedFile.open(filename, mode);
}

bool File::is_open() const {
    return m_structuredUncompressedFile.is_open();
}

void File::close() {
    m_structuredUncompressedFile.close();
}

StructuredUncompressedFile::indexsize File::read(ObjectHeaderBase ** objectHeaderBase) {
    return m_structuredUncompressedFile.read(objectHeaderBase);
}

StructuredUncompressedFile::indexpos File::tellg() {
    return m_structuredUncompressedFile.tellg();
}

void File::seekg(const StructuredUncompressedFile::indexpos pos) {
    m_structuredUncompressedFile.seekg(pos);
}

void File::seekg(const StructuredUncompressedFile::indexoff off, const std::ios_base::seekdir way) {
    m_structuredUncompressedFile.seekg(off, way);
}

bool File::write(ObjectHeaderBase * ohb) {
    return m_structuredUncompressedFile.write(ohb);
}

StructuredUncompressedFile::indexpos File::tellp() {
    return m_structuredUncompressedFile.tellp();
}

StructuredUncompressedFile::indexsize File::size() const {
    return m_structuredUncompressedFile.size();
}

void File::setApplication(const BYTE id, const BYTE major, const BYTE minor, const BYTE build) {
    m_structuredUncompressedFile.setApplication(id, major, minor, build);
}

void File::setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch) {
    m_structuredUncompressedFile.setApi(major, minor, build, patch);
}

void File::setObjectsRead(const DWORD objectsRead) {
    m_structuredUncompressedFile.setObjectsRead(objectsRead);
}

void File::setMeasurementStartTime(const SYSTEMTIME measurementStartTime) {
    m_structuredUncompressedFile.setMeasurementStartTime(measurementStartTime);
}

void File::setLastObjectTime(const SYSTEMTIME lastObjectTime) {
    m_structuredUncompressedFile.setLastObjectTime(lastObjectTime);
}

/* RawUncompressedFile pass-thru methods */

RawUncompressedFile::streamsize File::rawUncompressedFileSize() const {
    return m_structuredUncompressedFile.rawUncompressedFileSize();
}

RawUncompressedFile::streamsize File::rawUncompressedFileStatisticsSize() const {
    return m_structuredUncompressedFile.rawUncompressedFileStatisticsSize();
}

DWORD File::defaultLogContainerSize() const {
    return m_structuredUncompressedFile.defaultLogContainerSize();
}

void File::setDefaultLogContainerSize(DWORD defaultLogContainerSize) {
    m_structuredUncompressedFile.setDefaultLogContainerSize(defaultLogContainerSize);
}

int File::compressionMethod() const {
    return m_structuredUncompressedFile.compressionMethod();
}

void File::setCompressionMethod(const int compressionMethod) {
    m_structuredUncompressedFile.setCompressionMethod(compressionMethod);
}

int File::compressionLevel() const {
    return m_structuredUncompressedFile.compressionLevel();
}

void File::setCompressionLevel(const int compressionLevel) {
    m_structuredUncompressedFile.setCompressionLevel(compressionLevel);
}

/* StructuredCompressedFile pass-thru methods */

StructuredCompressedFile::indexsize File::structuredCompressedFileSize() const {
    return m_structuredUncompressedFile.structuredCompressedFileSize();
}

/* RawCompressedFile pass-thru methods */

RawCompressedFile::streamsize File::rawCompressedFileSize() const {
    return m_structuredUncompressedFile.rawCompressedFileSize();
}

FileStatistics File::statistics() const {
    return m_structuredUncompressedFile.statistics();
}

ObjectHeaderBase * File::read() {
    ObjectHeaderBase * objectHeaderBase;
    read(&objectHeaderBase);
    return objectHeaderBase;
}

}
}

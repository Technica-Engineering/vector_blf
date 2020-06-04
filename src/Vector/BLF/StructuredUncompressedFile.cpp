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

#include <Vector/BLF/StructuredUncompressedFile.h>

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/File.h>
#include <Vector/BLF/ObjectHeaderBase.h>

namespace Vector {
namespace BLF {

StructuredUncompressedFile::StructuredUncompressedFile(RawUncompressedFile & rawUncompressedFile) :
    m_rawUncompressedFile(rawUncompressedFile)
{
}

void StructuredUncompressedFile::uncompressedFile2ReadWriteQueue() {
    /* identify type */
    ObjectHeaderBase ohb(0, ObjectType::UNKNOWN);
    ohb.read(m_rawUncompressedFile);
    if (!m_rawUncompressedFile.good()) {
        /* This is a normal eof. No objects ended abruptly. */
        return;
    }
    m_rawUncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* create object */
    ObjectHeaderBase * obj = File::createObject(ohb.objectType);
    if (obj == nullptr) {
        /* in case of unknown objectType */
        throw Exception("StructuredUncompressedFile::uncompressedFile2ReadWriteQueue(): Unknown object.");
    }

    /* read object */
    obj->read(m_rawUncompressedFile);
    if (!m_rawUncompressedFile.good()) {
        delete obj;
        throw Exception("StructuredUncompressedFile::uncompressedFile2ReadWriteQueue(): Read beyond end of file.");
    }

    /* push data into readWriteQueue */
    m_readWriteQueue.write(obj);

    /* statistics */
    if (obj->objectType != ObjectType::Unknown115)
        currentObjectCount++;

    /* drop old data */
    m_rawUncompressedFile.dropOldData();
}

void StructuredUncompressedFile::readWriteQueue2UncompressedFile() {
    /* get from readWriteQueue */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

    /* process data */
    if (ohb == nullptr) {
        // Read intentionally returns, when the thread is aborted.
        return;
    }

    /* write into uncompressedFile */
    ohb->write(m_rawUncompressedFile);

    /* statistics */
    if (ohb->objectType != ObjectType::Unknown115)
        currentObjectCount++;

    /* delete object */
    delete ohb;
}

}
}

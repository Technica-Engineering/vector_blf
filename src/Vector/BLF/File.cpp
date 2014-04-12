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

#include <iostream>

#include "File.h"

namespace Vector {
namespace BLF {

File::File() :
    openMode(OpenMode::Read),
    compressionLevel(Z_DEFAULT_COMPRESSION),
    fileStatistics(),
    compressedFile(),
    uncompressedFile(),
    compressionStream()
{
    compressionStream.zalloc = (alloc_func) nullptr;
    compressionStream.zfree = (free_func) nullptr;
    compressionStream.opaque = (voidpf) nullptr;
}

void File::open(const char * filename)
{
    if (openMode == OpenMode::Read) {
        compressedFile.open(filename, std::ios_base::in);
        if (!compressedFile.is_open()) {
            std::cerr << "open failed." << std::endl;
        }

        fileStatistics.read(compressedFile);

        int ret = inflateInit(&compressionStream);
        if (ret != Z_OK) {
            std::cerr << "inflateInit failed." << std::endl;
        }
    } else {
        compressedFile.open(filename, std::ios_base::out);
        if (!compressedFile.is_open()) {
            std::cerr << "open failed." << std::endl;
        }

        fileStatistics.write(compressedFile);

        int ret = deflateInit(&compressionStream, compressionLevel);
        if (ret != Z_OK) {
            std::cerr << "deflateInit failed." << std::endl;
        }
    }
}

void File::close()
{
    if (openMode == OpenMode::Read) {
        int err = inflateEnd(&compressionStream);
    } else {
        int err = deflateEnd(&compressionStream);

        compressedFile.seekg(0);
        fileStatistics.write(compressedFile);
    }

    compressedFile.close();
}

ObjectHeaderBase * File::read(std::iostream & ios)
{
    ObjectHeaderBase ohb;
    ObjectHeaderBase * obj = nullptr;

    ohb.read(ios);
    switch(ohb.objectType) {
    case ObjectType::ENV_INTEGER:
    case ObjectType::ENV_DOUBLE:
    case ObjectType::ENV_STRING:
    case ObjectType::ENV_DATA:
        obj = new EnvironmentVariable();
        obj->copyObjectHeaderBase(ohb);
        obj->read(ios);
        break;

    case ObjectType::LOG_CONTAINER:
        obj = new LogContainer();
        obj->copyObjectHeaderBase(ohb);
        obj->read(ios);
        break;

    case ObjectType::SYS_VARIABLE:
        obj = new SystemVariable();
        obj->copyObjectHeaderBase(ohb);
        obj->read(ios);
        break;

    default:
        obj->skip(ios);
        break;
    }

    /* skip padding */
    ios.seekg(ohb.objectSize%4, std::iostream::cur);

    return obj;
}

ObjectHeaderBase * File::read()
{
    ObjectHeaderBase * obj;

    /* read from compressed file */
    if (compressionStream.avail_out <= 1024) {
        obj = read(compressedFile);

        /* decompress log container */
        if (obj->objectType == ObjectType::LOG_CONTAINER) {
            LogContainer * lc = reinterpret_cast<LogContainer *>(obj);
            compressionStream.avail_out = lc->uncompressedFileSize;
            compressionStream.next_out = reinterpret_cast<Bytef *>(new char[lc->uncompressedFileSize]);
            int ret = deflate(&compressionStream, Z_NO_FLUSH);
            if (ret == Z_STREAM_ERROR) {
                std::cerr << "deflate failed." << std::endl;
            }
        } else {
            return obj;
        }
    }

    /* read from uncompressed file */
    obj = read(uncompressedFile);
    return obj;
}

}
}

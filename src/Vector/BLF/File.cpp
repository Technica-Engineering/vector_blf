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
    m_rawCompressedFile(),
    m_structuredCompressedFile(m_rawCompressedFile),
    m_rawUncompressedFile(m_structuredCompressedFile),
    m_structuredUncompressedFile(m_rawUncompressedFile)
{
    /* set performance/memory values */
    m_structuredUncompressedFile.setBufferSize(10);
    m_rawUncompressedFile.setBufferSize(m_structuredCompressedFile.defaultLogContainerSize());
}

File::~File() {
    close();
}

void File::open(const char * filename, const std::ios_base::openmode mode) {
    /* check */
    if (is_open())
        return;

    /* try to open file */
    m_rawCompressedFile.open(filename, mode | std::ios_base::binary);
    if (!m_rawCompressedFile.is_open())
        return;
    m_openMode = mode;

    /* read */
    if (mode & std::ios_base::in) {
        /* read file statistics */
        fileStatistics.read(m_rawCompressedFile);

        /* fileStatistics done */
        currentUncompressedFileSize += fileStatistics.statisticsSize;

        /* prepare threads */
        m_uncompressedFileThreadRunning = true;
        m_compressedFileThreadRunning = true;

        /* create read threads */
        m_uncompressedFileThread = std::thread(uncompressedFileReadThread, this);
        m_compressedFileThread = std::thread(compressedFileReadThread, this);
    } else

        /* write */
        if (mode & std::ios_base::out) {
            /* write file statistics */
            fileStatistics.write(m_rawCompressedFile);

            /* fileStatistics done */
            currentUncompressedFileSize += fileStatistics.statisticsSize;

            /* prepare threads */
            m_uncompressedFileThreadRunning = true;
            m_compressedFileThreadRunning = true;

            /* create write threads */
            m_uncompressedFileThread = std::thread(uncompressedFileWriteThread, this);
            m_compressedFileThread = std::thread(compressedFileWriteThread, this);
        }
}

void File::open(const std::string & filename, std::ios_base::openmode mode) {
    open(filename.c_str(), mode);
}

bool File::is_open() const {
    return m_rawCompressedFile.is_open();
}

bool File::good() const {
    return m_structuredUncompressedFile.good();
}

bool File::eof() const {
    return m_structuredUncompressedFile.eof();
}

ObjectHeaderBase * File::read() {
    /* read object */
    ObjectHeaderBase * ohb = m_structuredUncompressedFile.read();

    return ohb;
}

void File::write(ObjectHeaderBase * ohb) {
    /* push to queue */
    m_structuredUncompressedFile.write(ohb);
}

void File::close() {
    /* check if file is open */
    if (!is_open())
        return;

    /* read */
    if (m_openMode & std::ios_base::in) {
        /* finalize compressedFileThread */
        m_compressedFileThreadRunning = false;
        m_rawCompressedFile.close();
        if (m_compressedFileThread.joinable())
            m_compressedFileThread.join();

        /* finalize uncompressedFileThread */
        m_uncompressedFileThreadRunning = false;
        m_rawUncompressedFile.abort();
        if (m_uncompressedFileThread.joinable())
            m_uncompressedFileThread.join();

        /* abort readWriteQueue */
        m_structuredUncompressedFile.abort();
    }

    /* write */
    if (m_openMode & std::ios_base::out) {
        /* set eof */
        m_structuredUncompressedFile.setMaxSize(m_structuredUncompressedFile.tellp()); // set eof

        /* finalize uncompressedFileThread */
        if (m_uncompressedFileThread.joinable())
            m_uncompressedFileThread.join();

        /* finalize compressedFileThread */
        if (m_compressedFileThread.joinable())
            m_compressedFileThread.join();

        /* write final LogContainer+Unknown115 */
        if (writeUnknown115) {
            /* create a new log container for it */
            m_rawUncompressedFile.nextLogContainer();

            /* set file size */
            fileStatistics.fileSizeWithoutUnknown115 = static_cast<ULONGLONG>(m_rawCompressedFile.tellp());

            /* write end of file message */
            Unknown115 * unknown115 = new Unknown115;
            m_structuredUncompressedFile.write(unknown115);

            /* process once */
            m_structuredUncompressedFile.readWriteQueue2UncompressedFile();
            uncompressedFile2CompressedFile();
        }

        /* set file statistics */
        fileStatistics.fileSize = static_cast<ULONGLONG>(m_rawCompressedFile.tellp());
        fileStatistics.uncompressedFileSize = currentUncompressedFileSize;
        fileStatistics.objectCount = m_structuredUncompressedFile.currentObjectCount;
        // @todo fileStatistics.objectsRead = ?

        /* write fileStatistics and close compressedFile */
        m_rawCompressedFile.seekp(0);
        fileStatistics.write(m_rawCompressedFile);
        m_rawCompressedFile.close();
    }
}

DWORD File::defaultLogContainerSize() const {
    return m_structuredCompressedFile.defaultLogContainerSize();
}

void File::setDefaultLogContainerSize(DWORD defaultLogContainerSize) {
    m_structuredCompressedFile.setDefaultLogContainerSize(defaultLogContainerSize);
}

void File::compressedFile2UncompressedFile() {
    // rawCompressedFile --> structuredCompressedFile

    /* read header to identify type */
    ObjectHeaderBase ohb(0, ObjectType::UNKNOWN);
    ohb.read(m_rawCompressedFile);
    if (!m_rawCompressedFile.good())
        throw Exception("File::compressedFile2UncompressedFile(): Read beyond end of file.");
    m_rawCompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);
    if (ohb.objectType != ObjectType::LOG_CONTAINER)
        throw Exception("File::compressedFile2UncompressedFile(): Object read for inflation is not a log container.");

    /* read LogContainer */
    std::shared_ptr<LogContainer> logContainer(new LogContainer);
    logContainer->read(m_rawCompressedFile);
    if (!m_rawCompressedFile.good())
        throw Exception("File::compressedFile2UncompressedFile(): Read beyond end of file.");

    // structuredCompressedFile --> rawUncompressedFile

    /* statistics */
    currentUncompressedFileSize +=
        logContainer->internalHeaderSize() +
        logContainer->uncompressedFileSize;

    /* uncompress */
    logContainer->uncompress();

    /* copy into uncompressedFile */
    m_rawUncompressedFile.write(logContainer);
}

void File::uncompressedFile2CompressedFile() {
    // rawUncompressedFile --> structuredCompressedFile

    /* setup new log container */
    LogContainer logContainer;

    /* copy data into LogContainer */
    logContainer.uncompressedFile.resize(m_structuredCompressedFile.defaultLogContainerSize());
    m_rawUncompressedFile.read(
        reinterpret_cast<char *>(logContainer.uncompressedFile.data()),
        m_structuredCompressedFile.defaultLogContainerSize());
    logContainer.uncompressedFileSize = static_cast<DWORD>(m_rawUncompressedFile.gcount());
    logContainer.uncompressedFile.resize(logContainer.uncompressedFileSize);

    /* compress */
    if (compressionLevel == 0) {
        /* no compression */
        logContainer.compress(0, 0);
    } else {
        /* zlib compression */
        logContainer.compress(2, compressionLevel);
    }

    // structuredCompressedFile --> rawCompressedFile

    /* write log container */
    logContainer.write(m_rawCompressedFile);

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    /* drop old data */
    m_rawUncompressedFile.dropOldData();
}

void File::uncompressedFileReadThread(File * file) {
    while (file->m_uncompressedFileThreadRunning) {
        /* process */
        try {
            file->m_structuredUncompressedFile.uncompressedFile2ReadWriteQueue();
        } catch (Vector::BLF::Exception &) {
            file->m_uncompressedFileThreadRunning = false;
        }

        /* check for eof */
        if (!file->m_rawUncompressedFile.good())
            file->m_uncompressedFileThreadRunning = false;
    }

    /* set end of file */
    file->m_structuredUncompressedFile.setMaxSize(file->m_structuredUncompressedFile.tellp());
}

void File::uncompressedFileWriteThread(File * file) {
    while (file->m_uncompressedFileThreadRunning) {
        /* process */
        file->m_structuredUncompressedFile.readWriteQueue2UncompressedFile();

        /* check for eof */
        if (!file->m_structuredUncompressedFile.good())
            file->m_uncompressedFileThreadRunning = false;
    }

    /* set end of file */
    file->m_rawUncompressedFile.setFileSize(file->m_rawUncompressedFile.tellp());
}

void File::compressedFileReadThread(File * file) {
    while (file->m_compressedFileThreadRunning) {
        /* process */
        try {
            file->compressedFile2UncompressedFile();
        } catch (Vector::BLF::Exception &) {
            file->m_compressedFileThreadRunning = false;
        }

        /* check for eof */
        if (!file->m_rawCompressedFile.good())
            file->m_compressedFileThreadRunning = false;
    }

    /* set end of file */
    file->m_rawUncompressedFile.setFileSize(file->m_rawUncompressedFile.tellp());
}

void File::compressedFileWriteThread(File * file) {
    while (file->m_compressedFileThreadRunning) {
        /* process */
        file->uncompressedFile2CompressedFile();

        /* check for eof */
        if (!file->m_rawUncompressedFile.good())
            file->m_compressedFileThreadRunning = false;
    }

    /* set end of file */
    // There is no CompressedFile::setFileSize that need to be set. std::fstream handles this already.
}

}
}

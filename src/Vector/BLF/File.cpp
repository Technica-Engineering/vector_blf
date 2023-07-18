// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Vector/BLF/File.h>

#include <cstring>
#include <iostream>

#include <Vector/BLF/Exceptions.h>

namespace Vector {
namespace BLF {

File::File() {
    /* set performance/memory values */
    m_readWriteQueue.setBufferSize(10);
    m_uncompressedFile.setBufferSize(m_uncompressedFile.defaultLogContainerSize());
}

File::~File() {
    close();
}

void File::open(const char * filename, const std::ios_base::openmode mode) {
    /* check */
    if (is_open())
        return;

    /* try to open file */
    m_compressedFile.open(filename, mode | std::ios_base::binary);
    if (!m_compressedFile.is_open())
        return;
    m_openMode = mode;

    /* read */
    if (mode & std::ios_base::in) {
        /* read file statistics */
        fileStatistics.read(m_compressedFile);

        /* read restore points */
        // @todo read restore points

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
            fileStatistics.write(m_compressedFile);

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
    return m_compressedFile.is_open();
}

bool File::good() const {
    return m_readWriteQueue.good();
}

bool File::eof() const {
    return m_readWriteQueue.eof();
}

ObjectHeaderBase * File::read() {
    /* read object */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

    return ohb;
}

void File::write(ObjectHeaderBase * ohb) {
    /* push to queue */
    m_readWriteQueue.write(ohb);
}

void File::close() {
    /* check if file is open */
    if (!is_open())
        return;

    /* read */
    if (m_openMode & std::ios_base::in) {
        /* finalize compressedFileThread */
        m_compressedFileThreadRunning = false;
        m_compressedFile.close();

        /* finalize uncompressedFileThread */
        m_uncompressedFileThreadRunning = false;
        m_uncompressedFile.abort();

        /* abort readWriteQueue */
        m_readWriteQueue.abort();

        /* finalize compressedFileThread */
        if (m_compressedFileThread.joinable())
            m_compressedFileThread.join();

        /* finalize uncompressedFileThread */
        if (m_uncompressedFileThread.joinable())
            m_uncompressedFileThread.join();
    }

    /* write */
    if (m_openMode & std::ios_base::out) {
        /* set eof */
        m_readWriteQueue.setFileSize(m_readWriteQueue.tellp()); // set eof

        /* finalize uncompressedFileThread */
        if (m_uncompressedFileThread.joinable())
            m_uncompressedFileThread.join();
        if (m_uncompressedFileThreadException) {
            try{
                std::rethrow_exception(m_uncompressedFileThreadException);
            } catch(const std::exception &ex) {
                std::cerr << "uncompressedFileThread exited with exception: " << ex.what() << std::endl;
            }
        }

        /* finalize compressedFileThread */
        if (m_compressedFileThread.joinable())
            m_compressedFileThread.join();
        if (m_compressedFileThreadException) {
            try{
                std::rethrow_exception(m_compressedFileThreadException);
            } catch(const std::exception &ex) {
                std::cerr << "compressedFileThread exited with exception: " << ex.what() << std::endl;
            }
        }

        /* write restore points */
        if (writeRestorePoints) {
            /* create a new log container for it */
            m_uncompressedFile.nextLogContainer();

            /* set file size */
            fileStatistics.restorePointsOffset = static_cast<uint64_t>(m_compressedFile.tellp());

            /* write end of file message */
//            auto * unknown115 = new Unknown115;
//            m_readWriteQueue.write(unknown115);

            /* process once */
            readWriteQueue2UncompressedFile();
            uncompressedFile2CompressedFile();
        }

        /* set file statistics */
        fileStatistics.fileSize = static_cast<uint64_t>(m_compressedFile.tellp());
        fileStatistics.uncompressedFileSize = currentUncompressedFileSize;
        fileStatistics.objectCount = currentObjectCount;
        // @todo fileStatistics.objectsRead = ?

        /* write fileStatistics and close compressedFile */
        m_compressedFile.seekp(0);
        fileStatistics.write(m_compressedFile);
        m_compressedFile.close();
    }
}

uint32_t File::defaultLogContainerSize() const {
    return m_uncompressedFile.defaultLogContainerSize();
}

void File::setDefaultLogContainerSize(uint32_t defaultLogContainerSize) {
    m_uncompressedFile.setDefaultLogContainerSize(defaultLogContainerSize);
}

ObjectHeaderBase * File::createObject(ObjectType type) {
    ObjectHeaderBase * obj = nullptr;

    switch (type) {
    case ObjectType::UNKNOWN:
        break;

    case ObjectType::CAN_MESSAGE:
        obj = new CanMessage();
        break;

    case ObjectType::CAN_ERROR:
        obj = new CanErrorFrame();
        break;

    case ObjectType::CAN_OVERLOAD:
        obj = new CanOverloadFrame();
        break;

    case ObjectType::CAN_STATISTIC:
        obj = new CanDriverStatistic();
        break;

    case ObjectType::APP_TRIGGER:
        obj = new AppTrigger();
        break;

    case ObjectType::ENV_INTEGER:
    case ObjectType::ENV_DOUBLE:
    case ObjectType::ENV_STRING:
    case ObjectType::ENV_DATA:
        obj = new EnvironmentVariable();
        break;

    case ObjectType::LOG_CONTAINER:
        obj = new LogContainer();
        break;

    case ObjectType::Reserved26:
    case ObjectType::Reserved27:
    case ObjectType::Reserved28:
        break;

    case ObjectType::CAN_DRIVER_ERROR:
        obj = new CanDriverError();
        break;

    case ObjectType::CAN_DRIVER_SYNC:
        obj = new CanDriverHwSync();
        break;

    case ObjectType::REALTIMECLOCK:
        obj = new RealtimeClock();
        break;

    case ObjectType::Reserved52:
    case ObjectType::Reserved53:
        break;

    case ObjectType::APP_TEXT:
        obj = new AppText();
        break;

    case ObjectType::SYS_VARIABLE:
        obj = new SystemVariable();
        break;

    case ObjectType::CAN_ERROR_EXT:
        obj = new CanErrorFrameExt();
        break;

    case ObjectType::CAN_DRIVER_ERROR_EXT:
        obj = new CanDriverErrorExt();
        break;

    case ObjectType::SERIAL_EVENT:
        obj = new SerialEvent();
        break;

    case ObjectType::OVERRUN_ERROR:
        obj = new DriverOverrun();
        break;

    case ObjectType::EVENT_COMMENT:
        obj = new EventComment();
        break;

    case ObjectType::GLOBAL_MARKER:
        obj = new GlobalMarker();
        break;


    case ObjectType::CAN_FD_MESSAGE:
        obj = new CanFdMessage();
        break;

    case ObjectType::CAN_FD_MESSAGE_64:
        obj = new CanFdMessage64();
        break;

    case ObjectType::CAN_FD_ERROR_64:
        obj = new CanFdErrorFrame64();
        break;

    case ObjectType::Reserved108:
        break;

    case ObjectType::Unknown115:
        obj = new RestorePointContainer;
        break;

    case ObjectType::Reserved116:
    case ObjectType::Reserved117:
        break;

    case ObjectType::TEST_STRUCTURE:
        obj = new TestStructure;
        break;

    case ObjectType::DIAG_REQUEST_INTERPRETATION:
        obj = new DiagRequestInterpretation;
        break;

    case ObjectType::FUNCTION_BUS:
        obj = new FunctionBus;
        break;

    case ObjectType::DATA_LOST_BEGIN:
        obj = new DataLostBegin;
        break;

    case ObjectType::DATA_LOST_END:
        obj = new DataLostEnd;
        break;
        
    case ObjectType::TRIGGER_CONDITION:
        obj = new TriggerCondition;
        break;

    case ObjectType::CAN_SETTING_CHANGED:
        obj = new CanSettingChanged;
        break;

    case ObjectType::DISTRIBUTED_OBJECT_MEMBER:
        obj = new DistributedObjectMember;
        break;

    case ObjectType::ATTRIBUTE_EVENT:
        obj = new AttributeEvent;
        break;
    }

    return obj;
}

void File::uncompressedFile2ReadWriteQueue() {
    /* identify type */
    ObjectHeaderBase ohb(0, ObjectType::UNKNOWN);
    ohb.read(m_uncompressedFile);
    if (!m_uncompressedFile.good()) {
        /* This is a normal eof. No objects ended abruptly. */
        return;
    }
    m_uncompressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);

    /* create object */
    ObjectHeaderBase * obj = createObject(ohb.objectType);
    if (obj == nullptr) {
        /* in case of unknown objectType */
        m_uncompressedFile.seekg(ohb.objectSize, std::ios_base::cur);
        return;
    }

    int32_t tmp = 0;
    if (obj->calculateObjectSize() > ohb.objectSize) {
        // we are about to read too much data
        tmp = ohb.objectSize - obj->calculateObjectSize();
    }

    /* read object */
    obj->read(m_uncompressedFile);
    if (!m_uncompressedFile.good()) {
        delete obj;
        throw Exception("File::uncompressedFile2ReadWriteQueue(): Read beyond end of file.");
    }

    if (tmp!=0) {
        m_uncompressedFile.seekg(tmp);
    }

    /* push data into readWriteQueue */
    m_readWriteQueue.write(obj);

    /* statistics */
    if (obj->objectType != ObjectType::Unknown115)
        currentObjectCount++;

    /* drop old data */
    m_uncompressedFile.dropOldData();
}

void File::readWriteQueue2UncompressedFile() {
    /* get from readWriteQueue */
    ObjectHeaderBase * ohb = m_readWriteQueue.read();

    /* process data */
    if (ohb == nullptr) {
        // Read intentionally returns, when the thread is aborted.
        return;
    }

    /* write into uncompressedFile */
    ohb->write(m_uncompressedFile);

    /* statistics */
    if (ohb->objectType != ObjectType::Unknown115)
        currentObjectCount++;

    /* delete object */
    delete ohb;
}

void File::compressedFile2UncompressedFile() {
    /* read header to identify type */
    ObjectHeaderBase ohb(0, ObjectType::UNKNOWN);
    ohb.read(m_compressedFile);
    if (!m_compressedFile.good())
        throw Exception("File::compressedFile2UncompressedFile(): Read beyond end of file.");
    m_compressedFile.seekg(-ohb.calculateHeaderSize(), std::ios_base::cur);
    if (ohb.objectType != ObjectType::LOG_CONTAINER)
        throw Exception("File::compressedFile2UncompressedFile(): Object read for inflation is not a log container.");

    /* read LogContainer */
    std::shared_ptr<LogContainer> logContainer(new LogContainer);
    logContainer->read(m_compressedFile);
    if (!m_compressedFile.good())
        throw Exception("File::compressedFile2UncompressedFile(): Read beyond end of file.");

    /* statistics */
    currentUncompressedFileSize +=
        logContainer->internalHeaderSize() +
        logContainer->uncompressedFileSize;

    /* uncompress */
    logContainer->uncompress();

    /* copy into uncompressedFile */
    m_uncompressedFile.write(logContainer);
}

void File::uncompressedFile2CompressedFile() {
    /* setup new log container */
    LogContainer logContainer;

    /* copy data into LogContainer */
    logContainer.uncompressedFile.resize(m_uncompressedFile.defaultLogContainerSize());
    m_uncompressedFile.read(
        reinterpret_cast<char *>(logContainer.uncompressedFile.data()),
        m_uncompressedFile.defaultLogContainerSize());
    logContainer.uncompressedFileSize = static_cast<uint32_t>(m_uncompressedFile.gcount());
    logContainer.uncompressedFile.resize(logContainer.uncompressedFileSize);

    /* compress */
    if (compressionLevel == 0) {
        /* no compression */
        logContainer.compress(0, 0);
    } else {
        /* zlib compression */
        logContainer.compress(2, compressionLevel);
    }

    /* write log container */
    logContainer.write(m_compressedFile);

    /* statistics */
    currentUncompressedFileSize +=
        logContainer.internalHeaderSize() +
        logContainer.uncompressedFileSize;

    /* drop old data */
    m_uncompressedFile.dropOldData();
}

void File::uncompressedFileReadThread(File * file) {
    try {
        while (file->m_uncompressedFileThreadRunning) {
            /* process */
            try {
                file->uncompressedFile2ReadWriteQueue();
            } catch (Vector::BLF::Exception &) {
                file->m_uncompressedFileThreadRunning = false;
            }

            /* check for eof */
            if (!file->m_uncompressedFile.good())
                file->m_uncompressedFileThreadRunning = false;
        }

        /* set end of file */
        file->m_readWriteQueue.setFileSize(file->m_readWriteQueue.tellp());
    } catch (...) {
        file->m_uncompressedFileThreadException = std::current_exception();
    }
}

void File::uncompressedFileWriteThread(File * file) {
    try {
        while (file->m_uncompressedFileThreadRunning) {
            /* process */
            file->readWriteQueue2UncompressedFile();

            /* check for eof */
            if (!file->m_readWriteQueue.good())
                file->m_uncompressedFileThreadRunning = false;
        }

        /* set end of file */
        file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp());
    } catch (...) {
        file->m_uncompressedFileThreadException = std::current_exception();
    }
}

void File::compressedFileReadThread(File * file) {
    try {
        while (file->m_compressedFileThreadRunning) {
            /* process */
            try {
                file->compressedFile2UncompressedFile();
            } catch (Vector::BLF::Exception &) {
                file->m_compressedFileThreadRunning = false;
            }

            /* check for eof */
            if (!file->m_compressedFile.good())
                file->m_compressedFileThreadRunning = false;
        }

        /* set end of file */
        file->m_uncompressedFile.setFileSize(file->m_uncompressedFile.tellp());
    } catch (...) {
        file->m_compressedFileThreadException = std::current_exception();
    }
}

void File::compressedFileWriteThread(File * file) {
    try {
        while (file->m_compressedFileThreadRunning) {
            /* process */
            file->uncompressedFile2CompressedFile();

            /* check for eof */
            if (!file->m_uncompressedFile.good())
                file->m_compressedFileThreadRunning = false;
        }

        /* set end of file */
        // There is no CompressedFile::setFileSize that need to be set. std::fstream handles this already.
    } catch (...) {
        file->m_compressedFileThreadException = std::current_exception();
    }
}

}
}

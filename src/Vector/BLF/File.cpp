#include <Vector/BLF/File.h>

#include <algorithm>
#undef NDEBUG
#include <cassert>
#include <cstring>

#include <Vector/BLF/Exceptions.h>
#include <Vector/BLF/LogContainer.h> /* for ObjectSignature */
#include <Vector/BLF/Unknown115.h>
#include <Vector/BLF/Types.h>

namespace Vector {
namespace BLF {

File::~File() {
    close(); // nothing happens, if the file is already closed
}

/* general methods */

void File::open(const char * filename, std::ios_base::openmode mode) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* check if file is already open */
    if (m_file.is_open()) {
        return;
    }

    /* correct file mode */
    mode |= std::ios_base::binary;
    // mode &= ~(std::ios_base::app | std::ios_base::ate | std::ios_base::trunc);

    /* open file */
    m_file.open(filename, mode);
    if (!m_file.is_open()) {
        return;
    }
    m_openMode = mode;
    assert(m_file.tellg() == 0);
    assert(m_file.tellp() == 0);

    /* read operations */
    if (mode & std::ios_base::in) {
        /* index file */
        indexCompressed();
        assert(!m_index.empty());

        /* read file statistics */
        assert(m_index[0].compressedObjectSize == m_fileStatistics.statisticsSize);
        std::vector<uint8_t> data(m_index[0].compressedObjectSize);
        m_file.read(reinterpret_cast<char *>(data.data()), data.size());
        assert(m_file.good());
        m_fileStatistics.fromData(data.begin());

        /* advance pointers */
        m_compressedFileGetPosition = m_fileStatistics.statisticsSize;
        m_uncompressedFileGetPosition = m_fileStatistics.statisticsSize;
        assert(m_file.tellg() == m_compressedFileGetPosition);
    }
    if (mode & std::ios_base::out) {
        assert(m_file.tellp() == 0);

        /* write initial file statistics */
        std::vector<uint8_t> data;
        m_fileStatistics.toData(data);
        assert(data.size() == m_fileStatistics.statisticsSize);
        m_file.write(reinterpret_cast<const char *>(data.data()), data.size());
        assert(m_file.good());

        /* advance pointers */
        m_compressedFilePutPosition = m_fileStatistics.statisticsSize;
        m_compressedFileSize = m_fileStatistics.statisticsSize;
        assert(m_file.tellp() == m_compressedFilePutPosition);
        m_uncompressedFilePutPosition = m_fileStatistics.statisticsSize;
        m_uncompressedFileSize = m_uncompressedFilePutPosition;
        m_uncompressedFileStatisticsSize = m_uncompressedFilePutPosition;

        /* add FileStatistics to index */
        IndexEntry indexEntry;
        indexEntry.uncompressedFilePosition = 0;
        indexEntry.compressedObjectSize = m_fileStatistics.statisticsSize;
        indexEntry.objectType = ObjectType::UNKNOWN;
        indexEntry.uncompressedObjectSize = m_fileStatistics.statisticsSize;
        m_index[0] = indexEntry;
    }
}

bool File::is_open() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_file.is_open();
}

void File::close() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* do nothing, if file is already closed */
    if (!m_file.is_open()) {
        return;
    }

    /* sync the buffered data */
    if (m_openMode & std::ios_base::out) {
        flushOldData();

        /* set file statistics (without Unknown115 objects) */
        m_fileStatistics.uncompressedFileSize = m_uncompressedFileStatisticsSize;
        m_fileStatistics.objectCount = m_objectCount;
        m_fileStatistics.fileSizeWithoutUnknown115 = m_compressedFileSize;

        // @todo handle/write Unknown115
#if 0
        /* write (multiple) unknown115 */
        std::vector<uint8_t> data;
        Unknown115 unknown115;
        unknown115.toData(data);
        unknown115.toData(data);
        LogContainer logContainer;
        logContainer.compress(data, m_compressionMethod, m_compressionLevel);
        data.clear();
        logContainer.toData(data);
        m_file.write(reinterpret_cast<const char *>(data.data()), data.size());
        flushOldData();
#endif

        /* update file statistics (including Unknown115 objects) */
        m_fileStatistics.fileSize = m_compressedFileSize;

        /* write file statistics */
        std::vector<uint8_t> data;
        m_fileStatistics.toData(data);
        assert(m_file.good());
        m_file.seekp(0);
        assert(m_file.good());
        assert(m_file.tellp() == 0);
        m_file.write(reinterpret_cast<const char *>(data.data()), data.size());
        assert(m_file.good());
        assert(m_file.tellp() == m_fileStatistics.statisticsSize);
    }

    /* close file */
    m_file.close();
}

FileStatistics File::statistics() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_fileStatistics;
}

void File::setApplication(const BYTE id, const BYTE major, const BYTE minor, const BYTE build) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_fileStatistics.applicationId = id;
    m_fileStatistics.applicationMajor = major;
    m_fileStatistics.applicationMinor = minor;
    m_fileStatistics.applicationBuild = build;
}

void File::setApi(const BYTE major, const BYTE minor, const BYTE build, const BYTE patch) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_fileStatistics.apiMajor = major;
    m_fileStatistics.apiMinor = minor;
    m_fileStatistics.apiBuild = build;
    m_fileStatistics.apiPatch = patch;
}

void File::setMeasurementStartTime(const SYSTEMTIME time) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_fileStatistics.lastObjectTime = time;
}

void File::setLastObjectTime(const SYSTEMTIME time) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_fileStatistics.lastObjectTime = time;
}

std::streamsize File::compressedSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_compressedFileSize;
}

std::streamsize File::uncompressedSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_uncompressedFileSize;
}

std::streamsize File::uncompressedStatisticsSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_uncompressedFileStatisticsSize;
}

DWORD File::objectCount() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_objectCount;
}

DWORD File::defaultLogContainerSize() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_defaultLogContainerSize;
}

void File::setDefaultLogContainerSize(DWORD size) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_defaultLogContainerSize = size;
}

WORD File::compressionMethod() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_compressionMethod;
}

void File::setCompressionMethod(const WORD compressionMethod) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_compressionMethod = compressionMethod;
}

int File::compressionLevel() const {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_compressionLevel;
}

void File::setCompressionLevel(const int compressionLevel) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    m_compressionLevel = compressionLevel;
}

/* input methods */

std::streamsize File::read(uint8_t * s, const std::streamsize n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    assert(!m_index.empty());
    std::streamsize gcount = 0;
    while (gcount < n) {
        assert(compressedFilePositionContaining(m_uncompressedFileGetPosition) == m_compressedFileGetPosition);

        /* check that index entry exists */
        if (m_index.count(m_compressedFileGetPosition) == 0) {
            return 0;
        }

        /* get index entry */
        const IndexEntry & indexEntry = m_index[m_compressedFileGetPosition];
        const std::streampos bufferBegin = indexEntry.uncompressedFilePosition;
        const std::streampos bufferEnd = bufferBegin + std::streamoff(indexEntry.uncompressedObjectSize);
        assert(bufferBegin <= m_uncompressedFileGetPosition);
        assert(m_uncompressedFileGetPosition < bufferEnd);

        /* load data into cache if not already there */
        if (m_uncompressedFileData.count(bufferBegin) == 0) {
            /* read compressed data */
            std::vector<uint8_t> compressedData;
            compressedData.resize(indexEntry.compressedObjectSize);
            m_file.seekg(m_compressedFileGetPosition);
            assert(m_file.good());
            m_file.read(reinterpret_cast<char *>(compressedData.data()), compressedData.size());
            assert(m_file.good());
            assert(m_file.gcount() == std::streamsize(compressedData.size()));

            /* expand compressed to uncompressed data */
            if (indexEntry.objectType == ObjectType::LOG_CONTAINER) {
                /* interpret it */
                LogContainer logContainer;
                logContainer.fromData(compressedData.begin());

                /* uncompress */
                std::vector<uint8_t> uncompressedData;
                logContainer.uncompress(uncompressedData);

                /* copy into cache */
                m_uncompressedFileData[bufferBegin] = uncompressedData;
            } else {
                /* copy into cache */
                m_uncompressedFileData[bufferBegin] = compressedData;
            }
        }

        /* copy data from cache */
        std::streamoff offset = m_uncompressedFileGetPosition - bufferBegin;
        assert(offset >= 0);
        std::streamsize maxSize = indexEntry.uncompressedObjectSize - offset;
        assert(maxSize > 0);
        std::streamsize size = std::min(n - gcount, maxSize);
        assert(size > 0);
        memcpy(s, m_uncompressedFileData[bufferBegin].data() + offset, size);

        /* advance pointers */
        s += size;
        m_uncompressedFileGetPosition += size;
        if (bufferEnd <= m_uncompressedFileGetPosition) {
            m_compressedFileGetPosition += indexEntry.compressedObjectSize;
        }
        gcount += size;

        /* drop old cache entries */
        dropOldData();
    }

    return gcount;
}

std::streampos File::tellg() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_uncompressedFileGetPosition;
}

void File::seekg(const std::streampos pos) {
    seekg(pos, std::ios_base::beg);
}

void File::seekg(const std::streamoff off, const std::ios_base::seekdir way) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    /* set reference position */
    std::streampos refPos;
    switch(way) {
    default:
    case std::ios_base::beg:
        refPos = 0;
        break;
    case std::ios_base::cur:
        refPos = m_uncompressedFileGetPosition;
        break;
    case std::ios_base::end:
        refPos = m_uncompressedFileSize;
        break;
    }

    /* set get positions */
    m_uncompressedFileGetPosition = refPos + off;
    m_compressedFileGetPosition = compressedFilePositionContaining(m_uncompressedFileGetPosition);

    /* drop all cache entries before get position */
    dropOldData();
}

ObjectHeaderBase * File::read() {
    uint8_t readData[4];

    /* remember position */
    std::streampos pos = tellg();

    /* read object header's signature */
    if (read(reinterpret_cast<uint8_t *>(&readData), sizeof(ObjectHeaderBase::signature)) < std::streamsize(sizeof(ObjectHeaderBase::signature))) {
        return nullptr;
    }
    DWORD signature =
        (static_cast<DWORD>(readData[0]) <<  0) |
        (static_cast<DWORD>(readData[1]) <<  8) |
        (static_cast<DWORD>(readData[2]) << 16) |
        (static_cast<DWORD>(readData[3]) << 24);
    if (signature != ObjectSignature) {
        throw Exception("File::read(): Object signature doesn't match.");
    }

    /* skip object header's headerSize and headerVersion */
    seekg(
        sizeof(ObjectHeaderBase::headerSize) +
        sizeof(ObjectHeaderBase::headerVersion),
        std::ios_base::cur);

    /* read object header's objectSize */
    if (read(reinterpret_cast<uint8_t *>(&readData), sizeof(ObjectHeaderBase::objectSize)) < std::streamsize(sizeof(ObjectHeaderBase::objectSize))) {
        return nullptr;
    }
    DWORD objectSize =
        (static_cast<DWORD>(readData[0]) <<  0) |
        (static_cast<DWORD>(readData[1]) <<  8) |
        (static_cast<DWORD>(readData[2]) << 16) |
        (static_cast<DWORD>(readData[3]) << 24);
    assert(objectSize > 0);

    /* read object header's objectType */
    if (read(reinterpret_cast<uint8_t *>(&readData), sizeof(ObjectHeaderBase::objectType)) < std::streamsize(sizeof(ObjectHeaderBase::objectType))) {
        return nullptr;
    }
    ObjectType objectType = static_cast<ObjectType>(
                                (static_cast<DWORD>(readData[0]) <<  0) |
                                (static_cast<DWORD>(readData[1]) <<  8) |
                                (static_cast<DWORD>(readData[2]) << 16) |
                                (static_cast<DWORD>(readData[3]) << 24));

    /* read data */
    seekg(pos);
    std::vector<uint8_t> data(objectSize);
    std::streamsize size = read(data.data(), data.size());
    if (size < objectSize) {
        return nullptr;
    }

    /* interpret data */
    ObjectHeaderBase * ohb = makeObject(objectType);
    if (!ohb) {
        return ohb;
    }
    ohb->fromData(data.begin());

    /* skip padding */
    seekg(padding(objectType, objectSize), std::ios_base::cur);

    /* increase object count */
    if (objectType != ObjectType::Unknown115) {
        m_objectCount++;
    }

    return ohb;
}

/* output methods */

std::streamsize File::write(uint8_t * s, const std::streamsize n) {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    assert(!m_index.empty()); // at least fileStatistics should be in
    std::streamsize pcount = 0;
    while (pcount < n) {
        assert(compressedFilePositionContaining(m_uncompressedFilePutPosition) == m_compressedFilePutPosition);

        /* create index if not existing yet */
        if (m_index.count(m_compressedFilePutPosition) == 0) {
            /* get last index entry */
            const IndexEntry & lastIndexEntry = m_index[m_index.rbegin()->first];
            assert(lastIndexEntry.uncompressedFilePosition <= m_uncompressedFilePutPosition);
            const std::streampos lastBufferBegin = lastIndexEntry.uncompressedFilePosition;
            const std::streampos lastBufferEnd = lastBufferBegin + std::streamsize(lastIndexEntry.uncompressedObjectSize);
            assert(lastBufferEnd > 0);
            assert(lastBufferEnd <= m_uncompressedFilePutPosition);

            /* create index entry */
            IndexEntry newIndexEntry;
            newIndexEntry.uncompressedFilePosition = lastBufferEnd; // bufferEnd of last entry, is bufferBegin for following entry
            // newIndexEntry.compressedObjectSize is set during sync/flush to file
            newIndexEntry.objectType = ObjectType::LOG_CONTAINER;
            newIndexEntry.uncompressedObjectSize = m_defaultLogContainerSize;
            m_index[m_compressedFilePutPosition] = newIndexEntry;
        }
        assert(m_index.count(m_compressedFilePutPosition) > 0);

        /* get index entry */
        const IndexEntry & indexEntry = m_index[m_compressedFilePutPosition];
        const std::streampos bufferBegin = indexEntry.uncompressedFilePosition;
        const std::streampos bufferEnd = bufferBegin + std::streamoff(indexEntry.uncompressedObjectSize);
        assert(bufferBegin <= m_uncompressedFilePutPosition);
        assert(m_uncompressedFilePutPosition < bufferEnd);

        /* create cache entry if not already there */
        if (m_uncompressedFileData.count(bufferBegin) == 0) {
            std::vector<uint8_t> uncompressedData(m_defaultLogContainerSize);
            m_uncompressedFileData[bufferBegin] = uncompressedData;
        }

        /* copy data into cache */
        std::streamoff offset = m_uncompressedFilePutPosition - bufferBegin;
        assert(offset >= 0);
        std::streamsize maxSize = indexEntry.uncompressedObjectSize - offset;
        assert(maxSize > 0);
        std::streamsize size = std::min(n - pcount, maxSize);
        assert(size > 0);
        memcpy(m_uncompressedFileData[bufferBegin].data() + offset, s, size);

        /* advance pointers */
        s += size;
        m_uncompressedFilePutPosition += size;
        m_uncompressedFileSize = std::max(m_uncompressedFileSize, std::streamsize(m_uncompressedFilePutPosition));
        pcount += size;

        /* write cache entries */
        writeOldData(); // advances m_compressedFilePutPosition
    }

    return pcount;
}

std::streampos File::tellp() {
    /* mutex lock */
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_uncompressedFilePutPosition;
}

void File::write(ObjectHeaderBase * ohb) {
    /* return if nothing is to be written */
    if (!ohb) {
        return;
    }

    /* get data */
    std::vector<uint8_t> data;
    ohb->toData(data);
    assert(data.size() == ohb->objectSize);

    /* add padding */
    DWORD objectSizeWithPadding = ohb->objectSize + padding(ohb->objectType, ohb->objectSize);
    data.resize(objectSizeWithPadding);

    /* write to file */
    std::streamsize size = write(data.data(), data.size());
    assert(size == objectSizeWithPadding);

    /* delete ohb */
    delete ohb;

    /* increase object counter */
    m_objectCount++;
}

void File::indexCompressed() {
    assert(m_file.tellg() == 0);
    assert(m_file.good());

    /* read file statistics */
    {
        uint8_t readData[4];

        /* read FileStatistics::signature */
        m_file.read(reinterpret_cast<char *>(&readData), sizeof(FileStatistics::signature));
        assert(m_file.good());
        if (m_file.gcount() < std::streamsize(sizeof(FileStatistics::signature))) {
            throw Exception("File::indexCompressed(): Unable to read File signature.");
        }
        m_fileStatistics.signature =
            (static_cast<DWORD>(readData[0]) <<  0) |
            (static_cast<DWORD>(readData[1]) <<  8) |
            (static_cast<DWORD>(readData[2]) << 16) |
            (static_cast<DWORD>(readData[3]) << 24);
        if (m_fileStatistics.signature != FileSignature) {
            throw Exception("File::indexCompressed(): File signature doesn't match.");
        }

        /* read FileStatistics::size */
        m_file.read(reinterpret_cast<char *>(&readData), sizeof(FileStatistics::statisticsSize));
        assert(m_file.good());
        m_fileStatistics.statisticsSize =
            (static_cast<DWORD>(readData[0]) <<  0) |
            (static_cast<DWORD>(readData[1]) <<  8) |
            (static_cast<DWORD>(readData[2]) << 16) |
            (static_cast<DWORD>(readData[3]) << 24);
        if (m_file.gcount() < std::streamsize(sizeof(FileStatistics::statisticsSize))) {
            throw Exception("File::indexCompressed(): Unable to read FileStatistics size.");
        }

        /* add FileStatistics to index */
        IndexEntry indexEntry;
        indexEntry.uncompressedFilePosition = 0;
        indexEntry.compressedObjectSize = m_fileStatistics.statisticsSize;
        indexEntry.objectType = ObjectType::UNKNOWN;
        indexEntry.uncompressedObjectSize = m_fileStatistics.statisticsSize;
        m_index[0] = indexEntry;

        /* seek to next object */
        m_compressedFileGetPosition = m_fileStatistics.statisticsSize;
        m_uncompressedFileGetPosition = m_fileStatistics.statisticsSize;
        m_file.seekg(m_compressedFileGetPosition);
        assert(m_file.good());
    }

    /* update statistics */
    m_compressedFileSize = m_compressedFileGetPosition;
    m_uncompressedFileSize = m_uncompressedFileGetPosition;
    m_uncompressedFileStatisticsSize = m_uncompressedFileGetPosition;

    /* read objects */
    while(m_file.good()) {
        uint8_t readData[4];

        /* read ObjectHeaderBase::signature */
        m_file.read(reinterpret_cast<char *>(&readData), sizeof(ObjectHeaderBase::signature));
        if (!m_file.good()) {
            break;
        }
        assert(m_file.good());
        if (m_file.gcount() < std::streamsize(sizeof(ObjectHeaderBase::signature))) {
            throw Exception("File::indexCompressed(): Unable to read Object signature.");
        }
        DWORD signature =
            (static_cast<DWORD>(readData[0]) <<  0) |
            (static_cast<DWORD>(readData[1]) <<  8) |
            (static_cast<DWORD>(readData[2]) << 16) |
            (static_cast<DWORD>(readData[3]) << 24);
        if (signature != ObjectSignature) {
            throw Exception("File::indexCompressed(): Object signature doesn't match.");
        }

        /* skip ObjectHeaderBase::headerSize and ObjectHeaderBase::headerVersion */
        m_file.seekg(
            sizeof(ObjectHeaderBase::headerSize) +
            sizeof(ObjectHeaderBase::headerVersion),
            std::ios_base::cur);
        assert(m_file.good());

        /* read ObjectHeaderBase::objectSize */
        m_file.read(reinterpret_cast<char *>(&readData), sizeof(ObjectHeaderBase::objectSize));
        assert(m_file.good());
        if (m_file.gcount() < std::streamsize(sizeof(ObjectHeaderBase::objectSize))) {
            throw Exception("File::indexCompressed(): Unable to read Object size.");
        }
        DWORD objectSize =
            (static_cast<DWORD>(readData[0]) <<  0) |
            (static_cast<DWORD>(readData[1]) <<  8) |
            (static_cast<DWORD>(readData[2]) << 16) |
            (static_cast<DWORD>(readData[3]) << 24);

        /* read ObjectHeaderBase::objectType */
        m_file.read(reinterpret_cast<char *>(&readData), sizeof(ObjectHeaderBase::objectType));
        assert(m_file.good());
        if (m_file.gcount() < std::streamsize(sizeof(ObjectHeaderBase::objectType))) {
            throw Exception("File::indexCompressed(): Unable to read Object type.");
        }
        ObjectType objectType = static_cast<ObjectType>(
                                    (static_cast<DWORD>(readData[0]) <<  0) |
                                    (static_cast<DWORD>(readData[1]) <<  8) |
                                    (static_cast<DWORD>(readData[2]) << 16) |
                                    (static_cast<DWORD>(readData[3]) << 24));

        /* skip padding */
        objectSize += padding(objectType, objectSize);

        /* LogContainers have other uncompressedSize */
        DWORD uncompressedObjectSize;
        DWORD uncompressedObjectStatisticsSize;
        if (objectType == ObjectType::LOG_CONTAINER) {
            /* skip LogContainer::compressionMethod and LogContainer::reserved* */
            m_file.seekg(sizeof(WORD) + sizeof(WORD) + sizeof(DWORD), std::ios_base::cur);
            assert(m_file.good());

            /* read LogContainer::uncompressedFileSize */
            m_file.read(reinterpret_cast<char *>(&readData), sizeof(LogContainer::uncompressedFileSize));
            assert(m_file.good());
            if (m_file.gcount() < std::streamsize(sizeof(LogContainer::uncompressedFileSize))) {
                throw Exception("File::indexCompressed(): Unable to read LogContainer uncompressedFileSize.");
            }
            DWORD uncompressedFileSize =
                (static_cast<DWORD>(readData[0]) <<  0) |
                (static_cast<DWORD>(readData[1]) <<  8) |
                (static_cast<DWORD>(readData[2]) << 16) |
                (static_cast<DWORD>(readData[3]) << 24);
            uncompressedObjectSize = uncompressedFileSize;
            uncompressedObjectStatisticsSize = 0x20 + uncompressedFileSize; // 0x20 = LogContainer::internalHeaderSize()
        } else {
            uncompressedObjectSize = objectSize;
            uncompressedObjectStatisticsSize = objectSize;
        }

        /* add to index */
        IndexEntry indexEntry;
        indexEntry.uncompressedFilePosition = m_uncompressedFileGetPosition;
        indexEntry.compressedObjectSize = objectSize;
        indexEntry.objectType = objectType;
        indexEntry.uncompressedObjectSize = uncompressedObjectSize;
        m_index[m_compressedFileGetPosition] = indexEntry;

        /* update statistics */
        m_compressedFileSize += objectSize;
        m_uncompressedFileSize += uncompressedObjectSize;
        m_uncompressedFileStatisticsSize += uncompressedObjectStatisticsSize;

        /* seek to next object */
        m_compressedFileGetPosition += objectSize;
        m_uncompressedFileGetPosition += uncompressedObjectSize;
        m_file.seekg(m_compressedFileGetPosition);
        assert(m_file.good());
    }

    /* seek to end and see if file is truncated */
    m_file.clear();
    m_file.seekg(0, std::ios_base::end);
    if (m_compressedFileSize > m_file.tellg()) {
        throw Exception("File::indexCompressed(): File is truncated.");
    }

    /* seek back to begin */
    m_file.clear();
    m_compressedFileGetPosition = 0;
    m_uncompressedFileGetPosition = 0;
    m_file.seekg(0);
    assert(m_file.good());
}

DWORD File::padding(const ObjectType objectType, const DWORD objectSize) const {
    switch(objectType) {
    case ObjectType::ENV_INTEGER: // 6
    case ObjectType::ENV_DOUBLE: // 7
    case ObjectType::ENV_STRING: // 8
    case ObjectType::ENV_DATA: // 9
    case ObjectType::LOG_CONTAINER: // 10
    case ObjectType::MOST_PKT: // 32
    case ObjectType::MOST_PKT2: // 33
    case ObjectType::APP_TEXT: // 65
    case ObjectType::MOST_ALLOCTAB: // 69
    case ObjectType::ETHERNET_FRAME: // 71
    case ObjectType::SYS_VARIABLE: // 72
    case ObjectType::MOST_150_MESSAGE: // 76
    case ObjectType::MOST_150_PKT: // 77
    case ObjectType::MOST_ETHERNET_PKT: // 78
    case ObjectType::MOST_150_MESSAGE_FRAGMENT: // 79
    case ObjectType::MOST_150_PKT_FRAGMENT: // 80
    case ObjectType::MOST_ETHERNET_PKT_FRAGMENT: // 81
    case ObjectType::MOST_150_ALLOCTAB: // 83
    case ObjectType::MOST_50_MESSAGE: // 84
    case ObjectType::MOST_50_PKT: // 85
    case ObjectType::SERIAL_EVENT: // 90
    case ObjectType::EVENT_COMMENT: // 92
    case ObjectType::WLAN_FRAME: // 93
    case ObjectType::GLOBAL_MARKER: // 96
    case ObjectType::AFDX_FRAME: // 97
    case ObjectType::ETHERNET_RX_ERROR: // 102
        return objectSize % 4;
        break;
    default:
        break;
    }

    return 0;
}

std::streampos File::compressedFilePositionContaining(std::streampos uncompressedFilePos) const {
    std::streampos compressedFilePos = 0;

    for(auto it = m_index.begin(); it != m_index.end(); ++it) {
        assert(compressedFilePos == it->first);

        const std::streampos bufferBegin = it->second.uncompressedFilePosition;
        const std::streampos bufferEnd = bufferBegin + std::streamoff(it->second.uncompressedObjectSize);
        if ((bufferBegin <= uncompressedFilePos) && (uncompressedFilePos < bufferEnd)) {
            break;
        }

        compressedFilePos = it->first + std::streamsize(it->second.compressedObjectSize);
    }

    return compressedFilePos;
}

void File::dropOldData() {
    for(auto it = m_uncompressedFileData.begin(); it != m_uncompressedFileData.end(); ) {
        const std::streampos bufferBegin = it->first;
        const std::streampos bufferEnd = bufferBegin + std::streamsize(it->second.size());

        /* delete old entry */
        if (m_uncompressedFileGetPosition - bufferEnd >= 0x16) {
            it = m_uncompressedFileData.erase(it);
        } else {
            ++it;
        }
    }
}

void File::writeOldData() {
    for(auto it = m_uncompressedFileData.begin(); it != m_uncompressedFileData.end(); ) {
        const std::streampos bufferBegin = it->first;
        const std::streampos bufferEnd = bufferBegin + std::streamsize(it->second.size());

        /* write old entry */
        if (m_uncompressedFilePutPosition - bufferEnd >= 0) {
            /* create log container */
            LogContainer logContainer;
            logContainer.compress(it->second, m_compressionMethod, m_compressionLevel);
            std::vector<uint8_t> data;
            logContainer.toData(data);

            /* add padding */
            data.resize(data.size() + padding(ObjectType::LOG_CONTAINER, data.size()));

            /* complete index entry */
            assert(m_index.count(m_compressedFilePutPosition) > 0);
            m_index[m_compressedFilePutPosition].compressedObjectSize = logContainer.objectSize;

            /* write log container to disk */
            assert(compressedFilePositionContaining(bufferBegin) == m_compressedFilePutPosition);
            assert(m_compressedFilePutPosition == m_file.tellp());
            m_file.write(reinterpret_cast<const char *>(data.data()), data.size());
            assert(m_file.good());

            /* advance pointers */
            m_compressedFilePutPosition += data.size();
            m_compressedFileSize = std::max(m_compressedFileSize, std::streamsize(m_compressedFilePutPosition));
            m_uncompressedFileStatisticsSize += logContainer.internalHeaderSize() + data.size();
            assert(m_compressedFilePutPosition == m_file.tellp());

            /* delete first cache entry */
            it = m_uncompressedFileData.erase(it);
        } else {
            ++it;
        }
    }
}

void File::flushOldData() {
    assert(m_compressedFilePutPosition > 0);
    if (m_index.count(m_compressedFilePutPosition) == 0) {
        // no new data to flush
        return;
    }

    /* get index entry */
    IndexEntry & indexEntry = m_index[m_compressedFilePutPosition];
    const std::streampos bufferBegin = indexEntry.uncompressedFilePosition;
    const std::streampos bufferEnd = bufferBegin + std::streamsize(indexEntry.uncompressedObjectSize);
    assert(compressedFilePositionContaining(bufferBegin) == m_compressedFilePutPosition);

    /* get cache entry */
    if (m_uncompressedFileData.count(bufferBegin) == 0) {
        return;
    }

    /* shrink cache entry to fit */
    assert(bufferBegin <= m_uncompressedFilePutPosition);
    assert(m_uncompressedFilePutPosition < bufferEnd);
    indexEntry.uncompressedObjectSize = m_uncompressedFilePutPosition - bufferBegin;
    m_uncompressedFileData[bufferBegin].resize(indexEntry.uncompressedObjectSize);

    /* write it */
    writeOldData();
}

}
}

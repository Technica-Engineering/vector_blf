#include <iostream>
#include <fstream>

#include "Vector/BLF/File.h"

void showFileStatistics(Vector::BLF::FileStatistics * fileStatistics)
{
    std::cout << "statisticsSize: 0x" << std::hex << fileStatistics->statisticsSize << std::endl;
    std::cout << "applicationId: " << std::dec << (unsigned short) fileStatistics->applicationId << std::endl;
    std::cout << "applicationVersion: "
              << (unsigned short) fileStatistics->applicationMajor << "."
              << (unsigned short) fileStatistics->applicationMinor << "."
              << (unsigned short) fileStatistics->applicationBuild << std::endl;
    std::cout << "apiVersion: "
              << (unsigned short) fileStatistics->apiMajor << "."
              << (unsigned short) fileStatistics->apiMinor << "."
              << (unsigned short) fileStatistics->apiBuild << "."
              << (unsigned short) fileStatistics->apiPatch << std::endl;
    std::cout << "fileSize: " << fileStatistics->fileSize << std::endl;
    std::cout << "uncompressedFileSize: " << fileStatistics->uncompressedFileSize <<
                 " (hex: 0x" << std::hex << fileStatistics->uncompressedFileSize << ")" << std::dec << std::endl;
    std::cout << "objectCount: " << fileStatistics->objectCount << std::endl;
    std::cout << "objectsRead: " << fileStatistics->objectsRead << std::endl;
    std::cout << "measurementStartTime: "
              << fileStatistics->measurementStartTime.year << "-"
              << fileStatistics->measurementStartTime.month << "-"
              << fileStatistics->measurementStartTime.day << " "
              << fileStatistics->measurementStartTime.dayOfWeek << " "
              << fileStatistics->measurementStartTime.hour << ":"
              << fileStatistics->measurementStartTime.minute << ":"
              << fileStatistics->measurementStartTime.second << "."
              << fileStatistics->measurementStartTime.milliseconds
              << std::endl;
    std::cout << "lastObjectTime: "
              << fileStatistics->lastObjectTime.year << "-"
              << fileStatistics->lastObjectTime.month << "-"
              << fileStatistics->lastObjectTime.day << " "
              << fileStatistics->lastObjectTime.dayOfWeek << " "
              << fileStatistics->lastObjectTime.hour << ":"
              << fileStatistics->lastObjectTime.minute << ":"
              << fileStatistics->lastObjectTime.second << "."
              << fileStatistics->lastObjectTime.milliseconds
              << std::endl;
    std::cout << std::endl;
}

void showCanMessage(Vector::BLF::CanMessage * canMessage)
{
    std::cout << "CANMessage:"
              << " Channel=" << canMessage->channel
              << " Flags=" << (unsigned short) canMessage->flags
              << " DLC=" << (unsigned short) canMessage->dlc
              << " ID=0x" << std::hex << canMessage->id
              << " Data=";
    for (int i = 0; (i < canMessage->dlc) && (i < 8); ++i) {
        std::cout << std::hex;
        if (canMessage->data[i] <= 0xf)
            std::cout << '0';
        std::cout << ((unsigned short) canMessage->data[i]);
        std::cout << " ";
    }
    std::cout << std::endl;
}

void showEnvironmentVariable(Vector::BLF::EnvironmentVariable * environmentVariable)
{
    std::cout << "EnvironmentVariable:";
    std::cout << " name=" << environmentVariable->name;
    switch(environmentVariable->objectType) {
    case Vector::BLF::ObjectType::ENV_INTEGER:
        std::cout << " value=" << std::dec << (int) *environmentVariable->data;
        std::cout << " type=Integer";
        break;
    case Vector::BLF::ObjectType::ENV_DOUBLE:
        std::cout << " value=" << std::fixed << (double) *environmentVariable->data;
        std::cout << " type=Double";
        break;
    case Vector::BLF::ObjectType::ENV_STRING:
        std::cout << " type=String";
        // todo
        break;
    case Vector::BLF::ObjectType::ENV_DATA:
        std::cout << " type=Data";
        // todo
        break;
    }
    std::cout << std::endl;
}

void showLogContainer(Vector::BLF::LogContainer * logContainer)
{
    std::cout << "signature: 0x" << std::hex << logContainer->signature << std::endl;
    std::cout << "headerSize: 0x" << std::hex << logContainer->headerSize << std::endl;
    std::cout << "headerVersion: 0x" << std::hex << logContainer->headerVersion << std::endl;
    std::cout << "objectSize: 0x" << std::hex << logContainer->objectSize << std::endl;
    std::cout << "objectType: " << std::dec << (int) logContainer->objectType << std::endl;

    std::cout << "objectFlags: 0x" << std::hex << logContainer->objectFlags << std::endl;
    std::cout << "reserved: 0x" << std::hex << logContainer->reserved << std::endl;
    std::cout << "objectVersion: 0x" << std::hex << logContainer->objectVersion << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << logContainer->uncompressedFileSize << std::endl;
    std::cout << std::endl;
}

void showSystemVariable(Vector::BLF::SystemVariable * systemVariable)
{
    std::cout << "SystemVariable:";
    std::cout << " name=" << systemVariable->name;
    switch(systemVariable->type) {
    case Vector::BLF::SystemVariable::Type::Double:
        std::cout << " value=" << std::fixed << (double) *systemVariable->data;
        std::cout << " type=Double";
        break;
    case Vector::BLF::SystemVariable::Type::Long:
        std::cout << " value=" << std::dec << (long) *systemVariable->data;
        std::cout << " type=Long";
        break;
    case Vector::BLF::SystemVariable::Type::String:
        std::cout << " type=String";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::DoubleArray:
        std::cout << " type=DoubleArray";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::LongArray:
        std::cout << " type=LongArray";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::LongLong:
        std::cout << " type=LongLong";
        // todo
        break;
    case Vector::BLF::SystemVariable::Type::ByteArray:
        std::cout << " type=ByteArray";
        // todo
        break;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Parser <filename.blf>" << std::endl;
        return -1;
    }

    Vector::BLF::File file;
    file.open(argv[1]);

    showFileStatistics(&file.fileStatistics);

    while(!file.eof()) {
        Vector::BLF::ObjectHeaderBase * obj = file.read();
        if (obj == nullptr)
            continue;

        switch(obj->objectType) {
        case Vector::BLF::ObjectType::CAN_MESSAGE:
            showCanMessage(reinterpret_cast<Vector::BLF::CanMessage *>(obj));
            break;

        case Vector::BLF::ObjectType::ENV_INTEGER:
        case Vector::BLF::ObjectType::ENV_DOUBLE:
        case Vector::BLF::ObjectType::ENV_STRING:
        case Vector::BLF::ObjectType::ENV_DATA:
            showEnvironmentVariable(reinterpret_cast<Vector::BLF::EnvironmentVariable *>(obj));
            break;

        case Vector::BLF::ObjectType::LOG_CONTAINER:
            showLogContainer(reinterpret_cast<Vector::BLF::LogContainer *>(obj));
            break;

        case Vector::BLF::ObjectType::SYS_VARIABLE:
            showSystemVariable(reinterpret_cast<Vector::BLF::SystemVariable *>(obj));
            break;

        default:
            std::cerr << "No parser support for ObjectType " << std::dec << (unsigned int) obj->objectType << std::endl;
        }
        delete obj;
    }

    std::cout << "End of file." << std::endl;
    std::cout << "objectCount: " << std::dec << file.currentObjectCount << std::endl;
    std::cout << "uncompressedFileSize: " << std::dec << file.currentUncompressedFileSize << std::endl;

    file.close();

    return 0;
}

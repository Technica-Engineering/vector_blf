// SPDX-FileCopyrightText: 2013-2021 Tobias Lorenz <tobias.lorenz@gmx.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <Vector/BLF/platform.h>

#include <Vector/BLF/AbstractFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief object type
 *
 * Object type.
 */
enum class ObjectType : uint32_t {
    UNKNOWN = 0, /**< unknown object */
    CAN_MESSAGE = 1, /**< CAN message object */
    CAN_ERROR = 2, /**< CAN error frame object */
    CAN_OVERLOAD = 3, /**< CAN overload frame object */
    CAN_STATISTIC = 4, /**< CAN driver statistics object */
    APP_TRIGGER = 5, /**< application trigger object */
    ENV_INTEGER = 6, /**< environment integer object */
    ENV_DOUBLE = 7, /**< environment double object */
    ENV_STRING = 8, /**< environment string object */
    ENV_DATA = 9, /**< environment data object */
    LOG_CONTAINER = 10, /**< container object */
    Reserved26 = 26, /**< reserved */
    Reserved27 = 27, /**< reserved */
    Reserved28 = 28, /**< reserved */
    CAN_DRIVER_ERROR = 31, /**< CAN driver error object */
    CAN_DRIVER_SYNC = 44, /**< CAN driver hardware sync */
    REALTIMECLOCK = 51, /**< Realtime clock object */
    Reserved52 = 52, /**< this object ID is available for the future */
    Reserved53 = 53, /**< this object ID is available for the future */
    APP_TEXT = 65, /**< text object */
    SYS_VARIABLE = 72, /**< system variable object */
    CAN_ERROR_EXT = 73, /**< CAN error frame object (extended) */
    CAN_DRIVER_ERROR_EXT = 74, /**< CAN driver error object (extended) */
    SERIAL_EVENT = 90,
    OVERRUN_ERROR = 91, /**< driver overrun event */
    EVENT_COMMENT = 92,
    GLOBAL_MARKER = 96,
    CAN_FD_MESSAGE = 100, /**< CAN FD message object */
    CAN_FD_MESSAGE_64 = 101, /**< CAN FD message object */
    CAN_FD_ERROR_64 = 104, /**< CAN FD Error Frame object */
    Reserved108 = 108,
    Unknown115 = 115,
    Reserved116 = 116,
    Reserved117 = 117,
    TEST_STRUCTURE = 118, /**< Event for test execution flow */
    DIAG_REQUEST_INTERPRETATION = 119, /**< Event for correct interpretation of diagnostic requests */
    FUNCTION_BUS = 124, /**< FunctionBus object */
    DATA_LOST_BEGIN = 125, /**< Data lost begin */
    DATA_LOST_END = 126, /**< Data lost end */
    TRIGGER_CONDITION = 128, /**< Trigger Condition event */
    CAN_SETTING_CHANGED = 129, /**< CAN Settings Changed object */
    DISTRIBUTED_OBJECT_MEMBER = 130, /**< Distributed object member (communication setup) */
    ATTRIBUTE_EVENT = 131, /**< ATTRIBUTE event (communication setup) */
};

/** object signature */
const uint32_t ObjectSignature = 0x4A424F4C; /* LOBJ */

/**
 * @brief Base object header type definition
 *
 * Object header base structure.
 */
struct VECTOR_BLF_EXPORT ObjectHeaderBase {
    ObjectHeaderBase(const uint16_t headerVersion, const ObjectType objectType);
    virtual ~ObjectHeaderBase() noexcept = default;
    ObjectHeaderBase(const ObjectHeaderBase &) = default;
    ObjectHeaderBase & operator=(const ObjectHeaderBase &) = default;
    ObjectHeaderBase(ObjectHeaderBase &&) = default;
    ObjectHeaderBase & operator=(ObjectHeaderBase &&) = default;

    /**
     * Read the data of this object
     *
     * @param is input stream
     */
    virtual void read(AbstractFile & is);

    /**
     * Write the data of this object
     *
     * @param os output stream
     */
    virtual void write(AbstractFile & os);

    /**
     * Calculates the headerSize
     *
     * @return header size
     */
    virtual uint16_t calculateHeaderSize() const;

    /**
     * Calculates the objectSize
     *
     * @return object size
     */
    virtual uint32_t calculateObjectSize() const;

    /**
     * @brief signature (ObjectSignature)
     *
     * Object signature, must be ObjectSignature.
     */
    uint32_t signature {ObjectSignature};

    /**
     * @brief sizeof object header
     *
     * Size of header in bytes, set this member to
     * sizeof(ObjectHeader) or
     * sizeof(ObjectHeader2) depending on
     * the object header type used for the object.
     */
    uint16_t headerSize {};

    /**
     * @brief header version (1)
     *
     * Version number of object header.
     *
     * Set this member to 1 if the object has a member
     * of type ObjectHeader.
     *
     * Set this member to 2 if the object has a member
     * of type ObjectHeader2.
     *
     * @note is set in ObjectHeader/ObjectHeader2
     */
    uint16_t headerVersion {};

    /**
     * @brief object size
     *
     * Object size in bytes.
     */
    uint32_t objectSize {};

    /**
     * @brief object type
     *
     * Object type.
     *
     * @note is set in each event class constructor
     */
    ObjectType objectType {ObjectType::UNKNOWN};
};

}
}

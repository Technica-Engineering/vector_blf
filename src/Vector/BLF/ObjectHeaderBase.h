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

#pragma once

#include "platform.h"

#include "AbstractFile.h"
#include "VectorTypes.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/* BL API */

/**
 * @brief object type
 *
 * Object type.
 */
enum class ObjectType : DWORD {
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
    LIN_MESSAGE = 11, /**< LIN message object */
    LIN_CRC_ERROR = 12, /**< LIN CRC error object */
    LIN_DLC_INFO = 13, /**< LIN DLC info object */
    LIN_RCV_ERROR = 14, /**< LIN receive error object */
    LIN_SND_ERROR = 15, /**< LIN send error object */
    LIN_SLV_TIMEOUT = 16, /**< LIN slave timeout object */
    LIN_SCHED_MODCH = 17, /**< LIN scheduler mode change object */
    LIN_SYN_ERROR = 18, /**< LIN sync error object */
    LIN_BAUDRATE = 19, /**< LIN baudrate event object */
    LIN_SLEEP = 20, /**< LIN sleep mode event object */
    LIN_WAKEUP = 21, /**< LIN wakeup event object */
    MOST_SPY = 22, /**< MOST spy message object */
    MOST_CTRL = 23, /**< MOST control message object */
    MOST_LIGHTLOCK = 24, /**< MOST light lock object */
    MOST_STATISTIC = 25, /**< MOST statistic object */
    reserved_1 = 26, /**< reserved */
    reserved_2 = 27, /**< reserved */
    reserved_3 = 28, /**< reserved */
    FLEXRAY_DATA = 29, /**< FLEXRAY data object */
    FLEXRAY_SYNC = 30, /**< FLEXRAY sync object */
    CAN_DRIVER_ERROR = 31, /**< CAN driver error object */
    MOST_PKT = 32, /**< MOST Packet */
    MOST_PKT2 = 33, /**< MOST Packet including original timestamp */
    MOST_HWMODE = 34, /**< MOST hardware mode event */
    MOST_REG = 35, /**< MOST register data (various chips)*/
    MOST_GENREG = 36, /**< MOST register data (MOST register) */
    MOST_NETSTATE = 37, /**< MOST NetState event */
    MOST_DATALOST = 38, /**< MOST data lost */
    MOST_TRIGGER = 39, /**< MOST trigger */
    FLEXRAY_CYCLE = 40, /**< FLEXRAY V6 start cycle object */
    FLEXRAY_MESSAGE = 41, /**< FLEXRAY V6 message object */
    LIN_CHECKSUM_INFO = 42, /**< LIN checksum info event object */
    LIN_SPIKE_EVENT = 43, /**< LIN spike event object */
    CAN_DRIVER_SYNC = 44, /**< CAN driver hardware sync */
    FLEXRAY_STATUS = 45, /**< FLEXRAY status event object */
    GPS_EVENT = 46, /**< GPS event object */
    FR_ERROR = 47, /**< FLEXRAY error event object */
    FR_STATUS = 48, /**< FLEXRAY status event object */
    FR_STARTCYCLE = 49, /**< FLEXRAY start cycle event object */
    FR_RCVMESSAGE = 50, /**< FLEXRAY receive message event object */
    REALTIMECLOCK = 51, /**< Realtime clock object */
    AVAILABLE2 = 52, /**< this object ID is available for the future */
    AVAILABLE3 = 53, /**< this object ID is available for the future */
    LIN_STATISTIC = 54, /**< LIN statistic event object */
    J1708_MESSAGE = 55, /**< J1708 message object */
    J1708_VIRTUAL_MSG = 56, /**< J1708 message object with more than 21 data bytes */
    LIN_MESSAGE2 = 57, /**< LIN frame object - extended */
    LIN_SND_ERROR2 = 58, /**< LIN transmission error object - extended */
    LIN_SYN_ERROR2 = 59, /**< LIN sync error object - extended */
    LIN_CRC_ERROR2 = 60, /**< LIN checksum error object - extended */
    LIN_RCV_ERROR2 = 61, /**< LIN receive error object */
    LIN_WAKEUP2 = 62, /**< LIN wakeup event object  - extended */
    LIN_SPIKE_EVENT2 = 63, /**< LIN spike event object - extended */
    LIN_LONG_DOM_SIG = 64, /**< LIN long dominant signal object */
    APP_TEXT = 65, /**< text object */
    FR_RCVMESSAGE_EX = 66, /**< FLEXRAY receive message ex event object */
    MOST_STATISTICEX = 67, /**< MOST extended statistic event */
    MOST_TXLIGHT = 68, /**< MOST TxLight event */
    MOST_ALLOCTAB = 69, /**< MOST Allocation table event */
    MOST_STRESS = 70, /**< MOST Stress event */
    ETHERNET_FRAME = 71, /**< Ethernet frame object */
    SYS_VARIABLE = 72, /**< system variable object */
    CAN_ERROR_EXT = 73, /**< CAN error frame object (extended) */
    CAN_DRIVER_ERROR_EXT = 74, /**< CAN driver error object (extended) */
    LIN_LONG_DOM_SIG2 = 75, /**< LIN long dominant signal object - extended */
    MOST_150_MESSAGE = 76, /**< MOST150 Control channel message */
    MOST_150_PKT = 77, /**< MOST150 Asynchronous channel message */
    MOST_ETHERNET_PKT = 78, /**< MOST Ethernet channel message */
    MOST_150_MESSAGE_FRAGMENT = 79, /**< Partial transmitted MOST50/150 Control channel message */
    MOST_150_PKT_FRAGMENT = 80, /**< Partial transmitted MOST50/150 data packet on asynchronous channel */
    MOST_ETHERNET_PKT_FRAGMENT = 81, /**< Partial transmitted MOST Ethernet packet on asynchronous channel */
    MOST_SYSTEM_EVENT = 82, /**< Event for various system states on MOST */
    MOST_150_ALLOCTAB = 83, /**< MOST50/150 Allocation table event */
    MOST_50_MESSAGE = 84, /**< MOST50 Control channel message */
    MOST_50_PKT = 85, /**< MOST50 Asynchronous channel message */
    CAN_MESSAGE2 = 86, /**< CAN message object - extended */
    LIN_UNEXPECTED_WAKEUP = 87,
    LIN_SHORT_OR_SLOW_RESPONSE = 88,
    LIN_DISTURBANCE_EVENT = 89,
    SERIAL_EVENT = 90,
    OVERRUN_ERROR = 91, /**< driver overrun event */
    EVENT_COMMENT = 92,
    WLAN_FRAME = 93,
    WLAN_STATISTIC = 94,
    MOST_ECL = 95, /**< MOST Electrical Control Line event */
    GLOBAL_MARKER = 96,
    AFDX_FRAME = 97,
    AFDX_STATISTIC = 98,
    KLINE_STATUSEVENT = 99, /**< E.g. wake-up pattern */
    CAN_FD_MESSAGE = 100, /**< CAN FD message object*/
    CAN_FD_MESSAGE_64 = 101, /**< CAN FD message object */
    ETHERNET_RX_ERROR = 102, /**< Ethernet RX error object */
    ETHERNET_STATUS = 103, /**< Ethernet status object */
    CAN_FD_ERROR_64 = 104 /**< CAN FD Error Frame object */
};

/**
 * object signature
 */
const DWORD ObjectSignature = 0x4A424F4C; /* LOBJ */

/**
 * @brief Base object header type definition
 *
 * Object header base structure.
 */
class VECTOR_BLF_EXPORT ObjectHeaderBase
{
public:
    ObjectHeaderBase();
    virtual ~ObjectHeaderBase();

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
    virtual size_t calculateHeaderSize();

    /**
     * Calculates the objectSize
     *
     * @return object size
     */
    virtual size_t calculateObjectSize();

    /**
     * @brief signature (ObjectSignature)
     *
     * Object signature, must be ObjectSignature.
     */
    DWORD signature;

    /**
     * @brief sizeof object header
     *
     * Size of header in bytes, set this member to
     * sizeof(ObjectHeader) or
     * sizeof(ObjectHeader2) depending on
     * the object header type used for the object.
     */
    WORD headerSize;

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
     */
    WORD headerVersion;

    /**
     * @brief object size
     *
     * Object size in bytes.
     */
    DWORD objectSize;

    /**
     * @brief object type
     *
     * Object type.
     */
    ObjectType objectType;
};

}
}

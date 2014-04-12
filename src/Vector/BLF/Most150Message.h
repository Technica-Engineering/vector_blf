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

#include "VectorTypes.h"
#include "ObjectHeader2.h"

#include "vector_blf_export.h"

namespace Vector {
namespace BLF {

/**
 * @brief MOST_150_MESSAGE
 */
class Most150Message : public ObjectHeader2
{
public:
    Most150Message();

    virtual void setObjectSize();

    WORD channel; /**< application channel */
    BYTE dir; /**< direction: 0: Rx; 1: Tx; 2: TxRequest */
    BYTE dummy1;
    DWORD sourceAdr; /**< source address */
    DWORD destAdr; /**< target address */
    BYTE transferType; /**< 1: node message; 2: spy message*/
    BYTE state; /**< transmission status */
    BYTE ackNack; /**< acknowledge code */
    BYTE dummy2;
    DWORD crc; /**< Cyclic Redundancy Check */
    BYTE pAck; /**< a preemptive acknowledge code */
    BYTE cAck; /**< CRC acknowledge from the packet receiver(s) to the packet transmitter */
    BYTE priority; /**< priority of the message */
    BYTE pIndex; /**< packet index, increments per message on MOST */
    DWORD msgLen; /**< length of variable data in bytes (51 max) */
    LPBYTE msg; /**< variable data */
};

}
}

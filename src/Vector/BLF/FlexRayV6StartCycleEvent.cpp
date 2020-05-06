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

#include <Vector/BLF/FlexRayV6StartCycleEvent.h>

namespace Vector {
namespace BLF {

FlexRayV6StartCycleEvent::FlexRayV6StartCycleEvent() :
    ObjectHeader(ObjectType::FLEXRAY_CYCLE) {
}

void FlexRayV6StartCycleEvent::read(AbstractFile & is) {
    ObjectHeader::read(is);
    is.read(reinterpret_cast<char *>(&channel), sizeof(channel));
    is.read(reinterpret_cast<char *>(&dir), sizeof(dir));
    is.read(reinterpret_cast<char *>(&lowTime), sizeof(lowTime));
    is.read(reinterpret_cast<char *>(&fpgaTick), sizeof(fpgaTick));
    is.read(reinterpret_cast<char *>(&fpgaTickOverflow), sizeof(fpgaTickOverflow));
    is.read(reinterpret_cast<char *>(&clientIndexFlexRayV6StartCycleEvent), sizeof(clientIndexFlexRayV6StartCycleEvent));
    is.read(reinterpret_cast<char *>(&clusterTime), sizeof(clusterTime));
    is.read(reinterpret_cast<char *>(dataBytes.data()), static_cast<std::streamsize>(dataBytes.size()));
    is.read(reinterpret_cast<char *>(&reservedFlexRayV6StartCycleEvent), sizeof(reservedFlexRayV6StartCycleEvent));
}

void FlexRayV6StartCycleEvent::write(AbstractFile & os) {
    ObjectHeader::write(os);
    os.write(reinterpret_cast<char *>(&channel), sizeof(channel));
    os.write(reinterpret_cast<char *>(&dir), sizeof(dir));
    os.write(reinterpret_cast<char *>(&lowTime), sizeof(lowTime));
    os.write(reinterpret_cast<char *>(&fpgaTick), sizeof(fpgaTick));
    os.write(reinterpret_cast<char *>(&fpgaTickOverflow), sizeof(fpgaTickOverflow));
    os.write(reinterpret_cast<char *>(&clientIndexFlexRayV6StartCycleEvent), sizeof(clientIndexFlexRayV6StartCycleEvent));
    os.write(reinterpret_cast<char *>(&clusterTime), sizeof(clusterTime));
    os.write(reinterpret_cast<char *>(dataBytes.data()), static_cast<std::streamsize>(dataBytes.size()));
    os.write(reinterpret_cast<char *>(&reservedFlexRayV6StartCycleEvent), sizeof(reservedFlexRayV6StartCycleEvent));
}

DWORD FlexRayV6StartCycleEvent::calculateObjectSize() const {
    return
        ObjectHeader::calculateObjectSize() +
        sizeof(channel) +
        sizeof(dir) +
        sizeof(lowTime) +
        sizeof(fpgaTick) +
        sizeof(fpgaTickOverflow) +
        sizeof(clientIndexFlexRayV6StartCycleEvent) +
        sizeof(clusterTime) +
        static_cast<DWORD>(dataBytes.size()) +
        sizeof(reservedFlexRayV6StartCycleEvent);
}

}
}

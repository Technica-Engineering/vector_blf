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

#include <codecvt>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <locale>

#include <Vector/BLF.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        std::cout << "Write-Example <filename.blf>" << std::endl;
        return -1;
    }

    /* open file for writing */
    Vector::BLF::File file;
    file.open(argv[1], std::ios_base::out);
    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return -1;
    }

    /* write a CanMessage */
    auto * canMessage = new Vector::BLF::CanMessage;
    canMessage->channel = 1;
    canMessage->flags = 1; // TX
    canMessage->dlc = 2;
    canMessage->id = 0x33;
    canMessage->data[0] = 0x44;
    canMessage->data[1] = 0x55;
    file.write(canMessage);

    /* close file */
    file.close();

    return 0;
}

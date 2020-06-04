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

#pragma once

#include <Vector/BLF/platform.h>

#include <fstream>
#include <mutex>

#include <Vector/BLF/RawFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * This class allows byte-wise access to the compressed file.
 */
class VECTOR_BLF_EXPORT RawCompressedFile :
    public RawFile
{
public:
    RawCompressedFile();

    void open(const char * filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override;
    bool is_open() const override;
    void close() override;
    bool good() const override;
    bool eof() const override;
    std::streamsize gcount() const override;
    void read(char * s, std::streamsize n) override;
    std::streampos tellg() override;
    void seekg(const std::streampos pos) override;
    void seekg(const std::streamoff off, const std::ios_base::seekdir way) override;
    void write(const char * s, std::streamsize n) override;
    std::streampos tellp() override;
    void seekp(const std::streampos pos) override;
    void seekp(const std::streamoff off, const std::ios_base::seekdir way) override;

private:
    /** actual file on disk */
    std::fstream m_file;

    /** mutex */
    mutable std::mutex m_mutex {};
};

}
}

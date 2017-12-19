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

#include <Vector/BLF/platform.h>

#include <vector>

#include <Vector/BLF/AbstractFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * UncompresesdFile (Input/output memory stream)
 *
 * This class is like a virtual file buffer.
 * m_data has a limited view on this virtual file with
 * start position at m_dataBegin and end position dataEnd.
 * In addition read is done at position m_tellg and
 * write position is at m_tellp.
 * Write or seek operations exceeding dataEnd(), extends the view.
 * And explicit dropOldData cuts the begin, so reduced the view.
 */
class VECTOR_BLF_EXPORT UncompressedFile final : public AbstractFile
{
public:
    UncompressedFile();

    virtual std::streamsize gcount() const override;
    virtual void read(char * s, std::streamsize n) override;
    virtual std::streampos tellg() override;
    virtual void seekg(std::streampos pos) override;
    virtual void seekg(std::streamoff off, std::ios_base::seekdir way) override;
    virtual void write(const char * s, std::streamsize n) override;
    virtual std::streampos tellp() override;
    virtual void seekp(std::streampos pos) override;
    virtual void seekp(std::streamoff off, std::ios_base::seekdir way) override;

    /**
     * drop old data (only if dropSize is possible)
     *
     * @param dropSize size of data to drop (used in write case)
     */
    virtual void dropOldData(std::streamsize dropSize);

private:
    /** last read size */
    std::streamsize m_gcount;

    /** get position */
    std::streampos m_tellg;

    /** put position */
    std::streampos m_tellp;

    /** data start position */
    std::streampos m_dataBegin;

    /** data */
    std::vector<char> m_data;

    /** data end position */
    std::streampos dataEnd() const;
};

}
}

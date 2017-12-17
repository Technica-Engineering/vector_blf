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

#include <fstream>

#include <Vector/BLF/AbstractFile.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/** CompressedFile (Input/output file stream) */
class VECTOR_BLF_EXPORT CompressedFile final : public AbstractFile
{
public:
    CompressedFile();

    virtual void read(char * s, std::streamsize n) override;
    virtual std::streampos tellg() override;
    virtual void seekg(std::streampos pos) override;
    virtual void seekg(std::streamoff off, std::ios_base::seekdir way) override;
    virtual void write(const char * s, std::streamsize n) override;
    virtual std::streampos tellp() override;
    virtual void seekp(std::streampos pos) override;
    virtual void seekp(std::streamoff off, std::ios_base::seekdir way) override;

    /**
     * open file
     *
     * @param filename file name
     * @param openMode open in read or write mode
     */
    virtual void open(const char * filename, std::ios_base::openmode openMode);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    virtual bool is_open() const;

    /**
     * close file
     */
    virtual void close();

    /**
     * check for end-of-file
     *
     * @return true if end-of-file reached
     */
    virtual bool eof() const;

private:
    std::fstream file;
};

}
}

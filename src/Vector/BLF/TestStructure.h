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

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>
#include <Vector/BLF/VectorTypes.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/**
 * @brief TEST_STRUCTURE
 */
class VECTOR_BLF_EXPORT TestStructure final : public ObjectHeader
{
public:
    TestStructure();

    virtual void read(AbstractFile & is) override;
    virtual void write(AbstractFile & os) override;
    virtual DWORD calculateObjectSize() const override;

    /**
     * @brief unique ID identifying the executing test module or test configuration
     */
    DWORD executionObjectIdentify;

    /** enumeration for type */
    enum Type : WORD {
        TM_TESTMODULE = 1,
        TM_TESTGROUP = 2,
        TM_TESTCASE = 3,
        TESTCONFIGURATION = 8,
        TESTUNIT = 9,
        TESTGROUP = 10,
        TESTFIXTURE = 11,
        TESTSEQUENCE = 12,
        TESTSEQUENCELIST = 13,
        TESTCASE = 14,
        TESTCASELIST = 15
    };

    /**
     * @brief type of structure element, see BL_TESTSTRUCT_TYPE_xxx
     */
    WORD type;

    /** reserved */
    WORD reservedTestStructure;

    /**
     * @brief unique number of structure element (in this test run, transitive, can be used to correlate begin/end events)
     */
    DWORD uniqueNo;

    /** enumeration for action */
    enum Action : WORD {
        BEGIN = 1,
        END = 2,

        /**
         * early abortion of test execution (due to e.g. verdict impact, user stop or failed assure pattern),
         * always correlated to test module / test configuration and followed by "end" action
         */
        ABORT = 3
    };

    /**
     * @brief indicates begin/end of structure element, see BL_TESTSTRUCT_ACTION_xxx
     */
    WORD action;

    /** enumeration for result */
    enum Result : WORD {
        UNDEFINED = 0,
        NONE = 1,
        PASSED = 2,
        INCONCLUSIVE = 3,
        FAILED = 4,
        ERRORINTESTSYSTEM = 5
    };

    /**
     * @brief overall result (verdict) for end of structure element events
     */
    WORD result;

    /**
     * @brief string length in wchar_t's for executingObjectName
     */
    DWORD executingObjectNameLength;

    /**
     * @brief string length in wchar_t's for name
     */
    DWORD nameLength;

    /**
     * @brief string length in wchar_t's for text
     */
    DWORD textLength;

    /**
     * @brief name of the executing test module or test configuration as shown in CANoe (wchar_t)
     */
    std::u16string executingObjectName;

    /**
     * @brief name of structure element (can change between begin/end when using CAPL function TestCaseTitle or similar (wchar_t)
     */
    std::u16string name;

    /**
     * @brief full informational text for event as it appears in CANoe trace window
     */
    std::u16string text;
};

}
}

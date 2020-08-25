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

#include <vector>

#include <Vector/BLF/AbstractFile.h>
#include <Vector/BLF/ObjectHeader.h>

#include <Vector/BLF/vector_blf_export.h>

namespace Vector {
namespace BLF {

/** @brief Distributed object member (communication setup) */
struct VECTOR_BLF_EXPORT DistributedObjectMember final : ObjectHeader {
    DistributedObjectMember();

    void read(AbstractFile & is) override;
    void write(AbstractFile & os) override;
    uint32_t calculateObjectSize() const override;

    /** @brief type of the distributed object member */
    enum MemberType : uint32_t {
        MemberTypeInvalid = 0, /**< BL_DO_MEMBER_TYPE_INVALID */
        MemberTypeData = 1, /**< BL_DO_MEMBER_TYPE_DATA */
        MemberTypeMethod = 2, /**< BL_DO_MEMBER_TYPE_METHOD */
        MemberTypeField = 3, /**< BL_DO_MEMBER_TYPE_FIELD */
        MemberTypeEvent = 4, /**< BL_DO_MEMBER_TYPE_EVENT */
        MemberTypeRefMember = 5, /**< BL_DO_MEMBER_TYPE_DOREF_MEMBER */
        MemberTypeRefObject = 6, /**< BL_DO_MEMBER_TYPE_DOREF_OBJECT */
        MemberTypeBindingError = 7 /**< BL_DO_MEMBER_TYPE_BINDING_ERROR */
    };

    /** @brief detail type of the distributed object */
    enum DetailType : uint32_t {
        DetailTypeInvalid = 0, /**< BL_DO_DETAIL_TYPE_INVALID */
        DetailTypeValue = 1, /**< BL_DO_DETAIL_TYPE_VALUE */
        DetailTypeFunctionCall = 2, /**< BL_DO_DETAIL_TYPE_FUNCTION_CALL */
        DetailTypeFunctionReturn = 3, /**< BL_DO_DETAIL_TYPE_FUNCTION_RETURN */
        DetailTypeFunctionDefaults = 4, /**< BL_DO_DETAIL_TYPE_FUNCTION_DEFAULTS */
        DetailTypeSubscriptionState = 5, /**< BL_DO_DETAIL_TYPE_SUBSCRIPTION_STATE */
        DetailTypeAnnouncementState = 6, /**< BL_DO_DETAIL_TYPE_ANNOUNCEMENT_STATE */
        DetailTypeReferencePath = 7, /**< BL_DO_DETAIL_TYPE_REFERENCE_PATH */
        DetailTypeBindingError = 8 /**< BL_DO_DETAIL_TYPE_BINDING_ERROR */
    };

    /* static */

    /** @brief type of the distributed object member */
    uint32_t memberType {MemberType::MemberTypeInvalid};

    /** @brief detail type of the distributed object */
    uint32_t detailType {DetailType::DetailTypeInvalid};

    /** @brief length of variable name in bytes */
    uint32_t pathLength;

    /** @brief length of variable data in bytes */
    uint32_t dataLength;

    /* dynamic */

    /** @brief path of the distributed object member */
    std::string path;

    /** @brief variable data */
    std::vector<uint8_t> data;
};

}
}

#pragma once

#include <cstdint>
#include <cstring>

#include "wtypes.h"

enum : uint32_t {
    GENERIC_READ = 0x80000000,
    GENERIC_WRITE = 0x40000000,
    GENERIC_EXECUTE = 0x20000000,
    GENERIC_ALL = 0x10000000
};

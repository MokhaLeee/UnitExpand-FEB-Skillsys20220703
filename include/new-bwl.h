#pragma once

#include "global.h"
#include "bmsave.h"
#include "bmreliance.h"

#define NEW_BWL_ARRAY_NUM (BWL_ARRAY_NUM * 2)

struct NewBwl {
    /* 00 */ u8 _pad_;
    /* 01 */ u8 supports[UNIT_SUPPORT_MAX_COUNT];
    /* 08 */
};

struct NewBwl * GetNewBwl(u8 pid);

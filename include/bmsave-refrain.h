#pragma once

#include "bmsave.h"

struct SramNewTail {
    /* 0000 */ struct bmsave_unkstruct1 unkstruct1;
    /* 0024 */ struct bmsave_unkstruct2 unkstruct2;
    /* 0038 */ struct bmsave_unkstruct3 unkstruct3;
    /* 017C */ u8 reserved[4];
    /* 0180 */
};

#define SramNewTailCartOffset (CART_SRAM_SIZE - sizeof(struct SramNewTail))

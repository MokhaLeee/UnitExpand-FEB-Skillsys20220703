#pragma once

#include "global.h"
#include "bmunit.h"
#include "bmitem.h"

void SaveExpandedBlueUnit(void * dst, int size);
void LoadExpandedBlueUnit(void * src, int size);

void SaveExpandedPurpleUnit(void * dst, int size);
void LoadExpandedPurpleUnit(void * src, int size);

struct GameSaveUnit {
    /* 00 */ u8 pid;
    /* 01 */ u8 jid;
    /* 02 */ u8 hp;
    /* 03 */ u8 str;
    /* 04 */ u8 mag;
    /* 05 */ u8 skl;
    /* 06 */ u8 spd;
    /* 07 */ u8 def;
    /* 08 */ u8 res;
    /* 09 */ u8 lck;
    /* 0A */ u8 con;
    /* 0B */ u8 mov;
    /* 0C */ u8 xPos  : 6;
             u8 yPos  : 6;
             u8 level : 5;
             u8 exp   : 7;
    /* 0F */ u8 ranks[8];
    /* 17 */ u8 supports[UNIT_SUPPORT_MAX_COUNT];
    /* 1E */ u16 items[UNIT_ITEM_COUNT];
    /* 28 */ u32 state;
    /* 2C */
} BITPACKED;

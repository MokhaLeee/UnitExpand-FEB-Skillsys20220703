#pragma once

#include "global.h"
#include "bmunit.h"

struct PrepUnitListRework {
    struct Unit * units[0x80];
    int max_num;        /* A cunter maybe related to the amount of units in team */
    int latest_pid;     /* Last unit char-id when you leave the prep-unit-screen */
};

extern struct PrepUnitListRework gPrepUnitListRework;

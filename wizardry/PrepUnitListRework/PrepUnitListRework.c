#include "global.h"
#include "bmunit.h"
#include "prepscreen.h"

#include "prep-unit-list.h"

struct Unit * GetUnitFromPrepList(int index)
{
    return gPrepUnitListRework.units[index];
}

void RegisterPrepUnitList(int index, struct Unit * unit)
{
    gPrepUnitListRework.units[index] = unit;
}

int PrepGetUnitAmount()
{
    return gPrepUnitListRework.max_num;
}

void PrepSetUnitAmount(int val)
{
    gPrepUnitListRework.max_num = val;
}

int PrepGetLatestCharId()
{
    if (0 == (gGMData.state.bits.state_0))
        return gPrepUnitListRework.latest_pid;
    else
        return sub_80C4088();
}

void PrepSetLatestCharId(int val)
{
    if (gGMData.state.bits.state_0)
        sub_80C409C(val);
    else
        gPrepUnitListRework.latest_pid = val;
}

void MakePrepUnitList(void)
{
    int i, cur = 0;
    struct Unit * unit;

    for (i = 1; i < 0x40; i++) {
        unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
            continue;

        if (IsUnitInCurrentRoster(unit)) {
            RegisterPrepUnitList(cur, unit);
            cur++;
        }
    }

    for (i = 0xC1; i < 0x100; i++) {
        unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
            continue;

        if (IsUnitInCurrentRoster(unit)) {
            RegisterPrepUnitList(cur, unit);
            cur++;
        }
    }

    PrepSetUnitAmount(cur);
}

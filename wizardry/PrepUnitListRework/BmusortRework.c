#include "global.h"
#include "bmunit.h"
#include "prepscreen.h"
#include "bm.h"

#include "prep-unit-list.h"

void LoadPlayerUnitsFromUnitStack(void)
{
    int i, amt = 0;
    for (i = 0; i < 0x3F; ++i)
    {
        struct Unit * unit = GetUnit(i);
        if (unit)
            ClearUnit(unit);

        if (amt < (sUnitStackSize - 1))
        {
            CpuCopy16(
                sUnitStackBase + amt * sizeof(struct Unit),
                unit,
                sizeof(struct Unit));

            amt++;
        }
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        struct Unit * unit = GetUnit(i);
        if (unit)
            ClearUnit(unit);

        if (amt < (sUnitStackSize - 1))
        {
            CpuCopy16(
                sUnitStackBase + amt * sizeof(struct Unit),
                unit,
                sizeof(struct Unit));

            unit->index = 0;

            amt++;
        }
    }
}

void LoadPlayerUnitsFromUnitStack2(void)
{
    int i, amt = 0;
    for (i = 0; i < 0x3F; ++i)
    {
        struct Unit * unit = GetUnit(i);
        if (unit)
            ClearUnit(unit);

        if (amt < (sUnitStackSize - 1))
        {
            CpuCopy16(
                sUnitStackBase + amt * sizeof(struct Unit),
                unit,
                sizeof(struct Unit));

            amt++;
        }
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        struct Unit * unit = GetUnit(i);
        if (unit)
            ClearUnit(unit);

        if (amt < (sUnitStackSize - 1))
        {
            CpuCopy16(
                sUnitStackBase + amt * sizeof(struct Unit),
                unit,
                sizeof(struct Unit));

            unit->index = 0;

            amt++;
        }
    }
}

void ShrinkPlayerUnits(void)
{
    int i;

    if (!(PLAY_FLAG_7 & gPlaySt.chapterStateBits))
        return;

    if (BM_FLAG_LINKARENA & gBmSt.gameStateBits)
        return;

    InitUnitStack(UnitSwapBuffer2);

    for (i = FACTION_BLUE + 1; i < FACTION_GREEN; ++i)
    {
        struct Unit * unit = GetUnit(i);

        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        if (!(unit->state & US_UNAVAILABLE))
            PushUnit(unit);
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        struct Unit * unit = GetUnit(i);

        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        if (!(unit->state & US_UNAVAILABLE))
            PushUnit(unit);
    }

    LoadPlayerUnitsFromUnitStack2();
}

void ReorderPlayerUnitsBasedOnDeployment(void)
{
    int i;
    struct Unit * unit;

    InitUnitStack(UnitSwapBuffer1);

    for (i = 1; i < 64; i++)
    {
        unit = GetUnit(i);
        if (UNIT_IS_VALID(unit) && !(0x1000C & unit->state))
            PushUnit(unit);
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        unit = GetUnit(i);
        if (UNIT_IS_VALID(unit) && !(0x1000C & unit->state))
            PushUnit(unit);
    }

    for (i = 1; i < 64; i++)
    {
        unit = GetUnit(i);
        if (UNIT_IS_VALID(unit) && (0x1000C & unit->state))
            PushUnit(unit);
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        unit = GetUnit(i);
        if (UNIT_IS_VALID(unit) && (0x1000C & unit->state))
            PushUnit(unit);
    }

    LoadPlayerUnitsFromUnitStack();
}

void SortPlayerUnitsForPrepScreen()
{
    int i, state1, state2;
    struct Unit * unit;
    int count = GetChapterAllyUnitCount();
    int _count = 0;

    InitUnitStack(UnitSwapBuffer1);

    for (i = 1; i < 64; i++)
    {
        unit = GetUnit(i);

        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        unit->state &= 0xFDFFFFFF;

        if (IsUnitInCurrentRoster(unit) &&
            IsCharacterForceDeployed(unit->pCharacterData->number))
                PushUnit(unit);
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        unit = GetUnit(i);

        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        unit->state &= 0xFDFFFFFF;

        if (IsUnitInCurrentRoster(unit) &&
            IsCharacterForceDeployed(unit->pCharacterData->number))
                PushUnit(unit);
    }

    for (i = 1; i < 64; i++)
    {
        unit = GetUnit(i);
        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        if (!IsUnitInCurrentRoster(unit) ||
            !IsCharacterForceDeployed(unit->pCharacterData->number))
            PushUnit(unit);
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        unit = GetUnit(i);
        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        if (!IsUnitInCurrentRoster(unit) ||
            !IsCharacterForceDeployed(unit->pCharacterData->number))
            PushUnit(unit);
    }

    LoadPlayerUnitsFromUnitStack();

    for (i = 1; i < 64; i++)
    {
        unit = GetUnit(i);

        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        if (!IsUnitInCurrentRoster(unit))
            continue;

        if (SomeLeftoverFunctionThatReturns0(unit))
        {
            state1 = unit->state;
            state2 = 0x02000008;
        }
        else
        {
            if (count > _count)
            {
                unit->state &= 0xFFFFFFF7;
                _count++;
                continue;
            }

            state1 = unit->state;
            state2 = 0x08;
        }

        unit->state = state1 | state2;
    }

    for (i = 0xC1; i < 0x100; i++)
    {
        unit = GetUnit(i);

        if (!unit || !UNIT_IS_VALID(unit))
            continue;

        if (!IsUnitInCurrentRoster(unit))
            continue;

        if (SomeLeftoverFunctionThatReturns0(unit))
        {
            state1 = unit->state;
            state2 = 0x02000008;
        }
        else
        {
            if (count > _count)
            {
                unit->state &= 0xFFFFFFF7;
                _count++;
                continue;
            }

            state1 = unit->state;
            state2 = 0x08;
        }

        unit->state = state1 | state2;
    }
}

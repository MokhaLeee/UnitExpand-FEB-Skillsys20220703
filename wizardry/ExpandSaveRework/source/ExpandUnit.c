#include "global.h"
#include "bmunit.h"
#include "agb_sram.h"
#include "expand-save.h"

static void PackUnit(u8 uid, struct GameSaveUnit * unitp)
{
    int i;

    struct Unit * unit = GetUnit(uid);

    if (UNIT_IS_VALID(unit))
    {
        unitp->pid = UNIT_CHAR_ID(unit);
        unitp->jid = UNIT_CLASS_ID(unit);
    }
    else
    {
        struct Unit tmp_unit;
        ClearUnit(&tmp_unit);
        unit = &tmp_unit;
        unitp->pid = 0;
        unitp->jid = 0;
    }

    unitp->hp = unit->maxHP;
    unitp->str = unit->pow;
    unitp->mag = unit->_u3A;
    unitp->skl = unit->skl;
    unitp->spd = unit->spd;
    unitp->def = unit->def;
    unitp->res = unit->res;
    unitp->lck = unit->lck;
    unitp->con = unit->conBonus;
    unitp->mov = unit->movBonus;
    unitp->xPos = unit->xPos;
    unitp->yPos = unit->yPos;
    unitp->level = unit->level;
    unitp->exp = unit->exp;

    for (i = 0; i < 8; i++)
        unitp->ranks[i] = unit->ranks[i];

    for (i = 0; i < UNIT_SUPPORT_MAX_COUNT; i++)
        unitp->supports[i] = unit->supports[i];

    for (i = 0; i < UNIT_ITEM_COUNT; i++)
        unitp->items[i] = unit->items[i];

    unitp->state = unit->state;
}

static void UnpackUnit(u8 uid, struct GameSaveUnit * unitp)
{
    int i;

    struct Unit * unit = GetUnit(uid);
    if (!unit)
        return;

    ClearUnit(unit);

    unit->maxHP = unitp->hp;
    unit->pow = unitp->str;
    unit->_u3A = unitp->mag;
    unit->skl = unitp->skl;
    unit->spd = unitp->spd;
    unit->def = unitp->def;
    unit->res = unitp->res;
    unit->lck = unitp->lck;
    unit->conBonus = unitp->con;
    unit->movBonus = unitp->mov;
    unit->xPos = unitp->xPos;
    unit->yPos = unitp->yPos;
    unit->level = unitp->level;
    unit->exp = unitp->exp;

    for (i = 0; i < 8; i++)
        unit->ranks[i] = unitp->ranks[i];

    for (i = 0; i < UNIT_SUPPORT_MAX_COUNT; i++)
        unit->supports[i] = unitp->supports[i];

    for (i = 0; i < UNIT_ITEM_COUNT; i++)
        unit->items[i] = unitp->items[i];

    unit->state = unitp->state;
}

void SaveExpandedBlueUnit(void * dst, int size)
{
    int i, amt = size / sizeof(struct GameSaveUnit);

    for (i = 52; i < (52 + amt); i++)
    {
        struct GameSaveUnit unitp;
        PackUnit(i, &unitp);

        WriteAndVerifySramFast(&unitp, dst, sizeof(unitp));
        dst += sizeof(unitp);
    }
}

void LoadExpandedBlueUnit(void * src, int size)
{
    int i, amt = size / sizeof(struct GameSaveUnit);

    for (i = 52; i < (52 + amt); i++)
    {
        struct GameSaveUnit unitp;
        ReadSramFast(src, &unitp, sizeof(unitp));

        UnpackUnit(i, &unitp);

        src += sizeof(unitp);
    }
}

void SaveExpandedPurpleUnit(void * dst, int size)
{
    int i, amt = size / sizeof(struct GameSaveUnit);

    for (i = 0xC1; i < (0xC1 + amt); i++)
    {
        struct GameSaveUnit unitp;
        PackUnit(i, &unitp);

        WriteAndVerifySramFast(&unitp, dst, sizeof(unitp));
        dst += sizeof(unitp);
    }
}

void LoadExpandedPurpleUnit(void * src, int size)
{
    int i, amt = size / sizeof(struct GameSaveUnit);

    for (i = 0xC1; i < (0xC1 + amt); i++)
    {
        struct GameSaveUnit unitp;
        ReadSramFast(src, &unitp, sizeof(unitp));

        UnpackUnit(i, &unitp);

        src += sizeof(unitp);
    }
}

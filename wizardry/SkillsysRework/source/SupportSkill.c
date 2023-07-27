#include "global.h"
#include "bmunit.h"
#include "event.h"
#include "uimenu.h"
#include "prepscreen.h"

#include "vanilla-skillsys.h"
#include "new-bwl.h"
#include "skill-system.h"

/**
 * Move unit RAM skill list from BWL to unit supports
 */
void HookUnitLoadingRework(struct Unit * unit)
{
    int i;
    u8 * skills = GetUnitRamSkills(unit);
    for (i = 0; i < UNIT_RAM_SKILL_AMT; i++)
        skills[i] = 0;

    AutoloadSkills(unit);
    *pExtraItemOrSkill = 0;
}

int GetSkillsCore(struct Unit * unit, u8 * out, int size)
{
    u8 sid;
    u8 * skills, tmp_buf[0x10];

    u8 pid = UNIT_CHAR_ID(unit);
    u8 jid = UNIT_CLASS_ID(unit);

    int i, amt = 0;

    /* vanilla */
    sid = PersonalSkillTable[pid];
    if (SKILL_VALID(sid))
        tmp_buf[amt++] = sid;

    sid = ClassSkillTable[jid];
    if (SKILL_VALID(sid))
        tmp_buf[amt++] = sid;

    skills = GetUnitRamSkills(unit);
    for (i = 0; i < UNIT_RAM_SKILL_AMT; i++)
    {
        sid = skills[i];
        if (SKILL_VALID(sid))
            tmp_buf[amt++] = sid;
    }

    tmp_buf[amt] = 0;

    if (out)
    {
        int real = size < amt ? size : amt;
        for (i = 0; i < real; i++)
            out[i] = tmp_buf[i];

        out[size - 1] = 0;
    }

    return amt;
}

/* LynJump! */
int SkillAdder(struct Unit * unit, u8 sid)
{
    int i;
    u8 * skills = GetUnitRamSkills(unit);

    for (i = 0; i < UNIT_RAM_SKILL_AMT; i++)
    {
        if (skills[i] == sid)
            return false;

        if (skills[i] == 0)
        {
            skills[i] = sid;
            return true;
        }
    }

    *pExtraItemOrSkill = sid | 0x8000;
    return true;
}

/* LynJump! */
u8 prGetSkillIdByIndex(struct Unit * unit, int index)
{
    u8 pid = UNIT_CHAR_ID(unit);
    u8 jid = UNIT_CLASS_ID(unit);
    u8 * skills = GetUnitRamSkills(unit);

    switch (index)
    {
    case 0:
        return PersonalSkillTable[pid];

    case 1:
        return ClassSkillTable[jid];

    case 2:
    case 3:
    case 4:
    case 5:
        return skills[index - 2];

    case 6:
        return *pExtraItemOrSkill;

    default:
        return 0;
    }
}

/* LynJump! */
u8 ASMC_ForgetSkill(struct EventEngineProc * proc)
{
    int i;
    u8 sid = gEventSlots[1];
    struct Unit * unit = GetUnitStructFromEventParameter(gEventSlots[2]);
    u8 * list = GetUnitRamSkills(unit);

    if (!unit)
        goto goto_false;

    for (i = 0; i < UNIT_RAM_SKILL_AMT; i++)
    {
        if (list[i] == sid)
        {
            for (; i < UNIT_RAM_SKILL_AMT; i++)
                list[i] = list[i + 1];

            list[UNIT_RAM_SKILL_AMT - 1] = 0;
            gEventSlots[0xC] = 1;
            return 1;
        }
    }

goto_false:
    gEventSlots[0xC] = 0;
    return 0;
}

/* LynJump! */
u8 prMenuRemoveSkillCommand_ForgetEffect(struct MenuProc * menu, struct MenuItemProc * menuItem)
{
    int i;
    struct ProcPrepItemUse * parent = menu->proc_parent;
    u8 index = menuItem->itemNumber - 2;
    struct Unit * unit = parent->unit;
    u8 * list = GetUnitRamSkills(unit);

    for (i = index; i < UNIT_RAM_SKILL_AMT; i++)
        list[i] = list[i + 1];

    list[UNIT_RAM_SKILL_AMT - 1] = *pExtraItemOrSkill;

    return MENU_ACT_END | MENU_ACT_SND6A | MENU_ACT_SND6B | MENU_ACT_CLEAR;
}

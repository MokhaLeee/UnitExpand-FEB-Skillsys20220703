#include "global.h"
#include "bmunit.h"
#include "proc.h"
#include "statscreen.h"

struct StatScreenEffectProc
{
    /* 00 */ PROC_HEADER;

    /* 29 */ u8 pad29[0x38 - 0x29];

    /* 38 */ int direction;
    /* 3C */ int yDispInit;
    /* 40 */ int yDispFinal;

    /* 44 */ u8 pad44[0x4A - 0x44];

    /* 4A */ short newItem; // page or unit depending on slide
    /* 4C */ short timer;
    /* 4E */ short blendDirection;

    /* 50 */ u8 pad50[0x52 - 0x50];

    /* 52 */ u16   key;
};

extern struct StatScreenSt gStatScreen;

struct StatScreenInfo
{
    /* 00 */ u8  unk00;
    /* 01 */ u8  unitId;
    /* 02 */ u16 config;
};

extern struct StatScreenInfo EWRAM_DATA sStatScreenInfo;

extern struct ProcCmd CONST_DATA gProcScr_SSUnitSlide[];
extern struct ProcCmd CONST_DATA gProcScr_StatScreen[];

extern struct Unit * gStatScreenSlideUnit;

void StartUnitSlide(struct Unit * unit, int direction, struct Proc * parent)
{
    struct StatScreenEffectProc* proc = Proc_StartBlocking(gProcScr_SSUnitSlide, parent);

    gStatScreenSlideUnit = unit;
    proc->direction = direction;

    PlaySoundEffect(0xC8); // TODO: song ids
}

void UnitSlide_SetNewUnit(struct StatScreenEffectProc* proc)
{
    gStatScreen.unit = gStatScreenSlideUnit;

    StatScreen_Display(Proc_Find(gProcScr_StatScreen));
    Proc_Break(proc);
}

/* Well... not a fatally flaw, let it go */
#if 0
struct Unit * FindNextUnit(struct Unit * u, int direction)
{
    int faction = UNIT_FACTION(u);
    int i       = u->index;

    struct Unit * unit;

    while (TRUE)
    {
        i = (i + direction) & 0x3F;
        unit = GetUnit(faction + i);

        if (!UNIT_IS_VALID(unit))
            continue;

        if ((sStatScreenInfo.config & STATSCREEN_CONFIG_NONDEAD) && (unit->state & US_DEAD))
            continue;

        if ((sStatScreenInfo.config & STATSCREEN_CONFIG_NONBENCHED) && (unit->state & US_NOT_DEPLOYED))
            continue;

        if ((sStatScreenInfo.config & STATSCREEN_CONFIG_NONUNK9) && (unit->state & US_BIT9))
            continue;

        if ((sStatScreenInfo.config & STATSCREEN_CONFIG_NONROOFED) && (unit->state & US_UNDER_A_ROOF))
            continue;

        if ((sStatScreenInfo.config & STATSCREEN_CONFIG_NONUNK16) && (unit->state & US_BIT16))
            continue;

        if ((sStatScreenInfo.config & STATSCREEN_CONFIG_NONSUPPLY) && (UNIT_CATTRIBUTES(unit) & CA_SUPPLY))
            continue;

        if (UNIT_IS_GORGON_EGG(unit))
            continue;

        return unit;
    }
}
#endif

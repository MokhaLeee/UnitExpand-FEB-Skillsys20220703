#include "global.h"
#include "bmunit.h"

struct Unit * GetFreeBlueUnit(const struct UnitDefinition * uDef)
{
    int i;

    for (i = 1; i < 0x40; ++i) {
        struct Unit * unit = GetUnit(i);

        if (unit->pCharacterData == NULL)
            return unit;
    }

    for (i = 0xC1; i < 0x100; ++i) {
        struct Unit * unit = GetUnit(i);

        if (unit->pCharacterData == NULL)
            return unit;
    }

    return NULL;
}

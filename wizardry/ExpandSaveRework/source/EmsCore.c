#include "global.h"
#include "bmsave.h"
#include "agb_sram.h"

#include "vanilla-skillsys.h"
#include "expand-save.h"

void MsSaveHookSave(void * dst, int size)
{
    StoreConvoyItemsToSaveFile(dst, size);

    /* 0x70C free */
    dst += 0x190;
    SaveExpandedBlueUnit(dst, 12 * sizeof(struct GameSaveUnit));

    dst += 0x2C * 12;
    SaveExpandedPurpleUnit(dst, 29 * sizeof(struct GameSaveUnit));
}

void MsSaveHookLoad(void * src, int size)
{
    LoadConvoyItemsFromSaveFile(src, size);

    /* 0x70C free */
    src += 0x190;
    LoadExpandedBlueUnit(src, 12 * sizeof(struct GameSaveUnit));

    src += 0x2C * 12;
    LoadExpandedPurpleUnit(src, 29 * sizeof(struct GameSaveUnit));
}

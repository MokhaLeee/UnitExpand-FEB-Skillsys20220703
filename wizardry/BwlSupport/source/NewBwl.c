#include "global.h"
#include "bmunit.h"

#include "new-bwl.h"

static inline bool CheckHasBwl(u8 pid)
{
    if (pid >= NEW_BWL_ARRAY_NUM)
        return false;

    if (GetCharacterData(pid)->affinity == 0)
        return false;

    return true;
}

struct NewBwl * GetNewBwl(u8 pid)
{
    if (!CheckHasBwl(pid))
        return NULL;

    return (void *)gPidStatsData + (pid - 1) * sizeof(struct NewBwl);
}

#pragma once

#include "bmunit.h"
#include "vanilla-skillsys.h"

#define SKILL_VALID(sid) ((sid != 0) && (sid < 0xFF))

/* BWL supports */
static inline u8 * GetUnitRamSkills(struct Unit * unit)
{
    return unit->supports;
}

void HookUnitLoadingRework(struct Unit * unit);
int GenerateSkillsBuffer(struct Unit * unit, u8 * out, int size);

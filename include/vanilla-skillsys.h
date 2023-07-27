#pragma once

#include "global.h"
#include "bmunit.h"

#define SKILL_ICON(index) (0x100 | (index))
#define MOUNT_ICON(index) (0x300 | (index))
#define AFFIN_ICON(index) (0x200 | (index))

#define UNIT_RAM_SKILL_AMT 4

/* reloc pointers */
extern struct CharacterData const * const gpCharacterData;

/* Vanilla Skillsys port */
extern const u16 SkillDescTable[256];
extern const u8 ClassSkillTable[];
extern const u8 PersonalSkillTable[];

void AutoloadSkills(struct Unit * unit);
u8 * Skill_Getter(struct Unit * unit);
int SkillDescGetter(u8 sid);
const char * GetSkillName(int sid);
bool SkillTester(struct Unit * unit, u8 sid);
int SkillAdder(struct Unit * unit, u8 sid);

/* AddSkills func */
extern struct Unit * SkillsUnitBuffer;
extern int SkillsCountBuffer;
extern u8 SkillsBuffer[];
extern u16 pExtraItemOrSkill[];

/* msg port */
int GetUnitMagic(struct Unit * unit);
int GetUnitMove(struct Unit * unit);
int GetUnitConstitution(struct Unit * unit);

/* Misc */
int GetTalkee(u8 pid);
u8 GetLeadershipStarCount(struct Unit * unit);

/* ems */
void StoreConvoyItemsToSaveFile(void * dst, int size);
void LoadConvoyItemsFromSaveFile(void * src, int size);

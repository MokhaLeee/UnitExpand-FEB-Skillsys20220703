@ free ram-spaces!
dat 0x0203F000, gUnitLookupExpa
dat 0x0203FDF0, gPrepUnitListRework

@ port arm-none-eabi to agbcc!
fun __divsi3, __aeabi_idiv
fun __modsi3, __aeabi_idivmod
fun __udivsi3, __aeabi_uidiv

fun 0x08B606C9, Skill_Getter
fun 0x08B60B5D, SkillDescGetter
fun 0x08B60945, SkillTester
fun 0x080191B9, GetUnitMagic
fun 0x08019225, GetUnitMove
fun 0x08019285, GetUnitConstitution
fun 0x08B3A8A1, GetTalkee
fun 0x08B39C11, GetLeadershipStarCount
fun 0x08B3B371, DontBlinkLeft
fun 0x08B3BC05, HP_Name_Color
fun 0x08B60C55, AutoloadSkills
fun 0x08B60BB9, SkillAdder
fun 0x08B7DF0D, prGetSkillIdByIndex
fun 0x08B7DA3D, ASMC_ForgetSkill
fun 0x08B7DE01, prMenuRemoveSkillCommand_ForgetEffect
fun 0x08B8447D, StoreConvoyItemsToSaveFile
fun 0x08B8449D, LoadConvoyItemsFromSaveFile

dat 0x08B61898, SkillDescTable
dat 0x08B803F4, Growth_Getter_Table
dat 0x08B2A940, MagClassTable
dat 0x08017d64, gpCharacterData
dat 0x02003BFB, gMssGrowthIndetifer
dat 0x0202BCDE, pExtraItemOrSkill

/* Add Skills */
dat 0x02026BB0, SkillsUnitBuffer
dat 0x02026BB4, SkillsCountBuffer
dat 0x02026B90, SkillsBuffer
dat 0x08B2F6DC, ClassSkillTable
dat 0x08B2F7DC, PersonalSkillTable

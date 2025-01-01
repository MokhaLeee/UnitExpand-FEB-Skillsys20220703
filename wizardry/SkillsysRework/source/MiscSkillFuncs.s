.thumb

.macro blh to, reg=r4
	ldr \reg, =\to
	mov r14, \reg
	.short 0xF800
.endm

/* LynJump! */
.global Skill_Getter
.type Skill_Getter, %function
Skill_Getter:
    push {r4, lr}

	/* if (SkillsUnitBuffer == unit) */
	ldr r1, =SkillsUnitBuffer
	ldr r2, [r1]
	cmp r0, r2
	beq 1f

	/* SkillsUnitBuffer = unit */
	str r0, [r1]

	/* amt = GenerateSkillsBuffer(unit, SkillsBuffer) */
	ldr r1, =SkillsBuffer
	mov r2, #7
    blh GetSkillsCore

	/* SkillsCountBuffer = amt */
	ldr r1, =SkillsCountBuffer
	str r0, [r1]

1:
	ldr r0, =SkillsBuffer
	ldr r1, =SkillsCountBuffer
	ldr r1, [r1]
    pop {r4, pc}

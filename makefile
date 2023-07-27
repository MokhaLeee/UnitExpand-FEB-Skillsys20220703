CACHE_DIR := .cache_dir
$(shell mkdir -p $(CACHE_DIR) > /dev/null)

FE8_GBA := skillsys20220703-feb.gba
FE8_CHX := skillsys20220703-feb-chax.gba

FE8_SYM := $(CACHE_DIR)/fe8.sym
FE8_REF := $(CACHE_DIR)/fe8-ref.s

LIB_SYM := tools/lib/fe8.sym
LIB_REF := tools/lib/fe8-ref.s
EXT_REF := skillsys-ref.s

MAIN    := UnitExpansionSkillsys.event

CLEAN_FILES :=
CLEAN_DIRS  := $(CACHE_DIR)

WIZARDRY_DIR := wizardry
GAMEDATA_DIR :=
HACK_DIRS    := $(WIZARDRY_DIR) $(GAMEDATA_DIR)

PREFIX ?= arm-none-eabi-
CC  := $(PREFIX)gcc
CPP := $(PREFIX)cpp
AS  := $(PREFIX)as
OBJCOPY := $(PREFIX)objcopy

EA_DIR := tools/EventAssembler
EA := $(EA_DIR)/ColorzCore$(EXE)

PARSEFILE         := $(EA_DIR)/Tools/ParseFile$(EXE)
PORTRAITFORMATTER := $(EA_DIR)/Tools/PortraitFormatter$(EXE)
PNG2DMP           := $(EA_DIR)/Tools/Png2Dmp$(EXE)
COMPRESS          := $(EA_DIR)/Tools/compress$(EXE)
LYN               := $(EA_DIR)/Tools/lyn$(EXE) -longcalls
EA_DEP            := $(EA_DIR)/ea-dep$(EXE)

MAIN_DEPS := $(shell $(EA_DEP) $(MAIN) -I $(EA_DIR) --add-missings)

# ========
# = Main =
# ========

$(FE8_CHX): $(MAIN) $(FE8_GBA) $(FE8_SYM) $(MAIN_DEPS)
	cp -f $(FE8_GBA) $(FE8_CHX)
	$(EA) A FE8 -input:$(MAIN) -output:$(FE8_CHX) --nocash-sym || rm -f $(FE8_CHX)
	cat $(FE8_SYM) >> $(FE8_CHX:.gba=.sym)

CLEAN_FILES += $(FE8_CHX)  $(FE8_CHX:.gba=.sym)

$(FE8_SYM): $(LIB_SYM)
	cat $(LIB_SYM) > $(FE8_SYM)

$(FE8_REF): $(LIB_REF) $(EXT_REF)
	cat $(LIB_REF) > $(FE8_REF)
	cat $(EXT_REF) >> $(FE8_REF)

# ============
# = Wizardry =
# ============

INC_DIRS := include tools/lib/include
INC_FLAG := $(foreach dir, $(INC_DIRS), -I $(dir))
LYN_REF := $(FE8_REF:.s=.o)

ARCH    := -mcpu=arm7tdmi -mthumb -mthumb-interwork
CFLAGS  := $(ARCH) $(INC_FLAG) -Wall -Wextra -Wno-unused-parameter -O2 -mtune=arm7tdmi -mlong-calls
ASFLAGS := $(ARCH) $(INC_FLAG)

CDEPFLAGS = -MMD -MT "$*.o" -MT "$*.asm" -MF "$(CACHE_DIR)/$(notdir $*).d" -MP
SDEPFLAGS = --MD "$(CACHE_DIR)/$(notdir $*).d"

%.lyn.event: %.o $(LYN_REF)
	$(LYN) $< $(LYN_REF) > $@

%.dmp: %.o
	$(OBJCOPY) -S $< -O binary $@

%.o: %.s
	$(AS) $(ASFLAGS) $(SDEPFLAGS) -I $(dir $<) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CDEPFLAGS) -g -c $< -o $@

%.asm: %.c
	$(CC) $(CFLAGS) $(CDEPFLAGS) -S $< -o $@ -fverbose-asm

.PRECIOUS: %.o;

-include $(wildcard $(CACHE_DIR)/*.d)

CFILES := $(shell find $(HACK_DIRS) -type f -name '*.c')
CLEAN_FILES += $(CFILES:.c=.o) $(CFILES:.c=.asm) $(CFILES:.c=.dmp) $(CFILES:.c=.lyn.event)

SFILES := $(shell find $(HACK_DIRS) -type f -name '*.s')
CLEAN_FILES += $(SFILES:.s=.o) $(SFILES:.s=.dmp) $(SFILES:.s=.lyn.event)

# ==============
# = MAKE CLEAN =
# ==============
clean:
	rm -f $(CLEAN_FILES)
	rm -rf $(CLEAN_DIRS)

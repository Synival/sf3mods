# -------------------------------------------------------------
# | Important Paths and Files (You may need to change these!) |
# -------------------------------------------------------------

TOOLCHAIN_PATH  := sh2-toolchain
SF3_PATH_scn1   := game-files/scn1
SF3_PATH_scn2   := game-files/scn2
SF3_PATH_scn3   := game-files/scn3
SF3_PATH_pd     := game-files/pd

CC              := $(TOOLCHAIN_PATH)/bin/sh2-elf-gcc
CC_NATIVE       := gcc
OBJCOPY         := $(TOOLCHAIN_PATH)/bin/sh2-elf-objcopy

MOD_PATH        := mods
LIB_PATH        := lib
LIB_SF3_PATH    := lib/sf3
BUILD_PATH      := build

# ---------------------------------------------
# | Mods (You'll need to define things here!) |
# ---------------------------------------------

MODS := $(notdir $(wildcard $(MOD_PATH)/*))

# All inputs to .elf files must (sadly) be provided by hand.
# Use $(MOD_SCN_OBJS) to automatically use all files.
# Otherwise, specify the .?.o file(s) required. The build folder prefix will automatically be added.

addLevelUpAnimation_OBJS_x014 = $(MOD_SCN_OBJS)
compressAniTables_OBJS_x014   = $(MOD_SCN_OBJS)
modernizedCamera_OBJS_x014    = $(MOD_SCN_OBJS)
modernizedLighting_OBJS_x014  = $(MOD_SCN_OBJS)
musicDebugger_OBJS_x001       = $(MOD_SCN_OBJS)

advisorChicken_OBJS_x1aspi_h  = x1aspi_h.c.o
advisorChicken_OBJS_x1stri_h  = x1stri_h.c.o
advisorChicken_OBJS_x1rinjin  = x1rinjin.c.o
advisorChicken_OBJS_x1obhonj  = x1obhonj.c.o

musicFix_OBJS_x014_scn3       = scspMuter.c.o
musicFix_OBJS_1stChanges_scn3 = \
    newCatastrophicError.S.o \
    catastrophicErrorReplacements.c.o \
    scn3RunMusicCommand.S.o \
    newPreBattleMusicCmds.S.o \
    gainLevelJingleFix.c.o
musicFix_OBJS_x014_pd         = scspMuter.c.o
musicFix_OBJS_1stChanges_pd   = \
    newCatastrophicError.S.o \
    catastrophicErrorReplacements.c.o \
    scn3RunMusicCommand.S.o \
    newPreBattleMusicCmds.S.o \
    gainLevelJingleFix.c.o

# ---------------
# | Build Flags |
# ---------------

CFLAGS_NATIVE   := -Wall -std=c23 -g
CFLAGS          := -I$(LIB_SF3_PATH)/inc -m2 -mb -Os -fno-builtin -Wall -Wconversion -Wsign-conversion -Wsign-compare -Wextra -Wpedantic -MMD -MP -std=c23
LDFLAGS         := -nostartfiles -nostdlib -Wl,--orphan-handling=error,--no-warn-rwx-segments

SCENARIO_VAL_scn1 := 1
SCENARIO_VAL_scn2 := 2
SCENARIO_VAL_scn3 := 3
SCENARIO_VAL_pd   := 4

# ------------------
# | Helpful macros |
# ------------------

get_files       = $(patsubst ./%,%,$(shell cd $(1) 2>/dev/null && find . -type f))
get_files_named = $(patsubst ./%,%,$(shell cd $(1) 2>/dev/null && find . -type f -name '$(2)'))

# -------------------------
# | Check for C23 support |
# -------------------------

# Check for -std=C23
HAS_C23_SUPPORT        := $(shell $(CC)        -Werror -std=c23 -x c -c /dev/null -o /dev/null >/dev/null 2>/dev/null && echo "yes")
HAS_NATIVE_C23_SUPPORT := $(shell $(CC_NATIVE) -Werror -std=c23 -x c -c /dev/null -o /dev/null >/dev/null 2>/dev/null && echo "yes")

ifneq ($(HAS_C23_SUPPORT), yes)
    $(error The SH-2 compiler '$(CC)' does not have C23 support.  Please upgrade to GCC 14)
endif
ifneq ($(HAS_NATIVE_C23_SUPPORT), yes)
    $(error The native compiler '$(CC_NATIVE)' does not have C23 support.  Please upgrade to GCC 14)
endif

# -------------------------
# | Special build targets |
# -------------------------

.PHONY: all clean

# (targets for 'all' populated by rule generation below)
all: dfrc

clean:
	rm -rf $(BUILD_PATH)
	rm -f dfrc

dfrc: tools/dfrc/dfrc.c
	$(CC_NATIVE) $(CFLAGS_NATIVE) $< -o $@

# ---------------------------
# | Rule generation scripts |
# ---------------------------

define DEFINE_SRCS_AND_OBJS

$(1)_SRCS       := $$(call get_files_named,$(MOD_SRC_PATH),*.c)
$(1)_SRCS       += $$(call get_files_named,$(MOD_SRC_PATH),*.S)
$(MOD_SCN)_SRCS := $$(addprefix $(MOD_SRC_PATH)/,$$($(1)_SRCS))
$(MOD_SCN)_OBJS := $$(patsubst  $(MOD_SRC_PATH)/%, $(MOD_OBJ_PATH)/%.o, $$($(MOD_SCN)_SRCS))

endef

define DEFINE_OBJ_RULES

$(MOD_OBJ_PATH)/%.c.o: MOD      := $(1)
$(MOD_OBJ_PATH)/%.c.o: SCENARIO := $(2)
$(MOD_OBJ_PATH)/%.c.o: $(MOD_SRC_PATH)/%.c
	@mkdir -p $$(dir $$@)
	@echo .c.o: $$< =\> $$@
	@$(CC) $(CFLAGS) -DSCENARIO=$$(SCENARIO_VAL_$(2)) -c $$< -o $$@

$(MOD_OBJ_PATH)/%.S.o: MOD      := $(1)
$(MOD_OBJ_PATH)/%.S.o: SCENARIO := $(2)
$(MOD_OBJ_PATH)/%.S.o: $(MOD_SRC_PATH)/%.S
	@mkdir -p $$(dir $$@)
	@echo .S.o: $$< =\> $$@
	@$(CC) $(CFLAGS) -DSCENARIO=$$(SCENARIO_VAL_$(2)) -c $$< -o $$@

endef

define DEFINE_ELF_RULES

MOD_SCN_OBJS := $$(patsubst $(MOD_OBJ_PATH)/%,%,$$($(1)_$(2)_OBJS))
LD_OBJS      := $$(addprefix $(MOD_OBJ_PATH)/,$$($(1)_OBJS_$(3)) $$($(1)_OBJS_$(3)_$(2)))

$(MOD_ELF_PATH)/$(3).elf: MOD      := $(1)
$(MOD_ELF_PATH)/$(3).elf: SCENARIO := $(2)
$(MOD_ELF_PATH)/$(3).elf: MOD_SCN  := $(1)_$(2)
$(MOD_ELF_PATH)/$(3).elf: MOD_SCN_OBJS := $$(MOD_SCN_OBJS)
$(MOD_ELF_PATH)/$(3).elf: LD_OBJS  := $$(LD_OBJS)
$(MOD_ELF_PATH)/$(3).elf: $(MOD_LD_PATH)/$(3).ld $$(LD_OBJS)
	@mkdir -p $$(dir $$@)
	@echo .elf: $$< =\> $$@
	@if [ -z "$$(strip $$(LD_OBJS))" ]; then \
	    echo "Need to define $(1)_OBJS_$(3) or $(1)_OBJS_$(3)_$(2)"; \
	    exit 1; \
	fi
	@$(CC) $(LDFLAGS) -Wl,-Map=$(MOD_ELF_PATH)/$(3).map $$(LD_OBJS) -L$(MOD_LD_PATH) -L$(LIB_SF3_PATH)/ld/$(2) -T $$< -o $$@

$(MOD_SCN)_ELFS += $(MOD_ELF_PATH)/$(3).elf
ALL_ELFS        += $(MOD_ELF_PATH)/$(3).elf

endef

define DEFINE_BIN_RULES

$(MOD_BIN_PATH)/$(3).bin: MOD      := $(1)
$(MOD_BIN_PATH)/$(3).bin: SCENARIO := $(2)
$(MOD_BIN_PATH)/$(3).bin: $(MOD_ELF_PATH)/$(3).elf
	@mkdir -p $$(dir $$@)
	@echo .bin: $$< =\> $$@
	@$(OBJCOPY) -O binary $$< $$@

$(MOD_SCN)_BINS += $(MOD_BIN_PATH)/$(3).bin
ALL_BINS        += $(MOD_BIN_PATH)/$(3).bin

endef

define DEFINE_DFR_RULES

$(MOD_DFR_OUT_PATH)/$(3): MOD               := $(1)
$(MOD_DFR_OUT_PATH)/$(3): SCENARIO          := $(2)
$(MOD_DFR_OUT_PATH)/$(3): MOD_ELF_PATH      := $(MOD_ELF_PATH)
$(MOD_DFR_OUT_PATH)/$(3): MOD_BIN_PATH      := $(MOD_BIN_PATH)
$(MOD_DFR_OUT_PATH)/$(3): SF3_SCENARIO_PATH := $$(SF3_PATH_$(2))
$(MOD_DFR_OUT_PATH)/$(3): $(MOD_DFR_IN_PATH)/$(3).in $$($(MOD_SCN)_BINS) dfrc
	@mkdir -p $$(dir $$@)
	@echo .dfr: $$< =\> $$@
	@./dfrc $(basename game-files/$$(SCENARIO)/$(3)) $$< $$(MOD_ELF_PATH) > $$@.tmp || { rm $$@.tmp; exit 1; }
	@mv $$@.tmp $$@

ALL_DFRS += $(MOD_DFR_OUT_PATH)/$(3)

endef

# -------------------
# | Rule generation |
# -------------------

$(foreach mod,$(MODS), \
    $(eval MOD_SRC_PATH := $(MOD_PATH)/$(mod)/src) \
    $(eval $(mod)_SCENARIOS = $(filter-out src,$(notdir $(wildcard $(MOD_PATH)/$(mod)/*)))) \
    $(foreach scn,$($(mod)_SCENARIOS), \
        $(eval MOD_SCN          := $(mod)_$(scn)) \
        $(eval MOD_LD_PATH      := $(MOD_PATH)/$(mod)/$(scn)/ld) \
        $(eval MOD_DFR_IN_PATH  := $(MOD_PATH)/$(mod)/$(scn)/dfr) \
        \
        $(eval MOD_BUILD_PATH   := $(BUILD_PATH)/$(mod)/$(scn)) \
        $(eval MOD_OBJ_PATH     := $(MOD_BUILD_PATH)/obj) \
        $(eval MOD_ELF_PATH     := $(MOD_BUILD_PATH)/elf) \
        $(eval MOD_BIN_PATH     := $(MOD_BUILD_PATH)/bin) \
        $(eval MOD_DFR_OUT_PATH := $(MOD_BUILD_PATH)/dfr) \
        \
        $(eval $(MOD_SCN)_LDS   := $(call get_files,$(MOD_LD_PATH))) \
        $(eval $(MOD_SCN)_DFRS  := $(call get_files,$(MOD_DFR_IN_PATH))) \
        \
        $(eval $(call DEFINE_SRCS_AND_OBJS,$(mod),$(scn))) \
        $(eval $(call DEFINE_OBJ_RULES,$(mod),$(scn))) \
        $(foreach src,$($(mod)_SRCS), \
            $(eval ALL_OBJS += $(MOD_OBJ_PATH)/$(src).o) \
        ) \
        $(foreach ld,$($(MOD_SCN)_LDS), \
            $(eval $(call DEFINE_ELF_RULES,$(mod),$(scn),$(basename $(ld)))) \
            $(eval $(call DEFINE_BIN_RULES,$(mod),$(scn),$(basename $(ld)))) \
        ) \
        $(foreach dfr,$($(MOD_SCN)_DFRS), \
            $(eval $(call DEFINE_DFR_RULES,$(mod),$(scn),$(basename $(dfr)))) \
        ) \
    ) \
)

all: \
    ${sort $(ALL_OBJS)} \
    ${sort $(ALL_ELFS)} \
    ${sort $(ALL_BINS)} \
    ${sort $(ALL_DFRS)}

# Include auto-generated header dependencies.
-include $(shell find ./$(BUILD_PATH) -name "*.d" 2>/dev/null)

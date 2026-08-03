INCLUDE "x014_intern.ld"

INCLUDE "1st.ld"

SECTIONS
{
    /* New function for loading animations. */
    . = 0x06093da4;
    .loadBattleAnimationBin : {
        KEEP(*(.loadBattleAnimation))
    }

    . = 0x060988ec;
    .animationTable : {
        KEEP(*(.g_battleAnimationLookupData))
    }

    . = 0x06098d38;
    .getBattleAnimationInfoBin : {
        /* New function *after* the data. */
        KEEP(*(.getBattleAnimationInfo))
        . = ALIGN(4);

        /* ...There shouldn't be anything else, but this is necessary... */
        *(.text .text.*)
        . = ALIGN(4);
        *(.rodata .rodata.*)
        . = ALIGN(4);
        *(.data .data.*)
        . = ALIGN(4);
        *(.bss .bss.*)
    }

    /* Discard a bunch of irrelevant stuff. */
    /DISCARD/ : { *(.comment .note.* .rel.* .rela.*) }
}

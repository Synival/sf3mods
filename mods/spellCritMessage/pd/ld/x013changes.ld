INCLUDE "x013.ld"

INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"

SECTIONS
{
    . = 0x06081c40;
    .getSpellPowerAttackInnate : {
        KEEP(*(.getSpellPowerAttackInnate));
        KEEP(*(.getSpellPowerAttackInnateOrScripted));
        . = ALIGN(4);
    }

    . = 0x06081cd4;
    .getSpellPowerAttackScripted : {
        KEEP(*(.getSpellPowerAttackScripted));
        *(.text .text.*)
        . = ALIGN(4);
        *(.rodata .rodata.*)
        . = ALIGN(4);
        *(.bss .bss.*)
        . = ALIGN(4);
        *(.data .data.*)
        . = ALIGN(4);
    }

    /* Discard a bunch of irrelevant stuff. */
    /DISCARD/ : { *(.comment .note.* .rel.* .rela.*) }
}

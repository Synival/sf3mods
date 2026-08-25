INCLUDE "x013.ld"

INCLUDE "x002_extern.ld"

SECTIONS
{
    /* Replace applyAntidote() */
    . = 0x060851b8;

    .newCode : {
        KEEP(*(.applyAntidote));

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

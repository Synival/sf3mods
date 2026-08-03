INCLUDE "x014_intern.ld"

INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"

SECTIONS
{
    . = 0x0609a624;

    .patch : {
        KEEP(*(.initLighting))
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

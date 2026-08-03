INCLUDE "x014_intern.ld"

INCLUDE "1st.ld"
INCLUDE "x003_extern.ld"

SECTIONS
{
    . = 0x06098e58;

    .patch : {
        KEEP(*(.levelUpNew))
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

INCLUDE "1st.ld"
INCLUDE "x003_extern.ld"

SECTIONS
{
    . = 0x060f6194;

    .patch : {
        KEEP(*(.musicDebugMenu))
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

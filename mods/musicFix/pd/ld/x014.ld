INCLUDE "1st.ld"

SECTIONS
{
    . = 0x06088730;
    .newDebugWriteStaExpEndSection : {
        KEEP(*(.newDebugWriteStaExpEnd))
        . = ALIGN(2);
    }

    . = 0x06088784;
    .newCode : {
        KEEP(*(.new_FUN_06015018_call))
        . = ALIGN(4);
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

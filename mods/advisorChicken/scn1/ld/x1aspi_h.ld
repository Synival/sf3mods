INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"
INCLUDE "x008_extern.ld"
INCLUDE "x022_extern.ld"

/* Functions in X1ASPI_H.BIN */
_originalStartFunction       = 0x0605f148;
_talkToAdvisor               = 0x0605fbbc;
_c_scriptMakeSolidUnpushable = 0x06061340;

SECTIONS
{
    /* Replace renderDynamicModelInstanceGroup() */
    . = 0x06060964;

    .newCode : {
        KEEP(*(.newStartFunction));
        KEEP(*(.talkToAdvisorChicken));
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

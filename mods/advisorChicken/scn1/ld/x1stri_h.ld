INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"
INCLUDE "x008_extern.ld"
INCLUDE "x022_extern.ld"

/* Functions in X1STRI_H.BIN */
_originalStartFunction       = 0x0605f1e8;
_talkToAdvisor               = 0x0605f81c;
_c_scriptMakeSolidUnpushable = 0x0606119c;

SECTIONS
{
    /* Replace renderDynamicModelInstanceGroup() */
    . = 0x06060254;

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

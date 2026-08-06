INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"
INCLUDE "x008_extern.ld"
INCLUDE "x022_extern.ld"

/* Functions in X1RINJIN.BIN */
_originalStartFunction       = 0x0605f164;
_talkToAdvisor               = 0x0605fe7c;
_c_scriptMakeSolidUnpushable = 0x0606176c;

SECTIONS
{
    /* Replace renderDynamicModelInstanceGroup() */
    . = 0x06060c60;

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

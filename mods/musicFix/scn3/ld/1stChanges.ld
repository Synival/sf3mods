INCLUDE "1st.ld"

/* Internal functions, but only because we had to place X014 code into X001 */
INCLUDE "x014_intern.ld"

SECTIONS
{
    . = 0x0601055c;
    .newCatastrophicErrorCode : {
        KEEP(*(.catastrophicError_AddressError))
        KEEP(*(.catastrophicError_DmaAddressError))
        KEEP(*(.catastrophicError_GeneralUndefinedInstruction))
        KEEP(*(.catastrophicError_SlotUndefinedInstruction))
        KEEP(*(.catastrophicError_MatrixPushPopError))
        KEEP(*(.catastrophicError))
        KEEP(*(".waitThenUnjinglify"))

        . = ALIGN(4);
        *(.text .text.*)
        . = ALIGN(4);
        *(.rodata .rodata.*)
        . = ALIGN(4);
        *(.data .data.*)
        . = ALIGN(4);
        *(.bss .bss.*)
    }

    . = 0x060106cc;
    .newPreBattleMusicCmdsSection : {
        KEEP(*(.newPreBattleMusicCmds))
    }

    . = 0x0601293c;
    .newRunMusicCommand : {
        KEEP(*(.scn3RunMusicCommand))
    }


    /* Discard a bunch of irrelevant stuff. */
    /DISCARD/ : { *(.comment .note.* .rel.* .rela.*) }
}

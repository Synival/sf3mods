INCLUDE "x014_intern.ld"

INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"

SECTIONS
{
    /* We're writing stuff all over the place in X014.BIN, so this script lays out
     * the memory to match the file for simplicity's sake. */

    /* Ensure the .BIN file starts with zeroes. */
    . = 0x06088000;
    .anchor : { BYTE(0) }

    /* End of bcmd_0x1b() */
    . = 0x0608ab68;
    .replaceEndOfBCmd0x1b : {
        KEEP(*(.bcmd0x1bEndJump))
    }

    /* Replace a specific function with a new (and smaller) version. */
    . = 0x0608d628;
    .replaceGetScreenDistForAttack : {
        KEEP(*(.getScreenDistForAttack))
        KEEP(*(.updatedBCmd0x1bEnd))
    }

    /* Replace the now-unused camera functions. */
    . = 0x0608d7b0;
    .replaceOldCameraFuncs : {
        KEEP(*(.updatedRunAttackFrameLoop))
        KEEP(*(.camFuncCam1Near))
        KEEP(*(.camFuncCam1Far))
        KEEP(*(.camFuncCam3Near))
    }

    /* All the rest of our new code, which goes in the memory cleared-up by the
     * compressed animation table from "Mod Essentials". */
    . = 0x06099ea0;
    .codeAndDataInFreedUpMemoryBlock : {
        KEEP(*(.cameraAssign))
        KEEP(*(.isFarAttackFromPolyCharAttacker))
        KEEP(*(.camFuncCam2))
        KEEP(*(.camFuncCam3Far))
        *(.text .text.*)
        . = ALIGN(4);
        *(.rodata .rodata.*)
        . = ALIGN(4);
        *(.data .data.*)
        . = ALIGN(4);
        *(.bss .bss.*)
        . = ALIGN(4);
    }

    /* Discard a bunch of irrelevant stuff. */
    /DISCARD/ : { *(.comment .note.* .rel.* .rela.*) }
}

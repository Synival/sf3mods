INCLUDE "x013.ld"

INCLUDE "x002_extern.ld"
INCLUDE "x012_extern.ld"
INCLUDE "x1_extern.ld"

SECTIONS
{
    . = 0x06081928;
    .getHeightBonusProbablyDamagePercentBoost : {
        /* Replaces getHeightBonusProbablyDamagePercentBoost() */
        KEEP(*(.multiplyDamageByWeaponElementPower));
        KEEP(*(.c_elementalWeapons));

        *(.text .text.*)
        . = ALIGN(4);
        *(.rodata .rodata.*)
        . = ALIGN(4);
        *(.bss .bss.*)
        . = ALIGN(4);
        *(.data .data.*)
        . = ALIGN(4);
    }

    . = 0x06081e0c;
    .getBaseAttackDamage : {
        KEEP(*(.getBaseAttackDamage));
        . = ALIGN(4);
    }

    /* Discard a bunch of irrelevant stuff. */
    /DISCARD/ : { *(.comment .note.* .rel.* .rela.*) }
}

INCLUDE "x013.ld"

INCLUDE "1st.ld"
INCLUDE "x002_extern.ld"
INCLUDE "x012_extern.ld"
INCLUDE "x1_extern.ld"

ASSERT(_g_currentVictimUnitID - _g_attackerUnitID == 0x14,
       "g_currentVictimUnitID must be +0x14 ahead of g_attackerUnitID");

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

    . = 0x06081c20;
    .getSpellPowerAttackInnate : {
        KEEP(*(.getSpellPowerAttackInnate));
        KEEP(*(.getSpellPowerAttackInnateOrScripted));
        . = ALIGN(4);
    }

    . = 0x06081cb4;
    .getSpellPowerAttackScripted : {
        KEEP(*(.getSpellPowerAttackScripted));
        KEEP(*(.scaleByElementAndApplyPiercingHook));
        KEEP(*(.multiplyDamageByWeaponElementPowerForSpecial));
        . = ALIGN(4);
    }

    /* Discard a bunch of irrelevant stuff. */
    /DISCARD/ : { *(.comment .note.* .rel.* .rela.*) }
}

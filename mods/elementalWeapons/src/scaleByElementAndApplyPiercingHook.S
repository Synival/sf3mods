# Replacement function for getDefPiercingBonus() that also applies weapon elemental power
.section .scaleByElementAndApplyPiercingHook
.global _scaleByElementAndApplyPiercingHook

# r4 = special ID
# r8 = damage calculated so far. This is luckily in the same register on all four discs.
_specialCalcHook:
    sts.l      pr,@-r15
    mov.l      r4,@-r15
    mov.l      r8,@-r15

    # Run a function that scales damage based
    mov.l      func_multiplyDamageByWeaponElementPowerForSpecial,r0
    jsr        @r0
    # (r4 is already the specialId)
    mov        r15,r5
    mov.l      @r15+,r8

    # Apply armor piercing after adjusting for elemental damage.
    mov.l      func_getDefPiercingBonus,r0
    jsr        @r0
    mov.l      @r15+,r4

    # Done.
    lds.l      @r15+,pr
    rts
    nop

# Data
.balign 4
func_multiplyDamageByWeaponElementPowerForSpecial: # specialId, &damage
    .long _multiplyDamageByWeaponElementPowerForSpecial
func_getDefPiercingBonus: # specialId
    .long _getDefPiercingBonus

#include <sf3/x013.h>

#if SCENARIO == 1
#include <sf3/1st.h>
#endif

#include <sf3/x002.h>

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".getSpellPowerAttackInnateOrScripted")]]
int32_t getSpellPowerAttackInnateOrScripted(
    int32_t spellId, int32_t spellLv, bool withFriendship, int32_t victimId
) {
    const spell_t *spell = getSpell(spellId);
    const battleUnit_t *victim = getUnit(victimId);

    // Get power multilier based on resistance (as a percentage)
    int magicPow = 100 - victim->state.magicRes[spell->element];

    // Friendship isn't considered for scripted magic attacks like special boss abilities.
    if (withFriendship)
        magicPow -= getCurrentFriendshipStatBoost(victimId, FBONUS_MAGIC_RES);

    // Cap at [0%, 200%].
    if (magicPow > 200)
        magicPow = 200;
    else if (magicPow < 0)
        magicPow = 0;

    int32_t power = (spell->levels[spellLv].power * magicPow) / 100;

#if SCENARIO == 1
    // Summons + X-Laser
    if ((spellId >= 0x26 && spellId < 0x2a) || spellId == 0x2d)
        power = divSigned(power, g_battleTurnAction->numVictims);
#endif

    return power;
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".getSpellPowerAttackInnate")]]
int getSpellPowerAttackInnate(int32_t spellId, int32_t spellLv, int32_t /*attackerId*/, int32_t victimId) {
    return getSpellPowerAttackInnateOrScripted(spellId, spellLv, /*withFriendship =*/ true, victimId);
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".getSpellPowerAttackScripted")]]
int getSpellPowerAttackScripted(int32_t spellId, int32_t spellLv, int32_t /*attackerId*/, int32_t victimId) {
    return getSpellPowerAttackInnateOrScripted(spellId, spellLv, /*withFriendship =*/ false, victimId);
}


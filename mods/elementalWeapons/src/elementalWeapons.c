#include <sf3/x013.h>

#include <sf3/1st.h>
#include <sf3/x002.h>
#include <sf3/x012.h>
#include <sf3/x1.h>

// --------------------------------------------------------------------------------------------------------------------

// Each item in the elemental weapon table is a 16-bit value with an item ID and an element.
// The item ID is the upper 12 bits (0xFFF0).
// The element is the lower 4 bits (0x000F).

#define ITEM_ID_WITH_ELEMENT(id, element) \
    ((uint16_t) ((uint16_t) ((id) << 4) | (uint16_t) ((element) & (uint16_t) 0x000F)))

#define GET_ITEM_ID_FROM_ITEM_ELEMENT_PAIR(pair) \
    ((uint16_t) ((uint16_t) (pair) >> 4))

#define GET_ELEMENT_FROM_ITEM_ELEMENT_PAIR(pair) \
    ((element_e8) ((uint16_t) (pair) & (uint16_t) 0x000F))

// All elemental weapons defined here.
alignas(4) const uint16_t c_elementalWeapons[] = {
    /* 1-10 */
    ITEM_ID_WITH_ELEMENT(0x078 /*Phoenix Sword*/, ELEMENT_FIRE),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,

    /* 11-20 */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,

    /* 21-30 */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,

    /* 31-37 */
    0,
    0,
    0,
    0,
    0,
    0,
    0,

    // Must always end with zero
    0,
};

// --------------------------------------------------------------------------------------------------------------------

static const battleMap_t *g_battleMap = (void *) 0x060b6000;

// --------------------------------------------------------------------------------------------------------------------

// Detects if the attacker's weapon is an elemental one. If so, 50% of the victim's magic resistance to that element is
// applied to the damage referenced. The result is a 50% boost for resistance of -100 and a 50% penalty for resistance
// of +100.
[[gnu::section(".multiplyDamageByWeaponElementPower")]]
void multiplyDamageByWeaponElementPower(
    const battleUnit_t *attacker, const battleUnit_t *victim, int32_t *damage, uint8_t baseline
) {
    // Don't bother if there's no weapon.
    const uint16_t weapon = attacker->weapon & 0x01FF;
    if (weapon == 0)
        return;

    // Is the weapon one of the elemental weapons?
    const uint16_t *ew = c_elementalWeapons;
    while (GET_ITEM_ID_FROM_ITEM_ELEMENT_PAIR(*ew) != weapon) 
        if (*(ew++) == 0)
            return;

    // Get and return the amount of damage the attack should do as a percentage.
    element_e8 element = GET_ELEMENT_FROM_ITEM_ELEMENT_PAIR(*ew);
    int32_t mult = baseline - victim->state.magicRes[element];
    *damage = divSigned(*damage * mult, baseline);
}

// --------------------------------------------------------------------------------------------------------------------

// Original base damage formula modified to apply elemental power (if applicable).
// Elemental power is applied to the base attack value (including partnership bonus) before defense, land effect, or
// effectiveness bonuses are considered.
[[gnu::section(".getBaseAttackDamage")]]
int32_t getBaseAttackDamage(int32_t attackerId, int32_t victimId) {
  battleUnit_t *victim   = getUnit(victimId);
  battleUnit_t *attacker = getUnit(attackerId);

  int32_t atk = attacker->state.attack;
  int32_t def = victim->state.defense;

  int32_t atkBonus = getCurrentFriendshipStatBoost(attackerId, FBONUS_ATK);
  int32_t defBonus = getCurrentFriendshipStatBoost(victimId, FBONUS_DEF);
  int32_t alsoDef  = getCurrentFriendshipStatBoost(victimId, FBONUS_MAYBE_DEF_BUT_SAYS_MAGIC_RES_LUCK);

  // Calculate base attack and apply elemental bonuses if applicable.
  int32_t damage = atkBonus + atk;
  multiplyDamageByWeaponElementPower(attacker, victim, &damage, 200); // New!

  // Reduce base damage by enemy defense.:w
  damage -= (def + defBonus + alsoDef);

  // Time to apply land effect!
  // If you do the math here, land effect is scaled down from 15/30% to 10/20%. Lame!
  terrain_e16 terrain = getTileTerrainType(g_battleMap, victim->x, victim->y);

  // In Scenario 1, this function is in X012.BIN. From Scenario 2 onward, it's in X1*.BIN.
#if SCENARIO == 1
  int32_t landEffectPercent = getLandEffectPercent(victimId, terrain); // 0, 15, or 30
#else
  int32_t landEffectPercent = x1_getLandEffectPercent(victimId, terrain); // 0, 15, or 30
#endif

  damage = (damage * (10 - landEffectPercent / 0xf)) / 10;

  // Make sure damage is capped.
  if (damage < 1)
    damage = 1;

  // Add effectivenes bonuses last.
  int32_t effectivenessBonus = getAttackEffectivenessPower(attackerId, victimId);
  g_effectivenessBonus = (int8_t) effectivenessBonus;

  return damage + effectivenessBonus;
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".multiplyDamageByWeaponElementPowerForSpecial")]]
void multiplyDamageByWeaponElementPowerForSpecial(int32_t low, int32_t *damage) {
    // Only if special doen't have a 'low' value of 100 (dec), which indicates an elemental attack.
    if (low == 100)
        return;

#if 0
    // Little hack to avod supplying `g_currentVictimID`, which is exacty 0x14 bytes ahead.
    // GCC can't optimize for this, but we can! Just be careful...
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
    const uint8_t *addr = (const uint8_t *) &g_attackerUnitID;
    const int32_t attackerId = *(const int32_t *) addr;
    const int32_t victimId   = *(const int32_t *) (addr + 0x14);
#pragma GCC diagnostic pop
    const battleUnit_t *attacker = getUnit(attackerId);
    const battleUnit_t *victim   = getUnit(victimId);
#endif

    const battleUnit_t *attacker = getUnit(g_attackerUnitID);
    const battleUnit_t *victim   = getUnit(g_currentVictimUnitID);

    multiplyDamageByWeaponElementPower(attacker, victim, damage, 100);
}

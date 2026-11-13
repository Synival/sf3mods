#include <sf3/x013.h>

#include <sf3/x002.h>
#include <sf3/x012.h>
#include <sf3/x1.h>

// --------------------------------------------------------------------------------------------------------------------

#define ITEM_ID_WITH_ELEMENT(id, element) \
    ((uint16_t) ((uint16_t) (id << 4) | (uint16_t) (element & 0x0F)))

alignas(4) const uint16_t c_elementalWeapons[] = {
    ITEM_ID_WITH_ELEMENT(0x078 /*Phoenix Sword*/, ELEMENT_FIRE),

    // For future use
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

[[gnu::section(".multiplyDamageByWeaponElementPower")]]
void multiplyDamageByWeaponElementPower(battleUnit_t *attacker, battleUnit_t *victim, int32_t *damage) {
    // Don't bother if there's no weapon.
    const uint16_t weapon = attacker->weapon;
    if (weapon == 0)
        return;

    // Is the weapon one of the elemental weapons?
    const uint16_t *ew = c_elementalWeapons;
    while ((*ew >> 4) != weapon) 
        if (*(ew++) == 0)
            return;

    // Get and return the amount of damage the attack should do as a percentage.
    element_e8 element = (element_e8) (*ew & 0x0F);
    int32_t mult = 201 - victim->state.magicRes[element]; // (201 because 200 won't compile for reasons)
    *damage = (*damage * mult) / 201;
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".getBaseAttackDamage")]]
int32_t getBaseAttackDamage(int32_t attackerId, int32_t victimId) {
  battleUnit_t *victim   = getUnit(victimId);
  battleUnit_t *attacker = getUnit(attackerId);

  int32_t atk = attacker->state.attack;
  int32_t def = victim->state.defense;

  int32_t atkBonus = getCurrentFriendshipStatBoost(attackerId, FBONUS_ATK);
  int32_t defBonus = getCurrentFriendshipStatBoost(victimId, FBONUS_DEF);
  int32_t alsoDef  = getCurrentFriendshipStatBoost(victimId, FBONUS_MAYBE_DEF_BUT_SAYS_MAGIC_RES_LUCK);

  int32_t damage = atkBonus + atk;
  multiplyDamageByWeaponElementPower(attacker, victim, &damage); // New!

  damage -= (def + defBonus + alsoDef);

  // Uhh, if you do the math here, land effect is scaled down from 15/30% to 10/20%. Lame!
  terrain_e16 terrain = getTileTerrainType(g_battleMap, victim->x, victim->y);
  int32_t landEffectPercent = x1_getLandEffectPercent(victimId, terrain); // 0, 15, or 30
  damage = (damage * (10 - landEffectPercent / 0xf)) / 10;
  if (damage < 1)
    damage = 1;

  int32_t effectivenessBonus = getAttackEffectivenessPower(attackerId, victimId);
  g_effectivenessBonus = (int8_t) effectivenessBonus;

  return damage + effectivenessBonus;
}

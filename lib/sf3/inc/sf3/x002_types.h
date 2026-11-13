#ifndef INCLUDED_SF3_X002_TYPES_H
#define INCLUDED_SF3_X002_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

#include <stddef.h>

// --------------------------------------------------------------------------------------------------------------------

typedef struct _battleUnitState_t {
    int16_t direction;
    int16_t currentHP;
    uint8_t currentMP;
    uint8_t attack;
    uint8_t defense;
    uint8_t agility;
    uint8_t mov;
    uint8_t luck;
    uint8_t turns;
    uint8_t hpRegen;
    uint8_t mpRegen;
    int8_t magicRes[8];
    uint8_t exp;
    uint8_t controlType;
    uint8_t teamId;
    uint8_t mapId;
    uint8_t isAlive;
    uint8_t magicBarrier;
    uint8_t resistTurns;
    uint8_t attackTurns;
    int8_t  slowSupportTurns;
    uint8_t sleepTurns;
    uint8_t confusedTurns;
    uint8_t illusionTurns;
    uint8_t silencedTurns;
    uint8_t paralyzedTurns;
    uint8_t poisonedTurns;
    uint8_t charmedTurns;
    uint8_t skippedTurns;
    uint8_t cursedTurns;
    uint8_t chantTurns;
    uint8_t berserkTurns;
    uint8_t frozenTurns;
    uint8_t critRate;
    uint8_t counterBonus;
    uint8_t tempRegen;
    uint8_t equippedWeaponLow;
    uint8_t extraSpecialAttack;
    uint8_t lastAttacker;
} battleUnitState_t;

static_assert(sizeof(battleUnitState_t) == 0x30);

typedef struct _weaponInfo_t {
    int8_t weaponType;
    int8_t weaponLevel;
    int16_t wexp;
} weaponInfo_t;

typedef struct _battleUnit_t {
    uint8_t           turnsUntilRespawn;     // 0x00
    uint8_t           turnsTaken;            // 0x01
    uint8_t           unknownBytes_0x03[0x0d]; // 0x02
    uint8_t           gender;                // 0x0f
    uint16_t          maxHP;                 // 0x10
    uint8_t           maxMP;                 // 0x12
    uint8_t           level;                 // 0x13
    uint8_t           baseAttack;            // 0x14
    uint8_t           baseDefense;           // 0x15
    uint8_t           baseAgility;           // 0x16
    uint8_t           baseMov;               // 0x17
    uint8_t           baseLuck;              // 0x18
    uint8_t           baseTurns;             // 0x19
    uint8_t           baseHPRegen;           // 0x1a
    uint8_t           baseMPRegen;           // 0x1b
    uint8_t           baseRes[8];            // 0x1c
    spellIdLevel_t    spells[4];             // 0x24
    uint16_t          weapon;                // 0x2c
    uint16_t          accessory;
    uint16_t          items[4];
    uint8_t           specials[10];
    uint8_t           unknown0x42;
    uint8_t           unknown0x43;
    uint8_t           intelligence;
    uint8_t           flags;
    uint8_t           isObject;
    uint8_t           timesSpawned;
    uint16_t          gold;
    uint16_t          dropItem;
    uint16_t          dropDisableRate;
    uint8_t           slowPlus;
    uint8_t           supportPlus;
    uint8_t           magicBonusId;
    uint8_t           movementType;
    uint8_t           orderMode;
    uint8_t           attackChoiceMode;
    uint8_t           attackChoices[6];
    uint8_t           weaponEqTypes[8];
    weaponInfo_t      weaponLevels[4];
    uint8_t           unknown0x72;
    uint8_t           unknown0x73;
    uint32_t          aiState_t;
    uint8_t           enemyOrClassId;
    uint8_t           timesKilled;
    uint16_t          unitsKilled;
    uint8_t           x;
    uint8_t           verticalY;
    uint8_t           y;
    uint8_t           unknown0x7f;
    battleUnitState_t state;
} battleUnit_t;

static_assert(offsetof(battleUnit_t, unknown0x42)    == 0x42);
static_assert(offsetof(battleUnit_t, attackChoices)  == 0x54);
static_assert(offsetof(battleUnit_t, weaponEqTypes)  == 0x5a);
static_assert(offsetof(battleUnit_t, weaponLevels)   == 0x62);
static_assert(offsetof(battleUnit_t, unknown0x72)    == 0x72);
static_assert(offsetof(battleUnit_t, enemyOrClassId) == 0x78);
static_assert(offsetof(battleUnit_t, state)          == 0x80);
static_assert(sizeof(battleUnit_t) == 0xb0);

typedef struct _item_t {
    uint16_t price;
    uint8_t  weaponEqType;
    uint8_t  effectsEquipType;
    uint8_t  requirements;
    uint8_t  range;
    uint8_t  attack;
    uint8_t  defense;
    uint8_t  attackRank;
    uint8_t  spellRank;
    uint16_t effectives[2];
    uint16_t stats[4];
    uint8_t  useSpellId;
    uint8_t  useSpellLevel;
} item_t;

static_assert(sizeof(item_t) == 0x18);

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_SF3_X002_TYPES_H

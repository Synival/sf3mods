#ifndef INCLUDED_SF3_COMMON_H
#define INCLUDED_SF3_COMMON_H

// --------------------------------------------------------------------------------------------------------------------

// Must be included before everything else.
#include "config.h"

#include "sgl_types.h"

// --------------------------------------------------------------------------------------------------------------------

typedef uint16_t color_t;

typedef void(voidFunc_f)();

// --------------------------------------------------------------------------------------------------------------------

// TODO: Add everything, for multiple scenarios!
enum {
    MONSTER_GOLEM      = 0x1F,
    MONSTER_QUEEN_WORM = 0x68,
    MONSTER_TITAN      = 0x6A,
};

typedef uint16_t monster_e16;
typedef uint32_t monster_e32;

// --------------------------------------------------------------------------------------------------------------------

// TODO: This is only for the PD, please update!
enum {
    SPELL_INVALID                = -1,
    SPELL_NONE                   = 0x00,
    SPELL_BLAZE                  = 0x01,
    SPELL_FREEZE                 = 0x02,
    SPELL_SPARK                  = 0x03,
    SPELL_TORNADO                = 0x04,
    SPELL_SOUL_STEAL             = 0x05,
    SPELL_INFERNO                = 0x06,
    SPELL_SUPPORT                = 0x07,
    SPELL_SLOW                   = 0x08,
    SPELL_SHINING                = 0x09,
    SPELL_RESIST                 = 0x0a,
    SPELL_ATTACK                 = 0x0b,
    SPELL_DISPEL                 = 0x0c,
    SPELL_CONFUSE                = 0x0d,
    SPELL_SLEEP                  = 0x0e,
    SPELL_CHARM                  = 0x0f,
    SPELL_DRAIN                  = 0x10,
    SPELL_HEAL                   = 0x11,
    SPELL_AURA                   = 0x12,
    SPELL_CHANT                  = 0x13,
    SPELL_ANTIDOTE               = 0x14,
    SPELL_RETURN                 = 0x15,
    SPELL_HEAL_ITEM              = 0x16,
    SPELL_MP_HEAL_ITEM           = 0x17,
    SPELL_STATUS_HEAL_ITEM       = 0x18,
    SPELL_ANGEL_WING             = 0x19,
    SPELL_RAISE1                 = 0x1a,
    SPELL_RAISE2                 = 0x1b,
    SPELL_RAISE3                 = 0x1c,
    SPELL_LEVEL_UP               = 0x1d,
    SPELL_BREATH_OF_FIRE         = 0x1e,
    SPELL_BREATH_OF_ICE          = 0x1f,
    SPELL_BREATH_OF_THUNDER      = 0x20,
    SPELL_NEGATIVE_FLASH         = 0x21,
    SPELL_BREATH_OF_DEMON        = 0x22,
    SPELL_BREATH_OF_WATER        = 0x23,
    SPELL_BREATH_OF_ACID         = 0x24,
    SPELL_CONJURE_CHAOS          = 0x25,
    SPELL_PHOENIX                = 0x26,
    SPELL_WENDIGO                = 0x27,
    SPELL_TIAMAT                 = 0x28,
    SPELL_THANATOS               = 0x29,
    SPELL_RAGE_INCREASE_ATTACK   = 0x2a,
    SPELL_MEAT                   = 0x2b,
    SPELL_ELBESEM_ORB            = 0x2c,
    SPELL_TITAN_LASER            = 0x2d,
    SPELL_TITAN_PUNCH            = 0x2e,
    SPELL_TITAN_ATTACK           = 0x2f,
    SPELL_PANIC_AND_CONFUSION    = 0x30,
    SPELL_VIOLENTLY_SHAKE_GROUND = 0x31,
    SPELL_BOULDER                = 0x32,
    SPELL_DIVINE_CANE_USE        = 0x33,
    SPELL_THOR                   = 0x34,
    SPELL_ZEPHYRUS               = 0x35,
    SPELL_GOLEM                  = 0x36,
    SPELL_HELL_DRAGON            = 0x37,
    SPELL_BREATH_WITH_BUBBLES    = 0x38,
    SPELL_INK                    = 0x39,
    SPELL_TAMED                  = 0x3a,
    SPELL_GOLDEN_BEAK            = 0x3b,
    SPELL_CORE_MAGIC             = 0x3c,
    SPELL_WALCURAY_ATTACK        = 0x3d,
    SPELL_PROSERPINA             = 0x3e,
    SPELL_DEMON_KING             = 0x3f,
    SPELL_SUMMON_PENKO           = 0x40,
    SPELL_SUMMON_PENN            = 0x41,
    SPELL_CANNON                 = 0x42,
    SPELL_WIND_STORM             = 0x43,
    SPELL_BLIZZARD               = 0x44,
    SPELL_DEADLY_ICE_STORM       = 0x45,
    SPELL_BLESSING               = 0x46,
    SPELL_CHAOS_GATE             = 0x47,
    SPELL_WALCURAY_LASER         = 0x48,
    SPELL_BLESSING_ATTACK        = 0x49,
    SPELL_EXHALE_EVIL_AIR        = 0x4a,
    SPELL_EVIL_BEAM              = 0x4b,
    SPELL_POISON_AND_WIND        = 0x4c,
};

typedef uint8_t  spellId_e8;
typedef uint16_t spellId_e16;
typedef uint32_t spellId_e32;

// --------------------------------------------------------------------------------------------------------------------

typedef struct _spellIdLevel_t {
    spellId_e8 spellId;
    int8_t level;
} spellIdLevel_t;

typedef struct _levelUpInfo_t {
    int16_t newLevel;
    int16_t spellSlotLeveled;
    int16_t hpGain;
    int16_t mpGain;
    int16_t atkGain;
    int16_t defGain;
    int16_t agiGain;
} levelUpInfo_t;

typedef struct _palette0x20_t {
    color_t colors[0x20];
} palette0x20_t;

// --------------------------------------------------------------------------------------------------------------------

#endif  // #ifndef INCLUDED_SF3_COMMON_H

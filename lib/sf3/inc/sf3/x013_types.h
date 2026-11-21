#ifndef INCLUDED_X013_TYPES_H
#define INCLUDED_X013_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

#include <stddef.h>

// --------------------------------------------------------------------------------------------------------------------

enum {
    BCMD_DONE                        = -1,
    BCMD_WAIT_FRAMES                 = 0x00,
    BCMD_MAYBE_START_ATTACK          = 0x01,
    BCMD_PLAY_SOUND                  = 0x02,
    BCMD_TRY_GAIN_LEVEL              = 0x03,
    BCMD_SET_CAM_MODE                = 0x04,
    BCMD_0x05                        = 0x05,
    BCMD_0x06                        = 0x06,
    BCMD_0x07                        = 0x07,
    BCMD_0x08                        = 0x08,
    BCMD_FINISH_COMBAT               = 0x09,
    BCMD_CACHE_UNIT_MODEL            = 0x0a,
    BCMD_0x0b                        = 0x0b,
    BCMD_MAYBE_STOP                  = 0x0c,
    BCMD_0x0d                        = 0x0d,
    BCMD_0x0e_DUMMY                  = 0x0e,
    BCMD_0x0f_DUMMY                  = 0x0f,
    BCMD_0x10_DUMMY                  = 0x10,
    BCMD_0x11_DUMMY                  = 0x11,
    BCMD_0x12_DUMMY                  = 0x12,
    BCMD_0x13_DUMMY                  = 0x13,
    BCMD_0x14_DUMMY                  = 0x14,
    BCMD_0x15_DUMMY                  = 0x15,
    BCMD_0x16_ON_MAGIC_BARRIER       = 0x16,
    BCMD_0x17_ON_IMMUNE              = 0x17,
    BCMD_0x18                        = 0x18,
    BCMD_SHOW_HURT                   = 0x19,
    BCMD_APPLY_DEATH_EFFECT_AND_WAIT = 0x1a,
    BCMD_DEAL_DAMACE                 = 0x1b,
    BCMD_REDUCE_MAGIC                = 0x1c,
    BCMD_0x1d_DUMMY                  = 0x1d,
    BCMD_MESSAGE_IF_SETTING_ON       = 0x1e,
    BCMD_MESSAGE_ALWAYS              = 0x1f,
    BCMD_0x20_HAPPENS_AT_END_A_LOT   = 0x20,
    BCMD_RESET_MESSAGE_VAR           = 0x21,
    BCMD_PUSH_MSG_NUMBER             = 0x22,
    BCMD_PUSH_MSG_CLASS_ID           = 0x23,
    BCMD_PUSH_MSG_UNIT_ID            = 0x24,
    BCMD_PUSH_MSG_SPELL_ID           = 0x25,
    BCMD_PUSH_MSG_ITEM_ID            = 0x26,
    BCMD_0x27                        = 0x27,
    BCMD_CHANGE_HP                   = 0x28,
    BCMD_CHANGE_MP                   = 0x29,
    BCMD_CHANGE_MAX_HP               = 0x2a,
    BCMD_CHANGE_MAX_MP               = 0x2b,
    BCMD_0x2c_DUMMY                  = 0x2c,
    BCMD_0x2d_DUMMY                  = 0x2d,
    BCMD_0x2e_DUMMY                  = 0x2e,
    BCMD_0x2f_DUMMY                  = 0x2f,
    BCMD_PUSH_MSG_SPECIAL_ID         = 0x30,
    BCMD_PUSH_MSG_PARTNER_LV         = 0x31,
    BCMD_0x32_DUMMY                  = 0x32,
    BCMD_SET_RESIST_TURNS            = 0x33,
    BCMD_SET_ATTACK_TURNS            = 0x34,
    BCMD_SET_SLOW_SUPPORT_TURNS      = 0x35,
    BCMD_REMOVE_SLEEP                = 0x36,
    BCMD_REMOVE_CONFUSE              = 0x37,
    BCMD_REMOVE_ILLUSION             = 0x38,
    BCMD_REMOVE_SILENCE              = 0x39,
    BCMD_REMOVE_PARALYSIS            = 0x3a,
    BCMD_REMOVE_POISON               = 0x3b,
    BCMD_REMOVE_CHARM                = 0x3c,
    BCMD_REMOVE_BERSERK              = 0x3d,
    BCMD_SET_CHANT_TURNS             = 0x3e,
    BCMD_SET_BERSERK_TURNS           = 0x3f,
    BCMD_SET_FROZEN_TURNS            = 0x40,
    BCMD_LAST                        = 0x41,
};

typedef uint8_t  battleCmd_e8;
typedef uint16_t battleCmd_e16;
typedef uint32_t battleCmd_e32;

// --------------------------------------------------------------------------------------------------------------------

enum {
    TURN_ACTION_FAILED      = -1,
    TURN_ACTION_ATTACK      =  0,
    TURN_ACTION_CAST        =  1,
    TURN_ACTION_USE_ITEM    =  2,
    TURN_ACTION_USE_WEAPON  =  3,
    TURN_ACTION_CONFUSED    =  4,
    TURN_ACTION_GIVE        = 91,
    TURN_ACTION_DROP        = 92,
    TURN_ACTION_FIRE_CANNON = 93,
    TURN_ACTION_MAP_MOVE    = 95,
    TURN_ACTION_TALK        = 96,
    TURN_ACTION_EGRESS      = 97,
    TURN_ACTION_INSPECT     = 98,
    TURN_ACTION_STAY        = 99,
};

typedef uint8_t  turnAction_e8;
typedef uint16_t turnAction_e16;
typedef uint32_t turnAction_e32;

// --------------------------------------------------------------------------------------------------------------------

typedef struct _turnAction_t {
    turnAction_e16 order;
    int16_t        arg1;
    int16_t        arg2;
    int16_t        numVictims;
    int16_t        victimIds[64];
} turnAction_t;

static_assert(sizeof(turnAction_t) == 0x88);

// --------------------------------------------------------------------------------------------------------------------

typedef struct _specialAttack_t {
    uint8_t type;
    uint8_t lowPow;
    uint8_t midPow;
    uint8_t highPow;
} specialAttack_t;

static_assert(sizeof(specialAttack_t) == 0x04);

#endif // #ifndef INCLUDED_X013_TYPES_H

#ifndef INCLUDED_SF3_X014_TYPES_H
#define INCLUDED_SF3_X014_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

#include <stddef.h>

// --------------------------------------------------------------------------------------------------------------------

enum {
    CAMTARGET_MANUAL   = -1,
    CAMTARGET_ATTACKER = 0,
    CAMTARGET_VICTIM   = 1,
    CAMTARGET_FRONT    = 2,
    CAMTARGET_BACK     = 3,
    CAMTARGET_BOTH     = 4,
};

typedef int8_t  camTarget_e8;
typedef int16_t camTarget_e16;
typedef int32_t camTarget_e32;

enum {
    CAMMODE_MANUAL                         = -0x01,
    CAMMODE_SIDE_VIEW_LOCK_AND_ADJUST_ROTX = 0x00,
    CAMMODE_SIDE_VIEW                      = 0x01,
    CAMMODE_SIDE_VIEW_ADJUST_ROTX          = 0x02,
    CAMMODE_ATTACKER_ROTY_NEG0x4000        = 0x14,
    CAMMODE_ATTACKER_ROTY_0x1555           = 0x15,
    CAMMODE_VICTIM_ROTY_0x1555             = 0x29,
    CAMMODE_SPIN_AROUND                    = 0x64,
};

typedef int8_t  camMode_e8;
typedef int16_t camMode_e16;
typedef int32_t camMode_e32;

enum {
    PCPOS_BBOX_CENTER = 0,
    PCPOS_CHEST       = 1,
    PCPOS_HEAD        = 2,
};

typedef uint8_t  polyCharPos_e8;
typedef uint16_t polyCharPos_e16;
typedef uint32_t polyCharPos_e32;

enum {
    ANIM_NONE         = -0x01,
    ANIM_IDLE         = 0x00,
    ANIM_HURT         = 0x10,
    ANIM_BLOCK        = 0x20,
    ANIM_ATTACK_CLOSE = 0x30,
    ANIM_MAGIC        = 0x40,
    ANIM_ITEM         = 0x50,
    ANIM_ATTACK_FAR   = 0x60,
    ANIM_COUNTER      = 0x70,
    ANIM_SPECIAL_1    = 0x80,
    ANIM_SPECIAL_2    = 0x90,
    ANIM_SPECIAL_3    = 0xa0,
    ANIM_DEATH        = 0xe0,
    ANIM_SPECIAL_4    = 0xf0,
    ANIM_EXTRA_1      = 0xf1,
};

// Don't use 8-bit value if you can help it; signedness is a big issue.
typedef int16_t animId_e16;
typedef int32_t animId_e32;

enum {
    WEAPONRANGE_CLOSE         = 0,
    WEAPONRANGE_CLOSE_AND_FAR = 1,
    WEAPONRANGE_FAR           = 2,
};

typedef uint8_t  weaponRange_e8;
typedef uint16_t weaponRange_e16;
typedef uint32_t weaponRange_e32;

// --------------------------------------------------------------------------------------------------------------------

typedef struct _polyChar_scn1_t {
    uint8_t stuff_0x00[0x14];

    // (pos is now 0x14)
    void *modelAnimRamAddr; // 0x14

    // (pos is now 0x18)
    uint8_t stuff_0x18[0x2c];

    // (pos is now 0x44)
    int16_t battleId;       // 0x44
    int16_t battleModelId;  // 0x46

    // (pos is now 0x48)
    uint8_t stuff_0x48[0x1e];

    // (pos is now 0x66)
    int16_t animId;         // 0x66
    int16_t currentAnimId;  // 0x68

    // (pos is now 0x6a)
    uint8_t stuff_0x6a[0x0e];

    // (pos is now 0x78)
    VECTOR boundingBoxHalfSize; // 0x78

    // (pos is now 0x84)
    uint8_t stuff_0x8a[0x5c];

    // (pos is now 0xe0)
    bool inAttackAnimation; // 0xe0
    bool inDeathAnimation;  // 0xe1
    bool inHurtAnimation;   // 0xe2
    bool isOnGround;        // 0xe3
    bool drawBoundingBox;   // 0xe4
    bool doneLoading;       // 0xe5
    bool isActive;          // 0xe6
    bool unknown0xe7;       // 0xe7
    bool unknown0xe8;       // 0xe8
    bool sceneIsWater;      // 0xe9
    bool unknown0xea;       // 0xea
    bool unknown0xeb;       // 0xeb
    bool isTitan;           // 0xec
    bool maybeShowCriticalHitChargeLines; // 0xed

    // (pos is now 0xee)
    uint8_t stuff_0xee[0x1e];

    // 0x10c bytes
} polyChar_scn1_t;

static_assert(offsetof(polyChar_scn1_t, battleId)            == 0x44);
static_assert(offsetof(polyChar_scn1_t, animId)              == 0x66);
static_assert(offsetof(polyChar_scn1_t, boundingBoxHalfSize) == 0x78);
static_assert(offsetof(polyChar_scn1_t, inAttackAnimation)   == 0xe0);
static_assert(sizeof(polyChar_scn1_t) == 0x10c);

// TODO: Are Scn3 + PD the same?
typedef struct _polyChar_scn3_t {
    // Not all of this is known, and not all of this has been entered yet out of laziness.
    uint8_t notYetDefined1[0x20];

    // (offset is now 0x20)
    VECTOR pos;
    VECTOR scale;
    ANGLES rot;

    // (offset is now 0x3e)
    uint8_t notYetDefined2[0x06];

    // (offset is now 0x44)
    uint16_t battleId;
    uint16_t battleModelId;

    // (offset is now 0x48)
    uint8_t notYetDefined3[0x130];

    // 0x178 bytes
} polyChar_scn3_t;

static_assert(offsetof(polyChar_scn3_t, pos)            == 0x20);
static_assert(offsetof(polyChar_scn3_t, notYetDefined2) == 0x3e);
static_assert(offsetof(polyChar_scn3_t, battleId)       == 0x44);
static_assert(sizeof(polyChar_scn3_t) == 0x178);

#if SCENARIO == 1
typedef polyChar_scn1_t polyChar_t;
#elif SCENARIO >= 3
typedef polyChar_scn3_t polyChar_t;
#endif

typedef struct _camera_scn1_t {
    ANGLES        rot;
    uint8_t       padding_0x06[2];
    FIXED         zOffset;
    FIXED         interp;
    voidFunc_f   *func;
    camMode_e16   camMode;
    int16_t       stage;
    int16_t       startupFrames;
    int16_t       frame;
    camTarget_e16 camTarget;
    uint16_t      camTargetSub;
    FIXED         targetDist;
    int16_t       shakeMode;
    uint8_t       padding_0x026[2];
    FIXED         shakeMode3Amount;
} camera_scn1_t;

static_assert(sizeof(camera_scn1_t) == 0x2c);

#if SCENARIO == 1
typedef camera_scn1_t camera_t;
#endif

typedef struct _battleSceneInfo_t {
    uint16_t mpdFileId;
    uint16_t lightingStyle;
    color_t  color;
} battleSceneInfo_t;

typedef struct _sprEff_t {
    VECTOR  pos;              // 0x00
    VECTOR  maybeTargetVec;   // 0x0c
    VECTOR  somePosVec;       // 0x18
    VECTOR  someRotVec;       // 0x24
    int16_t isRunning;        // 0x30
    uint8_t bytes_0x32[2];    // 0x32
    int16_t framesToWait;     // 0x34
    int16_t frame;            // 0x36
    void *func;               // 0x38
    uint8_t bytes_0x3c[8];    // 0x3c
    int16_t short_0x44;       // 0x44
    int16_t short_0x46;       // 0x46
    int16_t short_0x48;       // 0x48
    int16_t moveYaw;          // 0x4a
    int32_t moveDistPerFrame; // 0x4c
    int32_t maybeSize;        // 0x50
} sprEff_t;

static_assert(sizeof(sprEff_t) == 0x54);

// TODO: actually add these types.
typedef struct _pcFunc_t pcFunc_t;

#if SCENARIO == 1
typedef struct _intFunc_scn1_t intFunc_scn1_t;
#endif

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_SF3_X014_TYPES_H

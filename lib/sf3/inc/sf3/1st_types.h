#ifndef INCLUDED_1ST_TYPES_H
#define INCLUDED_1ST_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

enum {
    ACMD_00_STOP_MUSIC                       = 0x00,
    ACMD_F0_FADE_MUSIC_OUT                   = 0xf0,
    ACMD_F1_MAYBE_FADE_NEXT_TRACK_IN         = 0xf1,
    ACMD_F2_SET_MUSIC_VOLUME_TO_75_PERCENT   = 0xf2,
    ACMD_F3_RESET_MUSIC_VOLUME               = 0xf3,
    ACMD_F4_DUNNO_0x00_THEN_WAIT             = 0xf4,
    ACMD_F5_DUNNO_0x80_THEN_WAIT             = 0xf5,
    ACMD_F6_PAUSE_MUSIC                      = 0xf6,
    ACMD_F7_RESUME_MUSIC                     = 0xf7,
    ACMD_F8_DUNNO_LOOKS_LIKE_IT_DOES_NOTHING = 0xf8,
    ACMD_F9_PLAY_LAST_TRACK                  = 0xf9,
    ACMD_FA_SET_LAST_TRACK                   = 0xfa,
    ACMD_FB_STOP_BACKGROUND_SFX_1            = 0xfb,
    ACMD_FC_STOP_BACKGROUND_SFX_2            = 0xfc,
    ACMD_FD_STOP_SFX                         = 0xfd,
    ACMD_FE_STOP_JINGLE                      = 0xfe,
    ACMD_FF_KILL_AUDIO                       = 0xff,
    ACMD_SFX_ERROR_BUZZ                      = 0x202,
};

typedef uint8_t  audioCommand_e8;
typedef uint16_t audioCommand_e16;
typedef uint32_t audioCommand_e32;

enum {
    BUTTON_NONE                          = 0x0000,
    BUTTON_0x01_UNKNOWN                  = 0x0001,
    BUTTON_0x02_UNKNOWN                  = 0x0002,
    BUTTON_0x08_UNKNOWN                  = 0x0004,
    BUTTON_L                             = 0x0008,
    BUTTON_Z                             = 0x0010,
    BUTTON_Y                             = 0x0020,
    BUTTON_X                             = 0x0040,
    BUTTON_R                             = 0x0080,
    BUTTON_B                             = 0x0100,
    BUTTON_C                             = 0x0200,
    BUTTON_A                             = 0x0400,
    BUTTON_START                         = 0x0800,
    BUTTON_UP                            = 0x1000,
    BUTTON_DOWN                          = 0x2000,
    BUTTON_LEFT                          = 0x4000,
    BUTTON_RIGHT                         = 0x8000,
};

typedef uint8_t  controllerButton_e8;
typedef uint16_t controllerButton_e16;
typedef uint32_t controllerButton_e32;

// --------------------------------------------------------------------------------------------------------------------

typedef struct _fadeColorSetting_t {
    int16_t r;
    int16_t g;
    int16_t b;
} fadeColorSetting_t;

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_1ST_TYPES_H

#ifndef INCLUDED_SF3_X003_TYPES_H
#define INCLUDED_SF3_X003_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

enum {
    MSGVAR_UNSET      = 0,
    MSGVAR_UNIT_ID    = 1,
    MSGVAR_ITEM_ID    = 2,
    MSGVAR_CLASS_ID   = 3,
    MSGVAR_SPELL_ID   = 4,
    MSGVAR_NUMBER     = 5,
    MSGVAR_LOAD_ID    = 6,
    MSGVAR_SPECIAL_ID = 7,
    MSGVAR_PARTNER_LV = 8,
};

typedef uint8_t  msgVarType_e8;
typedef uint16_t msgVarType_e16;
typedef uint32_t msgVarType_e32;

// --------------------------------------------------------------------------------------------------------------------

// TODO: actually add these types.
typedef struct _dialog_t dialog_t;
typedef struct _dialogCursor_t dialogCursor_t;
typedef struct _dialogSprite_t dialogSprite_t;
typedef struct _dialogSpriteList_t dialogSpriteList_t;

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_SF3_X003_TYPES_H

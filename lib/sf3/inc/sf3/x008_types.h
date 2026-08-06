#ifndef INCLUDED_SF3_X008_TYPES_H
#define INCLUDED_SF3_X008_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

typedef struct _npc_t {
    int16_t spriteId;
    int16_t flagChecked;
    uint32_t *scriptPtr;
    VECTOR pos;
    ANGLE dir;
    int16_t interactBehavior;
} npc_t;

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_SF3_X008_TYPES_H

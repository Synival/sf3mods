#ifndef INCLUDED_SF3_X012_TYPES
#define INCLUDED_SF3_X012_TYPES

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

typedef struct _tileHeightTerrain_t {
    uint8_t height;
    terrain_e8 terrain;
} tileHeightTerrain_t;

typedef struct _battleMap_t {
    tileHeightTerrain_t tiles[64][64];
} battleMap_t;

// --------------------------------------------------------------------------------------------------------------------

#endif // INCLUDED_SF3_X012_TYPES

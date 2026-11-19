#ifndef INCLUDED_SF3_X012
#define INCLUDED_SF3_X012

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"
#include "x012_types.h"

// --------------------------------------------------------------------------------------------------------------------

extern terrain_e16 getTileTerrainType(const battleMap_t *map, int tileX, int tileY);

#if SCENARIO == 1
extern int32_t getLandEffectPercent(int32_t battleId, terrain_e16 terrainType);
#endif

// --------------------------------------------------------------------------------------------------------------------

#endif // INCLUDED_SF3_X012

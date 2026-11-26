#ifndef INCLUDED_SF3_GBR
#define INCLUDED_SF3_GBR

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

typedef struct _gbr_t {
    uint8_t stuff_0x00[0x74];

    // at 0x74
    int16_t totalPolygons;
    int16_t totalVertices;

    uint8_t stuff_0x74[0x2c];

    // at 0xa4
    int16_t dispPolygons;

    uint8_t stuff_0xa6[0x35a];
} gbr_t;

static_assert(offsetof(gbr_t, totalPolygons) == 0x74);
static_assert(offsetof(gbr_t, dispPolygons)  == 0xa4);
static_assert(sizeof(gbr_t) == 0x400);

// --------------------------------------------------------------------------------------------------------------------

extern gbr_t GBR;

// --------------------------------------------------------------------------------------------------------------------

#endif  // INCLUDED_SF3_GBR

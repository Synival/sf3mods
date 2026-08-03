#ifndef INCLUDED_SF3_SGL_TYPES_H
#define INCLUDED_SF3_SGL_TYPES_H

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

typedef int32_t FIXED;
typedef int16_t FRAC;
typedef int16_t ANGLE;

// --------------------------------------------------------------------------------------------------------------------

typedef struct _VECTOR {
    FIXED x, y, z;
} VECTOR;

typedef struct _FRAC_VECTOR {
    FRAC x, y, z;
} FRAC_VECTOR;

typedef struct _ANGLES {
    ANGLE x, y, z;
} ANGLES;

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_SF3_SGL_TYPES_H

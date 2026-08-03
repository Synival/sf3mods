#ifndef INCLUDED_SF3_CONFIG_H
#define INCLUDED_SF3_CONFIG_H

// --------------------------------------------------------------------------------------------------------------------

// Can't compile anything if SCENARIO isn't defined.
#if !defined(SCENARIO) || (SCENARIO - 0 == 0)
#error SCENARIO undefined! Please make sure this is defined from the build target in the Makefile.
#endif

// C23 required.
#if !(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
#error This project requires C23. Please use a compiler that supports the "-std=c23" argument.
#endif

// --------------------------------------------------------------------------------------------------------------------

#include <stdint.h>

// --------------------------------------------------------------------------------------------------------------------

#endif // #ifndef INCLUDED_SF3_CONFIG_H

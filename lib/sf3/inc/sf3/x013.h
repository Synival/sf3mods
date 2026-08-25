#ifndef INCLUDED_SF3_X013
#define INCLUDED_SF3_X013

// --------------------------------------------------------------------------------------------------------------------

#include "common.h"

#include "x013_types.h"

// --------------------------------------------------------------------------------------------------------------------

// Forward declarations
typedef struct _battleUnit_t battleUnit_t;

// --------------------------------------------------------------------------------------------------------------------

extern bool queueBCmd0(battleCmd_e16 cmd);
extern bool queueBCmd1(battleCmd_e16 cmd, int16_t arg);
extern bool queueBCmd2(battleCmd_e16 cmd, int16_t arg1, int16_t arg2);
extern bool queueBCmdMessageAlways(int16_t msg);
extern bool queueBCmdMessageIfSettingOn(int16_t msg);

extern bool applyAntidoteLv2(battleUnit_t *unit);

// --------------------------------------------------------------------------------------------------------------------

extern int16_t g_spellToCastLevel;
extern int32_t g_currentVictimBattleId;
extern bool g_attackDodged;

// --------------------------------------------------------------------------------------------------------------------

#endif  // INCLUDED_SF3_X013

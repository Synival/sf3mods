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

extern int32_t getCurrentFriendshipStatBoost(int32_t unitId, friendshipBonus_e32 bonus);
extern int32_t getAttackEffectivenessPower(int32_t attackerId, int32_t victimId);

extern bool applyAntidoteLv2(const battleUnit_t *unit);

// --------------------------------------------------------------------------------------------------------------------

extern int32_t g_attackerUnitID;
extern int16_t g_spellToCastLevel;
extern int32_t g_currentVictimUnitID;
extern bool g_attackDodged;
extern int8_t g_effectivenessBonus;
extern turnAction_t *g_battleTurnAction;
extern const specialAttack_t g_specialAttackTable[];

// --------------------------------------------------------------------------------------------------------------------

#endif  // INCLUDED_SF3_X013

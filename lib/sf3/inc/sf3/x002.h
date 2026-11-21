#ifndef INCLUDED_SF3_X002
#define INCLUDED_SF3_X002

// --------------------------------------------------------------------------------------------------------------------

#include "x002_types.h"

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

extern battleUnit_t *getUnit(int32_t battleId);
extern item_t *getItem(int32_t itemId);
extern spell_t *getSpell(int32_t spellId);

extern void beginScene();
extern void endScene();

extern bool getGameFlag(uint32_t flag);

// --------------------------------------------------------------------------------------------------------------------

// TODO: Make this part of g_saveData
extern uint16_t g_subLoadingId;
// TODO: Make this part of g_saveData
extern uint16_t g_saveDataMpdFileId;

// --------------------------------------------------------------------------------------------------------------------

#endif // INCLUDED_SF3_X002

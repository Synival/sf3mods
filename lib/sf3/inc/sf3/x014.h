#ifndef INCLUDED_SF3_X014
#define INCLUDED_SF3_X014

// --------------------------------------------------------------------------------------------------------------------

#include "x014_types.h"

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

extern void writeDebugBattleLoadingInfo();
extern void writeDebugPolyCharAnimationInfo(const polyChar_t *polyChar);

extern ANGLE getPitchBetweenPoints(VECTOR *vec1, VECTOR *vec2);
extern ANGLE getFlippedAngle(ANGLE angle);

extern void polyCharGetPosition(const polyChar_t *polyChar, VECTOR *vecOut, polyCharPos_e32 pos);
extern void getPolyCharPosition0x01or0x09ifNotFound(const polyChar_t *polyChar, VECTOR *vecOut);

#if SCENARIO >= 2
extern void camFuncCam1Near();
extern void camFuncCam1Far();
extern void camFuncCam2();
extern void camFuncCam3Near();
extern void camFuncCam3Far();
#endif

extern void camFuncGolem();
extern void camFuncTitan();

extern void setCameraFunc(voidFunc_f *camFunc);

extern void showBattleMessage(int msg, bool canSuppress);
extern void wait10FramesThen30OrButtonPress();
extern void loadAndStartBattleAnimation(polyChar_t *polyChar, animId_e32 animId);

extern animId_e32 getAvailableAnimId(polyChar_t *polyChar, animId_e32 animId);
extern void wait4SecsForAttackOrHurtAnimationToFinish(polyChar_t *polyChar);
extern void setAnimationSpeed(polyChar_t *polyChar, FIXED speed);
extern int32_t maybeGetAnimFrameCount0(polyChar_t *polyChar, animId_e32 animId, int lookFor);

// Looks like these were removed in Scenario 1, in favor of either "pcFunc" or "intJob", I think.
#if SCENARIO == 1
extern intFunc_scn1_t *newSpinnyLightIntFunc(polyChar_t *polyChar);
extern void deleteIntFunc(intFunc_scn1_t *intFunc);
extern void unknownAnimLoadingFunc(polyChar_scn1_t *polyChar, int32_t animId);
#endif

extern sprEff_t *newSprEffLine(const VECTOR *startPos, const VECTOR* endPos, uint16_t colorBGR, int16_t framesToWait);

extern void someKindOfUpdateUnitStats(polyChar_t *polyChar);

// TODO: what is this, exactly? we need it, but who knows what it does!
extern void pd_FUN_060909bc();

extern int32_t getBattleModelIdFileId(int32_t battleModelId);

// --------------------------------------------------------------------------------------------------------------------

extern bool g_debugMode_X014;

extern polyChar_t *g_polyCharAttacker;
extern polyChar_t *g_polyCharVictim;

extern bool        g_flipPolyChars;
extern animId_e16  g_attackerAnimId;

#if SCENARIO == 1
extern camera_t    g_camera;
extern VECTOR      g_cameraPos;
#endif

extern spellId_e16 g_attackerSpellId_X014;
extern short       g_attackerSpecialId_X014;

extern palette0x20_t *g_battlePaletteTable1[49];
extern VECTOR        g_lightPos;

extern int16_t g_animLoaded;
extern int32_t g_battleAnimationLoadingFileQueueIdx;
extern polyChar_scn1_t *g_battleAnimationLoadingPolyChar;

extern int16_t g_battleStageLoadState;

// --------------------------------------------------------------------------------------------------------------------

#endif  // INCLUDED_SF3_X014

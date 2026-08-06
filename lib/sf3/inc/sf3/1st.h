#ifndef INCLUDED_SF3_1ST
#define INCLUDED_SF3_1ST

// --------------------------------------------------------------------------------------------------------------------

#include "1st_types.h"

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

extern void memcpy(void *dst, const void *src, uint32_t size);
extern FIXED sin(ANGLE theta);
extern FIXED cos(ANGLE theta);
extern ANGLE atan2(FIXED y, FIXED x);
extern int32_t divFixed(FIXED divisor, FIXED dividend);
extern int32_t multFixed(FIXED a, FIXED b);
extern int32_t divSigned(int32_t dividend, int32_t divisor);

extern void gbrSetFov(ANGLE fov);
extern void gbrSetMsScreenDist(FIXED dist);
#if SCENARIO == 1
extern void getCoordInGbrMatrixSpace(FIXED x, FIXED y, FIXED z, VECTOR *vecOut);
#else
extern void getCoordInGbrMatrixSpace(const VECTOR *vecIn, VECTOR *vecOut);
#endif

extern void queueAudioCommand(audioCommand_e32 cmd);

extern void waitFrames(int frames);
extern uint16_t getBoundedRandom(uint16_t bound);
extern uint16_t getRandomUShort();

extern int32_t loadPartialFileToAddrWithoutCallback(int32_t fileId, void *toAddr, int32_t chunkPos, int32_t chunkSize);

extern void setColorFadeTransition(uint32_t fadeBitmask, int16_t fadeDuration, fadeColorSetting_t *fadeColor);
extern void resetColorFadeTransition(uint32_t fadeBitmask, int16_t fadeDuration);

extern void addIntJob(voidFunc_f *func, uint16_t orderAndType);
extern void removeIntJobByFunc(voidFunc_f *func);

extern void pushGbrMatrix();
extern void popGbrMatrix();
extern void translateGbrMatrix(FIXED x, FIXED y, FIXED z);
extern void rotateGbrMatrixY(FIXED rotY);

#if SCENARIO == 1 || SCENARIO == 2
// Something necessary for button buffering
extern void someBufferedButtonsFunc();
#endif

// --------------------------------------------------------------------------------------------------------------------

extern volatile controllerButton_e16 g_buttonsDown;
extern volatile controllerButton_e16 g_bufferedButtonsDown;

extern int g_messageId;
extern interactable_t *g_interactableTablePtr;

// --------------------------------------------------------------------------------------------------------------------

#endif  // INCLUDED_SF3_1ST

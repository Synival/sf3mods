#ifndef INCLUDED_SF3_X003
#define INCLUDED_SF3_X003

// --------------------------------------------------------------------------------------------------------------------

#include "x003_types.h"

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

extern dialog_t *newDialogWithSfx(int16_t x, int16_t y, int16_t width, int16_t height, bool frameless);
extern void closeDialogWithSfx(dialog_t *dialog);
extern void resetDialogState();
extern void freeDialogSpritesInRect(dialogSpriteList_t *spriteList, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
extern void writeHexValueToDialog(uint32_t value, uint8_t chars, dialog_t *dialog, int16_t x, int16_t y);
extern void writeStrToDialogAsWStr(const char *str, dialog_t *dialog, int16_t x, int16_t y);

extern dialogCursor_t *newDialogCursor(dialog_t *dialog, bool isArrow, int16_t width, int16_t height);

extern void pushMsgVariable(int value, msgVarType_e8 varId);

// --------------------------------------------------------------------------------------------------------------------

#endif // INCLUDED_SF3_X003

#ifndef INCLUDED_SF3_X003
#define INCLUDED_SF3_X003

// --------------------------------------------------------------------------------------------------------------------

#include "x003_types.h"

#include "common.h"

// --------------------------------------------------------------------------------------------------------------------

extern dialog_t *newDialog(int16_t x, int16_t y, int16_t width, int16_t height, bool frameless);
extern dialog_t *newDialogWithSfx(int16_t x, int16_t y, int16_t width, int16_t height, bool frameless);
extern void closeDialogWithSfx(dialog_t *dialog);

extern void setDialogWriteDefaults();
extern void setDialogWriteColor(int32_t color);

extern void freeDialogSpritesInRect(dialogSpriteList_t *spriteList, int16_t x1, int16_t y1, int16_t x2, int16_t y2);

extern void getMsgDimensions(int32_t msgId, int32_t *widthOut, int32_t *heightOut);

extern void writeHexValueToDialog(uint32_t value, uint8_t chars, dialog_t *dialog, int16_t x, int16_t y);
extern void writeStrToDialog(const char *str, dialog_t *dialog, int16_t x, int16_t y);
extern void writeStrToDialogAsWStr(const char *str, dialog_t *dialog, int16_t x, int16_t y);
extern void writeWStrToDialog(const int16_t *wstr, dialog_t *dialog, int16_t x, int16_t y);
extern void writeMsgToDialog(int32_t msgId, dialog_t *dialog, int16_t x, int16_t y);

extern dialogCursor_t *newDialogCursor(dialog_t *dialog, bool isArrow, int16_t width, int16_t height);

extern void pushMsgVariable(int32_t value, msgVarType_e8 varId);

extern void decodeMsgToMsgQueue(int32_t msgId);
extern void concatMsgQueueToCurrentMessage();

extern int16_t g_currentMessage[256];
extern int32_t g_currentMessageLength;

// --------------------------------------------------------------------------------------------------------------------

#endif // INCLUDED_SF3_X003

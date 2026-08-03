#include "sf3/1st.h"
#include "sf3/x003.h"

// --------------------------------------------------------------------------------------------------------------------

// Scenario 3+PD have music tracks not present in 1+2.
#if SCENARIO == 1 || SCENARIO == 2
    constexpr uint8_t MUSIC_X = 0x20;
    constexpr uint8_t MUSIC_Y = 0x01;
    constexpr uint8_t MUSIC_Z = 0x06;
#else
    constexpr uint8_t MUSIC_X = 0x3a;
    constexpr uint8_t MUSIC_Y = 0x0a;
    constexpr uint8_t MUSIC_Z = 0x38;
#endif

// --------------------------------------------------------------------------------------------------------------------

typedef struct _musicDebugDialog_t {
    dialog_t *dialog;
    uint16_t currentCmd;
} musicDebugDialog_t;

// --------------------------------------------------------------------------------------------------------------------

void setCommand(int16_t cmd);
void redrawCommand();

// --------------------------------------------------------------------------------------------------------------------

static musicDebugDialog_t mdd;

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".musicDebugMenu")]]
void musicDebugMenu() {
    resetDialogState();

    // Create our new dialog.
    mdd.dialog = newDialogWithSfx(160, 100, 160, 0x28, false);
    mdd.currentCmd = 0xF0;
    writeStrToDialogAsWStr("Command: ",           mdd.dialog, 0x04, 0x04);
    writeStrToDialogAsWStr("Music Debugger v1.1", mdd.dialog, 0x04, 0x14);

    redrawCommand();

    // Wait for buttons from previous menu to be released.
    while (g_buttonsDown != BUTTON_NONE)
        waitFrames(1);

    // Disabled for now -- if we ever need more menu items 
#if 0
    dialogCursor_t *cursor = newDialogCursor(mdd.dialog, false, 100, 16);
#endif

    // Now run our own menu.
    while (true) {
        waitFrames(1);

#if SCENARIO == 1 || SCENARIO == 2
        // Seems necessary for buffering.
        someBufferedButtonsFunc();
#endif

        controllerButton_e16 buttons = g_bufferedButtonsDown;
        if (buttons & BUTTON_B)
            break;

        if (buttons & BUTTON_LEFT)
            setCommand((int16_t) mdd.currentCmd - 0x01);
        else if (buttons & BUTTON_RIGHT)
            setCommand((int16_t) mdd.currentCmd + 0x01);
        else if (buttons & BUTTON_UP)
            setCommand((int16_t) mdd.currentCmd - 0x10);
        else if (buttons & BUTTON_DOWN)
            setCommand((int16_t) mdd.currentCmd + 0x10);
        else if (buttons & BUTTON_X)
            setCommand(MUSIC_X);
        else if (buttons & BUTTON_Y)
            setCommand(MUSIC_Y);
        else if (buttons & BUTTON_Z)
            setCommand(MUSIC_Z);
        else if (buttons & BUTTON_L)
            setCommand(0x00);
        else if (buttons & BUTTON_R)
            setCommand(0xF0);
        else if (buttons & BUTTON_START)
            setCommand(0x200);
        else if (buttons & (BUTTON_A | BUTTON_C))
            queueAudioCommand(mdd.currentCmd);
    }

    // Menu done. Close the dialog.
    closeDialogWithSfx(mdd.dialog);
    waitFrames(1);
}

// --------------------------------------------------------------------------------------------------------------------

void setCommand(int16_t cmd) {
    if (cmd < 0)
        cmd = 0;
    if (cmd > 0x2ff)
        cmd = 0x2ff;
    if (cmd != mdd.currentCmd) {
        mdd.currentCmd = (uint16_t) cmd;
        redrawCommand();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void redrawCommand() {
    freeDialogSpritesInRect((dialogSpriteList_t *) (mdd.dialog), 100, 0x04, 160, 0x14);
    if (mdd.currentCmd < 0x100)
        writeHexValueToDialog(mdd.currentCmd, 2, mdd.dialog, 108, 0x04);
    else
        writeHexValueToDialog(mdd.currentCmd, 3, mdd.dialog, 100, 0x04);
}


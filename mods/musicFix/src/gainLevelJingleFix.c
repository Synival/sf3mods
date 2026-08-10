#include <sf3/1st.h>
#include <sf3/x014.h>

// --------------------------------------------------------------------------------------------------------------------

// This replaces a call to wait10FramesThen30OrButtonDown() after the "FOO gained a level!" message.
[[gnu::section(".waitThenUnjinglify")]]
void waitThenUnjinglify() {
    // Original call
    wait10FramesThen30OrButtonPress();

    // Unjinglify! This will prevent the jingle from automatically switching back to the map track when complete.
    g_isPlayingJingle = 0;

    // Don't force a switch based on a timer.
    g_stopChannel1AndResumeChannel0Timer = 0;
}

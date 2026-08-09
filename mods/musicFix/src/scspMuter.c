#include <sf3/1st.h>

#include <sf3/common.h>

#include <stdint.h>

// --------------------------------------------------------------------------------------------------------------------

inline uint16_t *_getDebugTextCoords(int32_t x, int32_t y) {
    return (uint16_t *)(x * 2 + y * 0x80 + 0x25e58000);
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".newDebugWriteStaExpEnd")]]
void debugWriteStaExpEnd(int32_t what, uint32_t value) {
    if (what > 2)
        what = 2;

    int32_t y = 10 + what;
    const char *str = (const char *)(void *)(0x60886a0 + what * 4);

    writeDebugUIntWithoutZeroes(hexToDec(value), _getDebugTextCoords(-2, y));
    writeDebugStr(str, _getDebugTextCoords(1, y));
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".new_FUN_06015018_call")]]
uint32_t new_FUN_06015018_call() {
    // Unassign all voices on the SCSP.
    volatile uint32_t *ptr = (volatile uint32_t *)0x25A09C08;
    for (int i = 0; i < 32; ++i) {
        *ptr = 0;
        ptr += 3; 
    }

    // Call the function we were supposed to call (whatever it is).
    return ((uint32_t (*)()) 0x06015018)();
}

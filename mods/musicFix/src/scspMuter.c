#include "sf3/common.h"

#include <stdint.h>

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

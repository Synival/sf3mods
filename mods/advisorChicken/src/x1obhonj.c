#include <stdint.h>

// Compile implementation for Lookover HQ
constexpr uint8_t  c_chickenCharId     = 0x40;
constexpr uint16_t c_chickenCluckMsgId = 0x86f;
constexpr uint16_t c_advisorMsgId      = 0x88b;
#define ADVISOR_CHICKEN_CHECK_FOR_PALSIS 1
#define ADVISOR_CHICKEN_COMPILE_IMPL 1
#include "advisorChickenImpl.c"

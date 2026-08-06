#include <stdint.h>

// Compile implementation for Flagard HQ
constexpr uint8_t  c_chickenCharId     = 0x40;
constexpr uint16_t c_chickenCluckMsgId = 0; // TODO: chicken msg
constexpr uint16_t c_advisorMsgId      = 0; // TODO: Dantares' HQ dialogue
#define ADVISOR_CHICKEN_COMPILE_IMPL 1
#include "advisorChickenImpl.c"

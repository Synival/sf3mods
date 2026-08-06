#include <stdint.h>

// Compile implementation for Storich (X1STRI_H.BIN also used for Balsamo and Vagabond HQ)
constexpr uint8_t  c_chickenCharId     = 0x40;
constexpr uint16_t c_chickenCluckMsgId = 0x8b1;
constexpr uint16_t c_advisorMsgId      = 0x8d3;
#define ADVISOR_CHICKEN_CHECK_FOR_SUB_LOADING_ID 5
#define ADVISOR_CHICKEN_COMPILE_IMPL 1
#include "advisorChickenImpl.c"

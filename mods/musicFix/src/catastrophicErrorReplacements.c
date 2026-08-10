#include <sf3/1st.h>

// --------------------------------------------------------------------------------------------------------------------

extern void catastrophicError(const char *error);

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".catastrophicError_AddressError")]]
void catastrophicError_AddressError()
    { catastrophicError("ADDRESS ERROR"); }

[[gnu::section(".catastrophicError_DmaAddressError")]]
void catastrophicError_DmaAddressError()
    { catastrophicError("DMA ADDRESS ERROR"); }

[[gnu::section(".catastrophicError_GeneralUndefinedInstruction")]]
void catastrophicError_GeneralUndefinedInstruction()
    { catastrophicError("GENERAL UNDEFINED INSTRUCTION"); }

[[gnu::section(".catastrophicError_SlotUndefinedInstruction")]]
void catastrophicError_SlotUndefinedInstruction()
    { catastrophicError("SLOT UNDEFINED INSTRUCTION"); }

[[gnu::section(".catastrophicError_MatrixPushPopError")]]
void catastrophicError_MatrixPushPopError()
    { catastrophicError("MATRIX PUSH-POP ERROR"); }


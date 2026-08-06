#if ADVISOR_CHICKEN_COMPILE_IMPL

// Required pre-defined constexprs:
//
// - constexpr uint8_t  c_chickenCharId;
// - constexpr uint16_t c_chickenCluckMsgId;
// - constexpr uint16_t c_advisorMsgId;

// --------------------------------------------------------------------------------------------------------------------

#include <sf3/1st.h>
#include <sf3/x002.h>
#include <sf3/x008.h>
#include <sf3/x022.h>

#include <stdint.h>

// --------------------------------------------------------------------------------------------------------------------

extern int32_t originalStartFunction();
extern int32_t talkToAdvisor(int32_t charId, int32_t msgId);

extern uint32_t c_scriptMakeSolidUnpushable[];

// --------------------------------------------------------------------------------------------------------------------

void talkToAdvisorChicken();

// --------------------------------------------------------------------------------------------------------------------

static npc_t c_newNpcTable[2] = {
    {
        0x59,       /* Chicken */
        0x04,       /* Dantares not recruited */
        c_scriptMakeSolidUnpushable,
        {
            0x04F00000, /* x */
            0x00000000, /* y */
            0x02F00000, /* z */
        },
       -0x4000,     /* Direciion (facing west?) */
        00,         /* Turn when spoken to, then go back */
    },
    { -1 /* Please stop! */, 0, 0, { 0, 0, 0 }, 0, 0 },
};

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".newStartFunction")]]
int32_t newStartFunction() {
    // Run the original function, which might set up an interactable table or initialize sprites.
    auto const rval = originalStartFunction();

    // Initialize a chicken if 1) no Dantares...
    auto loadCondition = !getGameFlag(0x04);
    // 2) we haven't beaten the Tower yet (no Palsis)...
#if ADVISOR_CHICKEN_CHECK_FOR_PALSIS
    // and 3) we're the right sub-loading Id (Storich check for X1STRI_H.BIN)
    loadCondition = loadCondition && !getGameFlag(0x396);
#endif
#ifdef ADVISOR_CHICKEN_CHECK_FOR_SUB_LOADING_ID
    loadCondition = loadCondition && g_subLoadingId == ADVISOR_CHICKEN_CHECK_FOR_SUB_LOADING_ID;
#endif
    if (loadCondition) {
        loadNpcs(c_newNpcTable, c_chickenCharId);

        // SF3 only has one interactable table, so we're just going to hijack Dantares.
        for (interactable_t *intr = g_interactableTablePtr; intr->trigger != -1; intr++) {
            if (intr->triggerTargetId == 0x01) {
                intr->trigger         = 0;
                intr->triggerFlags    = 0;
                intr->triggerTargetId = c_chickenCharId;
                intr->flagChecked     = -1;
                intr->action          = (uint32_t) &talkToAdvisorChicken;
                break;
            }
        }
    }

    return rval;
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".talkToAdvisorChicken")]]
void talkToAdvisorChicken() {
    // Also loads X022.BIN
    beginScene();

    turnActorsToEachOtherById(c_chickenCharId, 0);
    if (talkToAdvisor(c_chickenCharId, c_advisorMsgId) == 0) {
        g_messageId = c_chickenCluckMsgId;
        queueAudioCommand(0x243);
        runDialogue(c_chickenCharId);
    }

    // Also unloads X022.BIN
    endScene();
}

#else

// To prevent compiler complaining about empty translation unit
const int c_advisorChickenDummy = 0;

#endif // #if ADVISOR_CHICKEN_COMPILE_IMPL

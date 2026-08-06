#include <stdint.h>

#include <sf3/1st.h>
#include <sf3/x002.h>
#include <sf3/x008.h>
#include <sf3/x022.h>

// --------------------------------------------------------------------------------------------------------------------

constexpr uint8_t  c_chickenCharId     = 0x40;
// TODO: these messages depend on the X1 file!
constexpr uint16_t c_chickenCluckMsgId = 0x8b1;
constexpr uint16_t c_advisorMsgId      = 0x8d3;

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
void newStartFunction() {
    // Initialize a chicken if 1) no Dantares and 2) we haven't beaten the Tower yet.
    // TODO: Second check should only be for the Lookover HQ
    if (!getGameFlag(0x04) && !getGameFlag(0x396)) {
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

    originalStartFunction();
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

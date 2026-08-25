#include <sf3/x013.h>

#include <sf3/x002.h>

#if SCENARIO == 1
    #define MSG_NO_LONGER_PARALYZED 0x7d0
    #define MSG_NO_LONGER_POISONED  0x7d1
#elif SCENARIO == 2
    #define MSG_NO_LONGER_PARALYZED 0x000 // TODO: what is it?
    #define MSG_NO_LONGER_POISONED  0x000 // TODO: what is it?
#elif SCENARIO == 3
    #define MSG_NO_LONGER_PARALYZED 0x8fd
    #define MSG_NO_LONGER_POISONED  0x8fe
#elif SCENARIO == 4
    #define MSG_NO_LONGER_PARALYZED 0x7ee
    #define MSG_NO_LONGER_POISONED  0x7ef
#else
    #error Unsupported Scenario!
#endif

// --------------------------------------------------------------------------------------------------------------------

// Forward declarations
static inline void removeCondition(battleCmd_e16 removeCmd, int16_t msg);
static inline bool applyAntidoteLv1(const battleUnit_t *unit);

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".applyAntidote")]]
void applyAntidote(void) {
    // Functions need the unit.
    const battleUnit_t *unit = getUnit(g_currentVictimUnitID);

    // What version of the antidote function should we run?
    const bool isStrongerAntidote = g_spellToCastLevel >= 2; // (lv3, lv4)

    // Run it, and see if we cured something.
    const bool somethingCured = isStrongerAntidote ? applyAntidoteLv2(unit) : applyAntidoteLv1(unit);

    // If not, the "attack" was "dodged" (nothing happens).
    g_attackDodged = !somethingCured;
}

// --------------------------------------------------------------------------------------------------------------------

static inline void removeCondition(battleCmd_e16 removeCmd, int16_t msg) {
    // Removes the condition and writes a message.
    queueBCmd2(removeCmd, (short) g_currentVictimUnitID, 0);
    queueBCmd1(BCMD_PUSH_MSG_UNIT_ID, (short) g_currentVictimUnitID);
    queueBCmdMessageAlways(msg);
}

// --------------------------------------------------------------------------------------------------------------------

static inline bool applyAntidoteLv1(const battleUnit_t *unit) {
    // Cure poison, if inflicted.
    const bool poisoned  = unit->state.poisonedTurns  != 0;
    if (poisoned)
        removeCondition(BCMD_REMOVE_POISON, MSG_NO_LONGER_POISONED);

    // Cure paralysis, if inflicted.
    const bool paralyzed = unit->state.paralyzedTurns != 0;
    if (paralyzed)
        removeCondition(BCMD_REMOVE_PARALYSIS, MSG_NO_LONGER_PARALYZED);

    // Return 'true' if this cured something.
    return paralyzed || poisoned;
}

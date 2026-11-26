#include "sf3/1st.h"
#include "sf3/x002_types.h"
#include "sf3/x003.h"
#include "sf3/x014.h"

// --------------------------------------------------------------------------------------------------------------------

void levelUpNew(levelUpInfo_t *levelUpInfo, polyChar_scn1_t *polyChar, battleUnit_t *unit);
void gainLevelCamFuncAttacker();
void gainLevelCamFuncVictim();
void spawnLevelUpParticlesIntJob();

// --------------------------------------------------------------------------------------------------------------------

static polyChar_scn1_t *g_polyCharLevelingUp = nullptr;

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".levelUpNew")]]
void levelUpNew_thunk(levelUpInfo_t *levelUpInfo, polyChar_scn1_t *polyChar, battleUnit_t *unit)
    { levelUpNew(levelUpInfo, polyChar, unit); }

// --------------------------------------------------------------------------------------------------------------------

void levelUpNew(levelUpInfo_t *levelUpInfo, polyChar_scn1_t *polyChar, battleUnit_t *unit) {
    // Things to remember for the 'end' function and the intJob.
    g_polyCharLevelingUp = polyChar;

    // Probably waiting for the scene to be reloaded in case of ending a spell or summon.
    while (g_battleStageLoadState != 0)
        waitFrames(1);

    // Wait for other animations in progress to finish.
    wait4SecsForAttackOrHurtAnimationToFinish(polyChar);

    // Start the "item" animation.
    auto animId = getAvailableAnimId(polyChar, ANIM_ITEM);
    loadAndStartBattleAnimation(polyChar, animId);
    setAnimationSpeed(polyChar, 0x10000);

    // This is what keeps the "use item" animation active.
    if (polyChar != nullptr)
        polyChar->inAttackAnimation = true;

    // Set up the spinny cam.
    voidFunc_f *camFunc = (polyChar == g_polyCharAttacker) ? gainLevelCamFuncAttacker : gainLevelCamFuncVictim;
    setCameraFunc(camFunc);

    // Fade the scene to a violet color.
    fadeColorSetting_t violet = { .r = -0x60, .g = -0x80, .b = -0x40 };
    setColorFadeTransition(0x31, 0x1e, &violet);

    // Let all but 10 frames of the animation play out. (I think?)
    auto aniFrameCountMinus10 = maybeGetAnimFrameCount0(polyChar, animId, 0) + -10;
    if (aniFrameCountMinus10 < 0)
        aniFrameCountMinus10 = 0;
    waitFrames(aniFrameCountMinus10);

    // Start spawning the "level up" rising particles, then wait another 10 frames.
    intFunc_scn1_t *spinnyLightIntFunc = newSpinnyLightIntFunc(polyChar);
    addIntJob(spawnLevelUpParticlesIntJob, 0x100);
    waitFrames(10);

    // TODO: We definitely don't want this, but how can we ensure that the jingle will stop?
    //       Do we need to match 1ST.BIN?
#if 0
    queueAudioCommand(ACMD_00_STOP_MUSIC);
    waitFrames(1);
#endif

    // Play the "promotion" / "level up" jingle.
    queueAudioCommand(0x106);

    // TODO: What exactly does this do?
    someKindOfUpdateUnitStats(polyChar);

    // Show the "<someone> is now level <level>!" message.
    pushMsgVariable(polyChar->unitId, MSGVAR_UNIT_ID);
    pushMsgVariable(levelUpInfo->newLevel, MSGVAR_NUMBER);
    showBattleMessage(0x7f2, false);
    wait10FramesThen30OrButtonPress();
    waitFrames(0x14);

    // Did we gain a spell or spell level?
    int16_t spellSlot = levelUpInfo->spellSlotLeveled;
    if (spellSlot != -1) {
        const spellIdLevel_t *spell = &(unit->spells[spellSlot]);

        if (spell->spellId != SPELL_NONE) {
            queueAudioCommand(0x257);

            if (spell->level < 2) {
                /* Learned a spell! */
                pushMsgVariable(spell->spellId, MSGVAR_SPELL_ID);
                showBattleMessage(0x7f3, false);
            }
            else {
                /* Gained a spell level! */
                pushMsgVariable(spell->spellId, MSGVAR_SPELL_ID);
                pushMsgVariable(spell->level, MSGVAR_NUMBER);
                showBattleMessage(0x7f4, false);
            }

            wait10FramesThen30OrButtonPress();
        }
    }

    /* Gain a bunch of stats! */
    int msgId = 0x7f7;
    int16_t *statPtr = &(levelUpInfo->hpGain);
    for (int i = 0; i < 5; i++) {
        if (*statPtr != 0) {
            queueAudioCommand(0x257);
            pushMsgVariable(*statPtr, MSGVAR_NUMBER);
            showBattleMessage(msgId, false);
            wait10FramesThen30OrButtonPress();
        }
        statPtr++;
        msgId++;
    }

    // End the animation, light effect, violet fade, and particles.
    if (polyChar != nullptr)
        polyChar->inAttackAnimation = false;

    removeIntJobByFunc(spawnLevelUpParticlesIntJob);
    deleteIntFunc(spinnyLightIntFunc);
    resetColorFadeTransition(0x31, 0x14);

    // TODO: not in polyChar, it's a global thing in Scenario 1.
    // This is what keeps the "use item" animation active.
    // It appears to be turned off anyway without this call.
    // polyChar->hasCustomLightPosition = false;

    waitFrames(0x14);
}

// --------------------------------------------------------------------------------------------------------------------

void gainLevelCamSpin() {
    FIXED sin0x0800 = multFixed(sin(g_camera.frame * 0x140), 0x0800);
    FIXED sin0x1999 = multFixed(sin(g_camera.frame * 0x0c0), 0x1999);

    g_camera.rot.x      = (ANGLE) (sin0x0800 + 0x400);
    g_camera.rot.y     += 0x01c0;
    g_camera.targetDist = sin0x1999 + 0xb333;
    g_camera.interp     = 0x1999;
}

// --------------------------------------------------------------------------------------------------------------------

void gainLevelCamFuncAttacker() {
    if (g_camera.stage == 1) {
        g_camera.camTarget = CAMTARGET_ATTACKER;
        gainLevelCamSpin();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void gainLevelCamFuncVictim() {
    if (g_camera.stage == 1) {
        g_camera.camTarget = CAMTARGET_VICTIM;
        gainLevelCamSpin();
    }
}

// --------------------------------------------------------------------------------------------------------------------

void spawnLevelUpParticle(polyChar_t *polyChar) {
    if (polyChar != nullptr) {
        // Get the chest/head position of our character.
        VECTOR polyCharPos;
        getPolyCharPosition0x01or0x09ifNotFound(polyChar, &polyCharPos);

        // Get the minimum distance away from the polyChar that the particle can start.
        FIXED minDist = (polyChar->boundingBoxHalfSize.x + polyChar->boundingBoxHalfSize.z) / 2;

        // Calculate the stop position of the particle.
        // Start with the position of the polyChar and translate out at random yaw and distance.
        VECTOR particleStop;
        pushGbrMatrix();
        translateGbrMatrix(polyCharPos.x, polyCharPos.y * 2, polyCharPos.z);
        rotateGbrMatrixY(getRandomUShort());
        getCoordInGbrMatrixSpace(minDist + (FIXED) (getRandomUShort() * 4), 0, 0, &particleStop);
        popGbrMatrix();

        // Start position is the same, but starting at the plane level.
        VECTOR particleStart;
        particleStart.x = particleStop.x;
        particleStart.y = 0;
        particleStart.z = particleStop.z;

        sprEff_t *sprEff = newSprEffLine(&particleStart, &particleStop, 0xe732, 0);
        if (sprEff != nullptr) {
            sprEff->short_0x44 = 7;
            sprEff->short_0x48 = 2;
        }
    }
}

// --------------------------------------------------------------------------------------------------------------------

void spawnLevelUpParticlesIntJob() {
    spawnLevelUpParticle(g_polyCharLevelingUp);
    spawnLevelUpParticle(g_polyCharLevelingUp);
    spawnLevelUpParticle(g_polyCharLevelingUp);
}


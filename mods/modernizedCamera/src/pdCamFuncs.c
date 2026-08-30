#include "sf3/1st.h"
#include "sf3/x002.h"
#include "sf3/x014.h"

// --------------------------------------------------------------------------------------------------------------------

void camFuncCam1Near();
void camFuncCam1Far();
void camFuncCam2();
void camFuncCam3Near();
void camFuncCam3Far();
bool isFarAttackFromPolyCharAttacker();

// --------------------------------------------------------------------------------------------------------------------

bool g_moveCam2ToVictim   = false;
bool g_moveCam2ToAttacker = false;

// --------------------------------------------------------------------------------------------------------------------

alignas(4) static voidFunc_f *const g_cameraFuncTable[6] = {
    // Near functions
    camFuncCam1Near, // camera 1
    camFuncCam2,     // camera 2
    camFuncCam3Near, // camera 3

    // Far functions
    camFuncCam1Far,  // camera 1
    camFuncCam2,     // camera 2
    camFuncCam3Far,  // camera 3
};

// --------------------------------------------------------------------------------------------------------------------

static weaponRange_e8 polyCharGetWeaponRange(polyChar_t *polyChar) {
    battleUnit_t *unit;
    item_t       *weapon;
    uint8_t       range;

    if (polyChar == nullptr)
        return 0;

    unit   = getUnit(polyChar->battleId);
    weapon = getItem(unit->weapon);
    range  = weapon->range;

    // Inner range check
    if ((range & 0xf) >= 0x2)
        return WEAPONRANGE_FAR;
    // Outer range check
    else if (((range >> 4) & 0xf) >= 0x2)
        return WEAPONRANGE_CLOSE_AND_FAR;
    else
        return WEAPONRANGE_CLOSE;
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".isFarAttackFromPolyCharAttacker")]]
bool isFarAttackFromPolyCharAttacker() {
    switch (polyCharGetWeaponRange(g_polyCharAttacker)) {
        case WEAPONRANGE_FAR:
            return true;

        case WEAPONRANGE_CLOSE_AND_FAR:
            if (g_attackerAnimId == ANIM_ATTACK_FAR)
                return true;
            return g_attackerSpellId_X014 != SPELL_NONE || g_attackerSpecialId_X014 > 0x13;

        default:
            return false;
    }
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".getScreenDistForAttack")]]
int getScreenDistForAttack() {
    // TODO: Add the GBR struct
    FIXED *gbrMsScreenDist = ((void *)0x060ffc68);

    FIXED newScreenDist;
    FIXED oldScreenDist;
    ANGLE newFov;

    oldScreenDist = *gbrMsScreenDist;
    newFov        = isFarAttackFromPolyCharAttacker() ? 0x2aaa : 0x2000;

    // Band-aid fixes to the Titan attacks to keep everything *mostly* in view.
    if (g_polyCharAttacker != nullptr && g_polyCharAttacker->isTitan)
        newFov = 0x0800;

    gbrSetFov(newFov);
    newScreenDist = *gbrMsScreenDist;
    gbrSetMsScreenDist(oldScreenDist);

    return newScreenDist;
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".cameraAssign")]]
void cameraAssign() {
    uint8_t cameraSetting;

    // Choose a camera angle at random unless a button is held down.
    switch (g_buttonsDown & (BUTTON_X | BUTTON_Y | BUTTON_Z)) {
        case BUTTON_X: cameraSetting = 0; break;
        case BUTTON_Y: cameraSetting = 1; break;
        case BUTTON_Z: cameraSetting = 2; break;
        default:       cameraSetting = (uint8_t) getBoundedRandom(3); break;
    }

    if (g_polyCharAttacker && g_polyCharAttacker->battleModelId == (0x2000 | MONSTER_QUEEN_WORM))
        cameraSetting = 1;

    if (g_polyCharVictim) {
        if (g_polyCharVictim->battleModelId == (0x2000 | MONSTER_QUEEN_WORM) || g_polyCharVictim->isTitan)
            cameraSetting = 0;
    }

    cameraSetting += (uint8_t) (isFarAttackFromPolyCharAttacker() ? 3 : 0);
    voidFunc_f *cameraFunc = g_cameraFuncTable[cameraSetting];

    if (g_polyCharAttacker) {
        if (g_polyCharAttacker->battleModelId == (0x2000 | MONSTER_GOLEM))
            cameraFunc = camFuncGolem;
        else if (g_polyCharAttacker->isTitan)
            cameraFunc = camFuncTitan;
    }

    setCameraFunc(cameraFunc);
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".camFuncCam1Near")]]
void camFuncCam1Near() {
    int16_t rotYMult = g_flipPolyChars ? -1 : 1;

    switch (g_camera.stage) {
    case 1:
        g_camera.camTarget  = CAMTARGET_ATTACKER;
        g_camera.rot.x      = 0;
        g_camera.rot.y      = getFlippedAngle(g_flipPolyChars ? -0x4000 : 0x1555);
        g_camera.targetDist = 0xb333;
        g_camera.interp     = 0x10000;
        g_camera.frame      = 0;
        g_camera.stage++;
        break;

    case 2:
        g_camera.rot.y  += (ANGLE) (rotYMult * -0x580);
        g_camera.interp  = 0x1999;
        if (g_camera.frame == 0x18)
            g_camera.stage++;
        break;

    case 3: {
        VECTOR attackerVec;
        VECTOR victimVec;
        polyCharGetPosition(g_polyCharAttacker, &attackerVec, PCPOS_HEAD);
        polyCharGetPosition(g_polyCharVictim,   &victimVec,   PCPOS_HEAD);
        ANGLE angle = atan2(victimVec.z - attackerVec.z, 0x140000);

        g_camera.camTarget = CAMTARGET_BOTH;
        g_camera.rot.x     = (getPitchBetweenPoints(&attackerVec, &victimVec) >> 1) * rotYMult;
        g_camera.rot.y     = getFlippedAngle(angle);
        g_camera.frame     = 0;
        g_camera.stage++;
        break;
    }

    case 4:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.targetDist = 0xb333;
        g_camera.interp     = 0x1999;
        if (g_camera.frame == 0x1e)
            g_camera.stage = 99;
        break;

    default:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.targetDist = 0xb333;
        g_camera.interp     = 0x4ccc;
        break;
    }
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".camFuncCam1Far")]]
void camFuncCam1Far() {
    int16_t rotYMult = g_flipPolyChars ? -1 : 1;

    switch (g_camera.stage) {
    case 1:
        g_camera.camTarget  = CAMTARGET_ATTACKER;
        g_camera.rot.x      = 0xa00;
        g_camera.rot.y      = getFlippedAngle(0x1555) * rotYMult;
        g_camera.targetDist = 0x9999;
        g_camera.interp     = 0x10000;
        g_camera.frame      = 0;
        g_camera.stage++;
        break;

    case 2:
        g_camera.rot.y += (ANGLE) (rotYMult * -0x580);
        g_camera.interp = 0x1999;
        if (g_camera.frame == 0x18)
            g_camera.stage++;
        break;

    case 3:
        g_camera.camTarget = CAMTARGET_BOTH;
        g_camera.rot.x     = 0xa00;
        g_camera.rot.y     = rotYMult * 0x1400;
        g_camera.stage     = 99;
        break;

    default:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.targetDist = 0x9999;
        g_camera.interp     = 0x1999;
        break;
    }
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".camFuncCam2")]]
void camFuncCam2() {
    int16_t rotYMult  = g_flipPolyChars ? -1 : 1;
    ANGLE rotY        = rotYMult * -0x18e3;
    ANGLE rotYFlipped = (ANGLE) (rotY + 0x8000);

    // This camera has some special triggers.
    if (g_camera.stage != 1) {
        if (g_moveCam2ToVictim)
            g_camera.stage = 98;
        if (g_moveCam2ToAttacker) {
            g_camera.frame = 0;
            g_camera.stage = 50;
        }
    }
    g_moveCam2ToVictim = false;
    g_moveCam2ToAttacker = false;

    switch (g_camera.stage) {
    case 1:
        g_camera.camTarget  = CAMTARGET_ATTACKER;
        g_camera.rot.x      = -0x3e00;
        rotY                = getFlippedAngle(-0x8000);
        g_camera.rot.y      = rotY * rotYMult;
        g_camera.interp     = 0x10000;
        g_camera.frame      = 0;
        g_camera.stage++;
        break;

    case 2:
        g_camera.rot.x  += 0x240;
        g_camera.rot.y  += (ANGLE) (rotYMult * -0x480);
        g_camera.interp  = 0x1999;
        if (g_camera.frame == 0x1e)
            g_camera.stage++;
        break;

    case 3: {
        VECTOR attackerVec;
        VECTOR victimVec;
        polyCharGetPosition(g_polyCharAttacker, &attackerVec, PCPOS_HEAD);
        polyCharGetPosition(g_polyCharVictim,   &victimVec,   PCPOS_HEAD);

        g_camera.rot.x = getPitchBetweenPoints(&attackerVec, &victimVec) >> 1;
        g_camera.frame = 0;
        g_camera.stage++;
        break;
    }

    case 4:
        g_camera.camTarget  = CAMTARGET_ATTACKER;
        g_camera.rot.y      = rotYFlipped;
        g_camera.interp     = 0x1999;
        if (g_camera.frame == 0x1e)
            g_camera.stage = 99;
        break;

    // Snap back to attacker
    case 50:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.rot.y      = rotYFlipped;
        g_camera.interp     = 0x3333;
        if (g_camera.frame == 0x0a /* was 0x1e (30) -- too long for scenario 1! */) {
            g_camera.frame = 0;
            g_camera.stage = 99;
        }
        break;

    // Snap to victim
    case 98:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.rot.y      = rotYFlipped;
        g_camera.interp     = 0x3333;
        break;

    // Done
    case 99:
        // Some spells don't have their own camera and therefore never "zoom out" to the victim.
        // Make sure those spells do indeed show the victim.
        // TODO: This big dumb volatile is to avoid an optimization using __lshrsi3_r0(),
        //       which I'm too dumb to understand. It's probably in 1ST.BIN somewhere.
        auto volatile bigHackSpellValue = g_attackerSpellId_X014;
        if (g_attackerSpellId_X014 == SPELL_CONFUSE ||
            g_attackerSpellId_X014 == SPELL_SLEEP   ||
            (g_attackerSpellId_X014 >= SPELL_BREATH_OF_FIRE && bigHackSpellValue <= SPELL_BREATH_OF_ACID) ||
            g_attackerSpellId_X014 == SPELL_ELBESEM_ORB ||
            g_attackerSpellId_X014 == SPELL_PANIC_AND_CONFUSION)
        {
            g_camera.camTarget = CAMTARGET_BOTH;
        }
        else
            g_camera.camTarget = CAMTARGET_ATTACKER;

        g_camera.rot.y      = rotYFlipped;
        g_camera.interp     = 0x3333;
        break;

    default:
        break;
    }

    // The Queen Worm doesn't fit in the camera! Use special zooming.
    bool isBigAttacker = (g_polyCharAttacker->battleModelId == (0x2000 | MONSTER_QUEEN_WORM));
    g_camera.targetDist = isBigAttacker
        ? ((g_camera.camTarget == CAMTARGET_ATTACKER) ? 0x13333 : 0x10000)
        : ((g_camera.camTarget == CAMTARGET_ATTACKER) ? 0x09999 : 0x0cccc);
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".camFuncCam3Near")]]
void camFuncCam3Near() {
    int16_t rotYMult  = g_flipPolyChars ? -1 : 1;

    VECTOR   vec1;
    VECTOR   vec2;
    polyCharGetPosition(g_polyCharAttacker, &vec1, PCPOS_BBOX_CENTER);
    polyCharGetPosition(g_polyCharVictim,   &vec2, PCPOS_BBOX_CENTER);

    FIXED diffZ = (vec1.z > vec2.z) ? vec1.z - vec2.z : vec2.z - vec1.z;

    switch (g_camera.stage) {
    case 1:
        g_camera.camTarget = CAMTARGET_MANUAL;
        g_camera.rot.x     = -0x3e00;
        g_camera.rot.y     = getFlippedAngle(0x4000) * rotYMult;
        g_camera.zOffset   = 0x1f40000;
        g_camera.frame     = 0;
        g_camera.stage++;

        polyCharGetPosition(g_polyCharAttacker, &vec1, PCPOS_HEAD);
        polyCharGetPosition(g_polyCharVictim,   &vec2, PCPOS_HEAD);

        g_cameraPos.x      = (vec1.x + vec2.x) >> 1;
        g_cameraPos.y      = (vec1.y + vec2.y) >> 1;
        g_cameraPos.z      = (vec1.z + vec2.z) >> 1;
        break;

    case 2:
        g_camera.rot.x  += 0x100;
        g_camera.zOffset = g_camera.zOffset - (0x1c20000 - diffZ) / 0x1e;
        if (g_camera.frame == 0x1e)
            g_camera.stage++;
        break;

    case 3:
        g_camera.camTarget = CAMTARGET_BOTH;
        g_camera.rot.x     = -0x1000;
        g_camera.rot.y     = getFlippedAngle(g_flipPolyChars ? 0x6aaa : 0x1555);
        g_camera.interp    = 0x1999;
        g_camera.stage     = 99;
        break;

    case 4:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.targetDist = 0xb333;
        g_camera.interp     = 0x2666;
        break;
    }
}

// --------------------------------------------------------------------------------------------------------------------

[[gnu::section(".camFuncCam3Far")]]
void camFuncCam3Far() {
    switch (g_camera.stage) {
    case 1:
        g_camera.camTarget = CAMTARGET_MANUAL;
        g_camera.rot.x     = 0x400;
        g_camera.rot.y     = g_flipPolyChars ? -0x8000 : 0;
        g_camera.zOffset   = -0x3200000;
        g_camera.frame     = 0;
        g_camera.stage++;
        polyChar_t *polyChar = g_flipPolyChars ? g_polyCharVictim : g_polyCharAttacker;
        polyCharGetPosition(polyChar, &g_cameraPos, PCPOS_HEAD);
        break;

    case 2:
        g_camera.rot.y  += -0x400;
        g_camera.zOffset = g_camera.zOffset + 0x1e0000;
        if (g_camera.frame == 0x18)
            g_camera.stage++;
        break;

    case 3:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.rot.x      = -0x400;
        g_camera.rot.y      = getFlippedAngle(0x71c);
        g_camera.targetDist = 0xb333;
        g_camera.interp     = 0x3333;
        g_camera.stage      = 99;
        break;

    default:
        g_camera.camTarget  = CAMTARGET_BOTH;
        g_camera.targetDist = 0xb333;
        g_camera.interp     = 0x3333;
        break;
    }
}

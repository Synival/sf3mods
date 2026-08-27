#include "sf3/1st.h"
#include "sf3/x002.h"
#include "sf3/x014.h"

// --------------------------------------------------------------------------------------------------------------------

const battleSceneInfo_t *getBattleSceneInfoForMpdFile(uint16_t mpdFileId);
palette0x20_t *getBattlePaletteById(uint8_t idx);
void buildLightingPalette(palette0x20_t *palette, uint8_t low, uint8_t mid, uint8_t high, uint8_t midIdx, FIXED rTint, FIXED gTint, FIXED bTint);

// --------------------------------------------------------------------------------------------------------------------

#define RGB(r, g, b) \
    ((r << 10) + (g << 5) + b)

alignas(4) static const battleSceneInfo_t g_battleSceneInfos[21] = {
    { 0x01b /* BTL02.MPD */ , 0x02, RGB(0x1f, 0x1f, 0x1f) },
    { 0x018 /* BOCHI.MPD */,  0x03, RGB(0x14, 0x1b, 0x1f) },
    { 0x0a4 /* FURAIN.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x0a9 /* GDI5.MPD */,   0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x0b0 /* HRNAKA.MPD */, 0x01, RGB(0x1f, 0x1f, 0x1f) },
    { 0x0b1 /* HRRAIL.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x0b2 /* INKA00.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x108 /* MGMA00.MPD */, 0x01, RGB(0x1f, 0x18, 0x14) },
    { 0x109 /* MGMA01.MPD */, 0x01, RGB(0x1f, 0x18, 0x14) },
    { 0x128 /* SHIEF1.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x129 /* SHIEF2.MPD */, 0x01, RGB(0x1c, 0x1c, 0x1f) },
    { 0x12a /* SHIEF3.MPD */, 0x01, RGB(0x1f, 0x1f, 0x1f) },
    { 0x12b /* SHIEF4.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x12c /* SHIEF5.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x4a2 /* YAKATA.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },
    { 0x4a4 /* ZLV1.MPD */,   0x00, RGB(0x1b, 0x1d, 0x1f) },
    { 0x4a5 /* ZLV2.MPD */,   0x00, RGB(0x1b, 0x1d, 0x1f) },
    { 0x4a6 /* ZLV3.MPD */,   0x00, RGB(0x1b, 0x1d, 0x1f) },
    { 0x4a7 /* ZLV4.MPD */,   0x00, RGB(0x1b, 0x1d, 0x1f) },
    { 0x4a8 /* ZOKU00.MPD */, 0x00, RGB(0x1f, 0x1f, 0x1f) },

    { (uint16_t) -1, 0x00, 0x0000 },
};

alignas(4) static const palette0x20_t g_battlePaletteTable2[2] = {
    {
        .colors = {
            0xc9ef, 0xb98d, 0xb190, 0xb1b2,
            0xb9f6, 0xbe7c, 0xcedd, 0xef9f,
            0xb9f6, 0xa9ce, 0xa98c, 0xa94a,
            0xa98c, 0xb98d, 0xa98c, 0xa94a,
            0xa94a, 0xa94a, 0xa98e, 0xb1d0,
            0xc5f2, 0xb1d0, 0xb1d0, 0xa94a,
            0xb98d, 0xb98d, 0xc1ce, 0xc1ce,
            0xc9ef, 0xde94, 0xffff, 0xf2f8,
        }
    },
    {
        .colors = {
            0xb96b, 0xa909, 0xa10c, 0xa12e,
            0xa972, 0xadf8, 0xbe59, 0xdf1b,
            0xa972, 0x994a, 0x9908, 0x98c6,
            0x9908, 0xa909, 0x9908, 0x98c6,
            0x98c6, 0x98c6, 0x990a, 0xa14c,
            0xb56e, 0xa14c, 0xa14c, 0x98c6,
            0xa909, 0xa909, 0xb14a, 0xb14a,
            0xb96b, 0xce10, 0x8c62, 0xe274,
        }
    }
};

// --------------------------------------------------------------------------------------------------------------------

const battleSceneInfo_t *getBattleSceneInfoForMpdFile(uint16_t mpdFileId) {
  const battleSceneInfo_t *bsi;

  for (bsi = g_battleSceneInfos; bsi->mpdFileId != 0xFFFF; bsi++)
    if (bsi->mpdFileId == mpdFileId)
        return bsi;

  return g_battleSceneInfos;
}

palette0x20_t *getBattlePaletteById(uint8_t idx) {
    return g_battlePaletteTable1[idx];
}

void buildLightingPalette(palette0x20_t *palette, uint8_t low, uint8_t mid, uint8_t high, uint8_t midIdx, FIXED rTint, FIXED gTint, FIXED bTint) {
  uint8_t  aboveBase;
  uint8_t  base;
  uint8_t  v, i;
  uint8_t  r, g, b;
  color_t *color;
  
  i = 0;
  color = palette->colors;
  for (i = 0; i < 0x20; ++i) {
    if (i < midIdx) {
      base = low;
      aboveBase = (uint8_t) divSigned(i * (mid - low), midIdx);
    }
    else {
      base = mid;
      aboveBase = (uint8_t) divSigned((i - midIdx) * (high - mid), 0x1f - midIdx);
    }

    v = base + aboveBase;
    r = (uint8_t) multFixed(rTint, v);
    g = (uint8_t) multFixed(gTint, v);
    b = (uint8_t) multFixed(bTint, v);

    *color = 0x8000 | r * 0x400 | g * 0x20 | b;
    color++;
  }
}

[[gnu::section(".initLighting")]]
void initLighting() {
    const battleSceneInfo_t *sceneInfo;
    palette0x20_t   *palette_0x01;
    palette0x20_t   *palette_0x02;
    palette0x20_t   *palette_0x0f;

    // We've hijacked a one-time init func with this one. Make sure that same init func happens.
    pd_FUN_060909bc();

    // TODO: This should be pulling from a struct, and referencing it properly!!
    uint16_t mpdFileId = g_saveDataMpdFileId;

    sceneInfo = getBattleSceneInfoForMpdFile(mpdFileId);

    palette_0x01 = getBattlePaletteById(0x01);
    palette_0x02 = getBattlePaletteById(0x02);
    palette_0x0f = getBattlePaletteById(0x0f);

    memcpy(palette_0x02->colors, g_battlePaletteTable2[sceneInfo->lightingStyle & 1].colors, sizeof(palette_0x02->colors));

    uint16_t color = sceneInfo->color;
    FIXED r = ((color & 0x1f) + 1) << 11;
    color >>= 5;
    FIXED g = ((color & 0x1f) + 1) << 11;
    color >>= 5;
    FIXED b = ((color & 0x1f) + 1) << 11;

    // Light
    if ((sceneInfo->lightingStyle & 0x01) == 0) {
        buildLightingPalette(palette_0x01, 0x11, 0x09, 0x1f, 0x0c, r, g, b);
        buildLightingPalette(palette_0x0f, 0x08, 0x08, 0x17, 0x00, r, g, b);
    }
    // Dark
    else {
        buildLightingPalette(palette_0x01, 0x0d, 0x05, 0x1b, 0x0c, r, g, b);
        buildLightingPalette(palette_0x0f, 0x05, 0x05, 0x14, 0x00, r, g, b);
    }

    // Set the light position.
    //
    // For some reason, the values in the PD are miniscule, and don't make much of a difference, at least
    // in Scenario 1. They look correct when amplified like crazy. The models in Scenario 1 also seem to
    // be offset a bit, so we adjust Z to compensate.
    //
    // Values have also had their sign swapped. (Could Scenario 2+ have changed this from positional
    // lighting to directional in a way I didn't notice...?)

    if ((sceneInfo->lightingStyle & 0x02) == 0) {
        g_lightPos.x = ( 0x0000 * 0x100);
        g_lightPos.y = ( 0xdd2b * 0x100);
        g_lightPos.z = (-0x8000 * 0x100) - 0x100000;
    }
    else {
        g_lightPos.x = (-0xb504 * 0x100);
        g_lightPos.y = (-0xb504 * 0x100);
        g_lightPos.z = ( 0x0000 * 0x100) - 0x100000;
    }

    // (fog stuff was here, but I'm not doing that)
}

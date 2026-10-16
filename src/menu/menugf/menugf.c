#include "common.h"
#include "menu_tint.h"
#include "card.h"
#include "menugf.h"
#include "menu.h"
#include "gamestate.h"
#include "character.h"
#include "battle.h"

extern s32 D_801E7E84;

/* Defined last to preserve the original rodata order. */
static const s16 D_801E7DCC[2];
s32 func_801E70A8(s32, s32, s32, s32, s32);
s32 func_801E6884(s32, s32, s32, s32, s32, s32);

s32 func_801E6A8C(s32, s32, s32, s32, s32);

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E5800);

/**
 * @brief Display a GF stat value from a lookup table.
 *
 * Copies 8 halfwords from D_801E7DD0 into a local buffer, indexes
 * by @p a1 to get a base value, adds 0x32, and renders via
 * func_801F0A34 at position (a0, 0) with width 0xD.
 *
 * @param a0 Render context pointer.
 * @param a1 Index into the stat table (0-7).
 */
void func_801E58C8(u8 *a0, s32 a1) {
    s16 buf[32];
    func_801F5984(D_801E7DD0, buf, 8);
    func_801F0A34(a0, 0, buf[a1] + 0x32, 0xD);
}

/**
 * @brief Render a GF ability icon at a grid position.
 *
 * Computes screen coordinates from a linear index @p a0 using an
 * 8-column grid layout: column = a0 % 8 (x = col * 40 + 0x24),
 * row = a0 / 8 (y = row * 72 + 0x46). Calls func_801F0994 to draw.
 *
 * @param a0 Linear index into the ability grid.
 */
INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E592C);

/**
 * @brief Configure GF ability display by looking up base and alternate addresses.
 *
 * Calls getMenuString(0x79) for a base lookup, passes the result with @p a1
 * to copyString. Then calls getMagicNamePtr on @p a0+0x40 for an alternate
 * lookup, passing that result with @p a1 to btlStrcat2.
 *
 * @param a0 Pointer to GF ability data (offset +0x40 used for alternate lookup).
 * @param a1 Destination or context pointer for ability storage.
 */
void func_801E5988(u8 *a0, u8 *a1) {
    s32 val;
    val = getMenuString(0x79);
    copyString(a1, val);
    val = getMagicNamePtr(a0 + 0x40);
    btlStrcat2(a1, val);
}

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E59E0);

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E5A60);

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E6884);

s32 DrawGfGrid(s32 ot, s32 packet, s32 x, s32 y, u16 gfMask) {
    s32 i;
    s32 col;
    s32 row;
    s32 level;

    for (i = 0; i < GF_COUNT; i++) {
        if ((gfMask >> i) & 1) {
            col = (i % 8) * 40 + 12;
            row = (i / 8) * 72 + 14;
            level = g_battleChars.levelEntries[i].level;
            packet = func_801E6884(ot, packet, x + col, y + row, i, level);
        }
    }
    return packet;
}

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E6A8C);

/**
 * @brief Configure GF ability list display and register callback.
 *
 * Sets up g_menuDisplayCfg display config with icon 0x55, dimensions 0x144 x 0x1A,
 * scroll enabled, and page mode. Reads total item count from offset 0x28
 * and data pointer from offset 0x20. Registers func_801E6A8C as callback.
 *
 * @param a0 Source data structure.
 * @param a1 First callback parameter.
 * @param a2 Second callback parameter.
 * @param a3 X position for display config.
 * @param arg4 Y position for display config.
 */
void func_801E6B3C(GfMenuState *a0, s32 a1, s32 a2, s32 a3, s32 arg4) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;

    cfg->iconType = 0x55;
    cfg->iconSubType = 0;
    cfg->x = a3;
    cfg->w = 324;
    cfg->h = 26;
    cfg->columnCount = 1;
    cfg->pageStart = 0;
    cfg->pageEnd = 1;
    cfg->y = arg4;
    cfg->scrollOffset = a0->scroll;
    cfg->dataPtr = a0->items;
    func_801EFBB4(a1, a2, func_801E6A8C);
}

s32 func_801E6BB8(GfMenuState *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    const s16 *list;
    s32 tx = x + 26;
    s32 ty = y + 6;

    if (ctx->unk30 != 0) {
        list = D_801E7DD0;
    } else {
        list = D_801E7DCC;
    }
    pkt = func_801F5A38(ot, pkt, tx, ty, 8, list, 1);
    cfg->iconType = 0;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 244;
    cfg->h = 18;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

/**
 * @brief Set up GF summary display with icon and border rendering.
 *
 * Calls getGfAvailabilityMask to get a status value, then passes it along with
 * position constants to DrawGfGrid for rendering. Configures g_menuDisplayCfg
 * with icon 0x50, position (24, 56), dimensions (336 x 160), and
 * calls func_801EF9AC for final display.
 *
 * @param a0 GF context pointer.
 * @param a1 Render context.
 */
void func_801E6C84(s32 a0, s32 a1) {
    s32 ctx = a0;
    s32 renderCtx = a1;
    s32 result;
    MenuDisplayConfig *cfg;

    result = getGfAvailabilityMask() & 0xFFFF;
    result = DrawGfGrid(ctx, renderCtx, 24, 56, result);
    cfg = &g_menuDisplayCfg;
    cfg->iconType = 0x50;
    cfg->iconSubType = 0;
    cfg->x = 24;
    cfg->y = 56;
    cfg->w = 336;
    cfg->h = 160;
    func_801EF9AC(ctx, result, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

/**
 * @brief Render a GF ability entry with conditional highlight.
 *
 * Tests a bit in the g_gameState ability table at offset 0x4E8, indexed by
 * @p arg4 (stride 152) and shifted by @p arg6. If the bit is set, renders
 * a highlighted entry via drawIcon; otherwise skips. Then renders the
 * ability name and icon via func_801F0FEC and func_801F4EA8.
 *
 * @param a0    Entity/context pointer
 * @param a1    Display string or value (updated if highlighted)
 * @param a2    X position
 * @param a3    Y position
 * @param arg4  GF index (stride 152 into g_gameState)
 * @param arg5  Parameter passed to getCharName
 * @param arg6  Bit shift amount for ability flag test
 * @param arg7  Icon type (u16)
 * @param arg8  Extra parameter for func_801F0FEC
 */
void func_801E6D20(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4, volatile unsigned int arg5, s32 arg6, u16 arg7, s32 arg8) {
    int new_var5;
    s32 new_var;
    s32 new_var4;
    unsigned char new_var3;
    s32 base;
    s32 new_var2;
    s32 ret;
    s32 result;

    new_var = arg5;
    ret = getCharName(new_var);
    new_var3 = 2;
    new_var5 = 0x4E8;
    base = (s32)&g_gameState;
    new_var2 = arg4;

    if (((*((u16 *)((base + ((2 * new_var2) * 76)) + new_var5))) >> arg6) & 1) {
        new_var4 = g_menuTint[MENU_TINT_NORMAL];
        result = (new_var2 = new_var4);
        a1 = drawIcon(a0, a1, 0xC0, a2 - 10, a3, result);
    }

    arg4 = a2;
    do { new_var2 = arg4; } while (0);
    arg6 = a3;
    new_var4 = arg6;
    result = func_801F0FEC(a0, a1, arg4, arg6, ret, arg8);
    func_801F4EA8(a0, ret = result, new_var2 + 0x6C, new_var4 + new_var3, arg7);
}

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E6E3C);

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E70A8);

void func_801E733C(GfMenuState *menu, s32 ot, s32 head, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;

    cfg->iconType = 0x5E;
    cfg->iconSubType = 0;
    cfg->x = x + 144;
    cfg->w = 216;
    cfg->h = 160;
    cfg->columnCount = 11;
    cfg->y = y + 56;
    cfg->pageStart = menu->unk36;
    cfg->pageEnd = menu->unk37;
    cfg->scrollOffset = menu->scroll;
    cfg->itemId = g_gameState.gfs[menu->gfId].learning;
    if (D_801E7E84 >= 12) {
        head = func_801F5F30(ot, head, cfg->x + 40, cfg->y, g_menuTint[MENU_TINT_NORMAL], menu->unk36);
        head = func_801F5F60(ot, head, g_menuTint[MENU_TINT_NORMAL], menu->unk36 == 0 ? 2 : 1);
    }
    func_801EFBB4(ot, head, func_801E70A8);
}

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E7480);

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E77B4);

INCLUDE_ASM("asm/ovl/menugf/nonmatchings/menugf", func_801E7988);

/**
 * @brief Initialize GF menu overlay and register callbacks.
 *
 * Registers func_801E5A60 as the update callback and func_801E7988 as
 * the render callback via func_801F179C. Calls func_801F0948(0) to
 * initialize shared state. If registration succeeds, clears all menu
 * context fields (positions, flags, scroll state), loads the current
 * GF's data via getGfAvailabilityMask/popcount, and enters the update
 * callback.
 */
void func_801E7C20(s32 unused) {
    s32 ctx;

    ctx = func_801F179C((s32)func_801E5A60, (s32)func_801E7988);
    func_801F0948(0);
    if (ctx != 0) {
        *(u8 *)(ctx + 0x30) = 0;
        *(u8 *)(ctx + 0x31) = 0;
        *(u8 *)(ctx + 0x36) = 0;
        *(u8 *)(ctx + 0x37) = 0;
        *(s16 *)(ctx + 0x28) = 0;
        *(u8 *)(ctx + 0x35) = 0;
        *(s32 *)(ctx + 0x20) = 0;
        *(s32 *)(ctx + 0x24) = 0;
        *(s16 *)(ctx + 0x2A) = 0;
        *(u8 *)(ctx + 0x34) = 0;
        *(s16 *)(ctx + 0x2E) = 0;
        *(u8 *)(ctx + 0x33) = popcount(getGfAvailabilityMask());
        *(u8 *)(ctx + 0x56) = 0;
        *(u8 *)(ctx + 0x57) = 0xFF;
        func_801E5A60(ctx);
    }
}

/**
 * @brief Reset GF menu state and redraw.
 *
 * Calls func_801F1DBC to set menu mode to 4 (GF submenu reset),
 * clears the D_801E7E88 flag, and calls func_801E7C20 to redraw.
 *
 * @param a0 Pointer to GF menu context.
 */
void func_801E7CB8(u8 *a0) {
    func_801F1DBC(4);
    D_801E7E88 = 0;
    func_801E7C20(a0);
}

/**
 * @brief Initialize GF menu state and load resources.
 *
 * Sets menu mode to 4 via func_801F1DBC, enables the D_801E7E88 flag,
 * calls func_801E2ABC for setup, loads resources between 0x801D1000
 * and 0x801CD000 via func_801F1210, and redraws via func_801E7C20.
 *
 * @param a0 Pointer to GF menu context.
 */
void func_801E7CF4(u8 *a0) {
    func_801F1DBC(4);
    D_801E7E88 = 1;
    func_801E2ABC(a0);
    func_801F1210(0x801D1000, 0x801CD000);
    func_801E7C20(a0);
}

static const s16 D_801E7DCC[2] = {-1, 0};

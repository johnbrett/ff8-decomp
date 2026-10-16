#include "common.h"
#include "menu.h"
#include "menu_tint.h"
#include "menutmag.h"

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
    /* 0x08 */ u8 unk08[13];
    /* 0x15 */ u8 subOverlay;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18[11];
    /* 0x23 */ u8 showHeader;
    /* 0x24 */ u8 unk24[32];
} TripleMagicEntry;

typedef struct {
    /* 0x00 */ u8 unk00[32];
    /* 0x20 */ s32 brightness;
    /* 0x24 */ s32 fade;
    /* 0x28 */ s32 entryIndex;
    /* 0x2C */ s32 previousEntryIndex;
} TripleMagicContext;

extern u8 D_801E764C[];
extern u8 D_801E63EC[];
extern TripleMagicEntry D_801E63F8[];

void func_801E5800(TripleMagicContext *);
static s32 DrawTripleMagicMenu(TripleMagicContext *, s32, s32);
s32 func_801E606C(s32, s32, TripleMagicEntry *);

INCLUDE_ASM("asm/ovl/menutmag/nonmatchings/menutmag", func_801E5800);

INCLUDE_ASM("asm/ovl/menutmag/nonmatchings/menutmag", func_801E5AF0);

/**
 * @brief Look up a triple magic menu entry address.
 *
 * Indexes into D_801E764C by a0 (halfword stride), loads the offset
 * at +2, and returns base + offset.
 *
 * @param a0 Menu entry index.
 * @return Pointer into D_801E764C data.
 */
s32 func_801E5C0C(s32 a0) {
    u16 *table = (u16 *)D_801E764C;
    return table[a0 + 1] + (s32)D_801E764C;
}

/**
 * @brief Return triple magic data buffer address.
 *
 * @return Constant 0x801CD000.
 */
s32 func_801E5C28(void) {
    return (s32)0x801CD000;
}

INCLUDE_ASM("asm/ovl/menutmag/nonmatchings/menutmag", func_801E5C34);

INCLUDE_ASM("asm/ovl/menutmag/nonmatchings/menutmag", func_801E5D1C);

INCLUDE_ASM("asm/ovl/menutmag/nonmatchings/menutmag", func_801E5E2C);

/**
 * @brief Render a complete triple magic menu entry through multiple rendering passes.
 *
 * Chains five rendering calls in sequence: icon rendering (func_801E5D1C),
 * text rendering (func_801E5C34), color/shade rendering (func_801E5AF0),
 * border rendering (func_8002B898), and GPU primitive setup (func_801E5E2C).
 * Each call's return value becomes the next call's second argument.
 *
 * @param ctx Render context.
 * @param a1 Initial buffer/primitive pointer.
 * @param display Display configuration pointer.
 * @param colorData Color/shading data.
 * @param src Source entry data pointer (passed as 5th arg to sub-calls).
 */
s32 func_801E5F5C(s32 ctx, s32 a1, MenuDisplayConfig *display, s32 colorData, TripleMagicEntry *src) {
    a1 = func_801E5D1C(ctx, a1, display, colorData, src);
    a1 = func_801E5C34(ctx, a1, display, colorData, src);
    a1 = func_801E5AF0(ctx, a1, display, colorData, src);
    a1 = func_8002B898(ctx, a1, display, colorData);
    return func_801E5E2C(ctx, a1, display, colorData, src);
}

/**
 * @brief Set up display config from a source struct and render triple magic entry.
 *
 * Copies four halfwords from the source struct to g_menuDisplayCfg, adding x and y
 * offsets to the first two fields. Then calls func_801E5F5C to perform the
 * actual rendering with the configured display parameters.
 *
 * @param a0 Render context parameter.
 * @param a1 Entry index parameter.
 * @param xOff X offset to add to position.
 * @param yOff Y offset to add to position.
 * @param src Pointer to source coordinate/size struct (4 halfwords).
 */
s32 func_801E6008(s32 a0, s32 a1, s32 xOff, s32 yOff, TripleMagicEntry *src) {

    g_menuDisplayCfg.x = src->x + xOff;
    g_menuDisplayCfg.y = src->y + yOff;
    g_menuDisplayCfg.w = src->w;
    g_menuDisplayCfg.h = src->h;
    return func_801E5F5C(a0, a1, &g_menuDisplayCfg, g_menuTint[MENU_TINT_NORMAL], src);
}

/**
 * @brief Render the triple magic menu title/header area.
 *
 * Creates a display box for the menu header using func_801F08D4, measures the
 * title text width to center it, renders the border and GPU primitives.
 *
 * @param ctx Render context.
 * @param buf Buffer/primitive pointer.
 * @param entryData Entry data pointer (passed to GPU primitive setup).
 */
INCLUDE_ASM("asm/ovl/menutmag/nonmatchings/menutmag", func_801E606C);

static s32 DrawTripleMagicMenu(TripleMagicContext *ctx, s32 ot, s32 head) {
    TripleMagicEntry *entry;

    if (ctx->brightness == 0) {
        return head;
    }
    func_801F1AFC();
    setMenuBrightness(ctx->brightness * ctx->fade / 4096);
    setTextBrightness(ctx->brightness * ctx->fade / 4096);
    entry = D_801E63F8;
    entry += ctx->entryIndex;
    head = func_801E6008(ot, head, 0, 0, entry);
    setMenuBrightness(ctx->brightness);
    setTextBrightness(ctx->brightness);
    if (entry->showHeader != 0) {
        head = func_801E606C(ot, head, entry);
    }
    func_801F1B10();
    return head;
}

/**
 * @brief Initialize and run the triple magic menu overlay.
 *
 * Registers the overlay's main handler and render callback, loads the
 * "mmag.bin" data file, and if an active menu context is returned, looks up
 * the current entry, configures palette and display parameters, and invokes
 * the main state machine (func_801E5800).
 */
void func_801E6290(void) {

    TripleMagicContext *ctx;
    s32 entryIdx;
    TripleMagicEntry *entry;

    ctx = func_801F179C(func_801E5800, DrawTripleMagicMenu);
    func_801F1D2C(0, D_801E63EC, D_801E63F8);

    if (ctx != 0) {
        entryIdx = func_801E2800();
        ctx->entryIndex = entryIdx;
        ctx->previousEntryIndex = entryIdx;
        entry = &D_801E63F8[entryIdx];
        loadSubOverlay(entry->subOverlay + 0x57, D_801E764C);
        func_801E2820(entry->unk16, entry->unk17);
        func_801E5800(ctx);
    }
}

/**
 * @brief Wrapper that calls func_801E6290 (triple magic menu init/update).
 */
void func_801E6348(void) {
    func_801E6290();
}

/**
 * @brief Wrapper that calls func_801E6290 (triple magic menu init/update).
 */
void func_801E6368(void) {
    func_801E6290();
}

/**
 * @brief Wrapper that calls func_801E6290 (triple magic menu init/update).
 */
void func_801E6388(void) {
    func_801E6290();
}

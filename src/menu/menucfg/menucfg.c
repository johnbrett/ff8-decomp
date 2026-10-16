#include "common.h"
#include "menu.h"
#include "menumain.h"
#include "menucfg.h"
#include "thread.h"
#include "gamestate.h"

/** One row of the config table @c D_801E7094: an option id and its state. */
typedef struct {
    u8 id;
    u8 state;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
} CfgEntry;

/* flag_2D gates battle animation options; flag_2E gates analog pad options. */
typedef struct {
    /* 0x00 */ u8 unk00[32];
    /* 0x20 */ u8 *text;
    /* 0x24 */ s16 brightness;
    /* 0x26 */ s16 previewOffset;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ s8 selection;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 entryCount;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 flag_2D;
    /* 0x2E */ u8 flag_2E;
} CfgContext;

/** Terminator id closing the config option table. */
#define CFG_ENTRY_END 0xFF

/** The config option table, CFG_ENTRY_END-terminated. */
extern CfgEntry D_801E7094[];

typedef union {
    /* 0x00 */ void (*apply)(void);
    /* 0x00 */ u8 *text;
} CfgAction;

typedef struct {
    /* 0x00 */ u16 label;
    /* 0x02 */ u16 firstValue;
    /* 0x04 */ u16 secondValue;
    /* 0x06 */ u16 type;
    /* 0x08 */ u16 setting;
    /* 0x0A */ u16 value;
    /* 0x0C */ CfgAction action;
} CfgOption;

extern CfgOption D_801E6FD4[];
extern u16 D_801E70EC;

/* All file-local; the overlay is a single translation unit and only
   func_801E5800 is reached from outside it. */
static s32 func_801E6538(CfgContext *, s32, s32, s32, s32);
static s32 func_801E698C(CfgContext *, s32, s32, s32, s32);
static void func_801E59F8(CfgContext *);
static s32  func_801E5820(CfgContext *arg0);
static void func_801E587C(CfgContext *cfg);
static void func_801E58EC(s32 a0, s32 a1);
static void func_801E5918(s32 a0, s32 a1, s32 a2);
static u8  *func_801E59A0(s32 a0);
static u8  *func_801E59CC(s32 a0);
static s32 func_801E61A0(u8 *text, s32 data, s32 value, s32 x, s32 y);
static s32  func_801E67A8(CfgContext *a0, s32 a1, s32 a2, s32 a3, s32 arg4);

/** @brief Config menu entry point — delegates to func_801F798C. */
void func_801E5800(s32 a0) {
    func_801F798C();
}

/**
 * @brief Count available config menu entries.
 *
 * Walks the @c D_801E7094 table to its @c CFG_ENTRY_END terminator, counting
 * entries that are offered: every one of them when @c flag_2E is set, otherwise
 * only those whose state is not 1.
 *
 * @param arg0 Config menu context.
 * @return Number of available config entries.
 */
static s32 func_801E5820(CfgContext *arg0)
{
    s32 count;
    s32 endId;
    CfgEntry *entry;
    s32 flag;
    s32 stateOn;
    count = 0;
    if (D_801E7094[0].id != CFG_ENTRY_END)
    {
        flag = arg0->flag_2E;
        stateOn = 1;
        endId = CFG_ENTRY_END;
        /* The cached endId/stateOn and this empty statement are load-bearing:
           spelling the loop with plain literals costs the match. */
        do { } while (0);
        entry = D_801E7094;
        do
        {
            if ((flag != 0) || (entry->state != stateOn))
            {
                count++;
            }
            entry++;
        }
        while (entry->id != endId);
    }
    return count;
}

/**
 * @brief Initialize config menu availability flags.
 *
 * Sets both availability flags, then clears whichever the hardware does not
 * support. @c func_80027DB4 reads an analog axis, so a negative result means no
 * analog pad answered and @c flag_2E is cleared. @c flag_2D is cleared unless a
 * battle animation is both active and reports a nonzero field 0x0B.
 *
 * @param cfg Config menu context.
 */
static void func_801E587C(CfgContext *cfg) {
    s32 val = 1;
    cfg->flag_2E = val;
    cfg->flag_2D = val;
    if (func_80027DB4(0, PAD_AXIS_X2, 0) < 0) {
        cfg->flag_2E = 0;
    }
    if (isPadConnected() == 0 || getPadField0B(0) == 0) {
        cfg->flag_2D = 0;
    }
}

/**
 * @brief Render a config option label at a grid position.
 *
 * Computes y-coordinate from @p a1 (row * 16 + 0x24) and renders
 * a string of width 0x30 at that position via func_801F0A34.
 *
 * @param a0 Render context pointer.
 * @param a1 Row index (0-based).
 */
static void func_801E58EC(s32 a0, s32 a1) {
    func_801F0A34(a0, 0, 0x30, a1 * 16 + 0x24);
}

/**
 * @brief Render a config option value at a computed grid position.
 *
 * Computes a horizontal offset by looking up a volume/level table entry
 * from D_801FA3C8 (indexed by a2 / 64), scaling it by 150/4096, and
 * adding 0x5A. Reads the y-offset from the D_801E7094 config entry table
 * at index a1 (byte at offset 3) and adds 0x2F. Then renders via
 * func_801F0A34.
 *
 * @param a0 Render context pointer.
 * @param a1 Config entry index.
 * @param a2 Raw value (divided by 64 to index the table).
 */
static void func_801E5918(s32 a0, s32 a1, s32 a2) {
    a2 = D_801FA3C8[a2 / 64];
    a2 = a2 * 150 / 4096;
    func_801F0A34(a0, 0, a2 + 0x5A, D_801E7094[a1].unk03 + 0x2F);
}

/** @brief Look up string @p a0 in menu text category 2. */
static u8 *func_801E59A0(s32 a0) {
    return func_801F08D4(1, 2, a0, 0);
}

/** @brief Look up string @p a0 in menu text category 2, with the last flag set. */
static u8 *func_801E59CC(s32 a0) {
    return func_801F08D4(1, 2, a0, 1);
}

INCLUDE_ASM("asm/ovl/menucfg/nonmatchings/menucfg", func_801E59F8);

static s32 func_801E61A0(u8 *text, s32 data, s32 value, s32 x, s32 y)
{
    MenuDisplayConfig *s = &g_menuDisplayCfg;
    s32 xoff = x + 10;
    s32 yoff = y + 7;

    if (text != NULL)
    {
        value = func_801F0FEC(data, value, xoff, yoff, text, 7);
    }

    s->iconType = 0x55;
    s->iconSubType = 0;
    s->x = x;
    s->w = 0xF4;
    s->y = y;
    s->h = 0x16;

    return func_801EF9AC(data, value, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menucfg/nonmatchings/menucfg", func_801E625C);

static s32 DrawConfigHeading(CfgContext *cfg, s32 data, s32 value, s32 x, s32 y) {
    s32 textY = y + 5;
    u8 *text = func_801E59A0(cfg->selection + 50);
    s32 textWidth = getFirstLineWidth(text);
    s32 width = 284;
    textWidth = width - textWidth;
    value = func_801F0FEC(data, value, x + textWidth / 2, textY, text, 7);
    g_menuDisplayCfg.iconType = 0;
    g_menuDisplayCfg.iconSubType = 0;
    g_menuDisplayCfg.x = x;
    g_menuDisplayCfg.y = y;
    g_menuDisplayCfg.w = width;
    g_menuDisplayCfg.h = 20;
    value = func_801F5F60(data, value, g_menuTint[MENU_TINT_NORMAL], 3);
    value = func_801EF9AC(data, value, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
    return value;
}

INCLUDE_ASM("asm/ovl/menucfg/nonmatchings/menucfg", func_801E6538);

static s32 func_801E67A8(CfgContext *a0, s32 a1, s32 a2, s32 a3, s32 arg4) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;

    cfg->iconType = 0;
    cfg->iconSubType = 0;
    cfg->x = a3;
    cfg->w = 284;
    cfg->h = 37;
    cfg->y = arg4;
    return func_801EF9AC(a1, a2, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

static s32 DrawConfigFooter(CfgContext *cfg, s32 data, s32 value, s32 x, s32 y) {
    u8 *text = func_801E59A0(64);
    s32 textWidth = getTextSize(text) & 0xFFFF;
    s32 width = 284;
    textWidth = width - textWidth;

    value = func_801F0FEC(data, value, x + textWidth / 2, y + 5, text, 7);
    g_menuDisplayCfg.iconType = 0;
    g_menuDisplayCfg.iconSubType = 0;
    g_menuDisplayCfg.x = x;
    g_menuDisplayCfg.y = y;
    g_menuDisplayCfg.w = width;
    g_menuDisplayCfg.h = 20;
    value = func_801EF9AC(data, value, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
    return value;
}

static s32 DrawConfigPreview(CfgContext *cfg, s32 data, s32 value, s32 x, s32 y) {
    s32 offsetY = y + 27;
    value = DrawConfigHeading(cfg, data, value, x, offsetY);
    offsetY = y + 47;
    value = func_801E6538(cfg, data, value, x, offsetY);
    offsetY = y + 158;
    value = func_801E67A8(cfg, data, value, x, offsetY);
    offsetY = y + 195;
    value = DrawConfigFooter(cfg, data, value, x, offsetY);
    return value;
}

INCLUDE_ASM("asm/ovl/menucfg/nonmatchings/menucfg", func_801E698C);

static s32 DrawConfigMenu(CfgContext *cfg, s32 data, s32 value) {
    s32 head;
    s32 offset;
    s32 y;
    func_801F1AFC();
    setMenuBrightness(cfg->brightness);
    head = getDisplayListHead();
    if (cfg->previewOffset < 4096) {
        offset = D_801FA3C8[cfg->previewOffset / 64];
        offset = offset * 150 / 4096;
        value = DrawConfigPreview(cfg, data, value, offset + 75, 0);
    }
    y = 31;
    value = func_801E698C(cfg, data, value, 24, y);
    y = 6;
    value = func_801E61A0(cfg->text, data, value, 24, y);
    func_801F1B10();
    storeGpuPacket(head);
    return value;
}

static void InitializeConfigMenu(void) {
    CfgContext *cfg = func_801F179C(func_801E59F8, DrawConfigMenu);
    u8 *settings = (u8 *)&g_gameState.config;
    CfgOption *option;
    s32 type;
    D_801E70EC = 0;
    func_801F0948(0);
    while (1) {
        option = &D_801E6FD4[D_801E70EC];
        if (option->label == 0xFFFF) {
            break;
        }
        type = option->type;
        if (type < 6) {
            if (type >= 3) {
                option->value = (4 - settings[option->setting]) * 1024;
            }
        }
        D_801E70EC++;
    }
    if (cfg != NULL) {
        func_801E587C(cfg);
        cfg->brightness = 0;
        cfg->previewOffset = 4096;
        cfg->selection = 0;
        cfg->entryCount = func_801E5820(cfg);
        func_801E59F8(cfg);
    }
}

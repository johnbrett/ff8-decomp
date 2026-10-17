#include "common.h"
#include "battle.h"
#include "menu.h"
#include "menumain.h"
#include "menusts.h"
#include "numstr.h"
#include "gamestate.h"
#include "ui/icon.h"
#include "ui/font.h"
#include "game.h"
#include "kernel.h"
#include "battle_results/number.h"

typedef struct {
    /* 0x00 */ u8 pad00[32];
    /* 0x20 */ MenuParentCtx *parent;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad28[2];
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E[3];
    /* 0x34 */ u16 openProgress;
    /* 0x36 */ u8 charIdx;
    /* 0x37 */ u8 pad37[3];
    /* 0x3A */ u8 trickLearning;
    /* 0x3B */ s8 unk3B;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ u8 pad3D[4];
    /* 0x41 */ u8 unk41[8];
} StatusMenuTask;

#define STAT_ROW_SUFFIX 0x01 /* draws string 20 after the value */
#define STAT_ROW_CONV_A 0x10 /* value goes through func_801F7BAC */
#define STAT_ROW_CONV_B 0x20 /* value goes through func_801F7BE4 */

typedef struct {
    /* 0x00 */ u16 icon;
    /* 0x02 */ u16 flags;
    /* 0x04 */ u16 offset; /* byte offset of the value in the stats block; 0xFFFF ends the table */
    /* 0x06 */ u16 x;
    /* 0x08 */ u16 y;
} StatRow;

extern StatRow D_801E954C[];

typedef struct {
    /* 0x00 */ u8 first; /* 0xFF: no limit break list */
    /* 0x01 */ u8 last;
} LimitBreakRange;

extern LimitBreakRange D_801E9604[];

extern StatusEntry D_801E95A8[];
extern u8 D_801EA284[];
extern u8 D_801EA28C;
s32 func_801E5D28(StatusMenuTask *, s32, s32, s32);
s32 func_801E69E4(s32, s32, s32, s32, s32, s32);
void func_801E62A8(StatusMenuTask *);

/* The status slide calculation needs a full-width return for the match. */
s32 func_801E5800(s32 a0) {
    return D_801FA3C8[a0 / 64];
}

/**
 * @brief Look up status display type byte.
 *
 * @param index Status entry index.
 * @return Type byte.
 */
u8 func_801E582C(s32 index) {
    MenustsStatusEntry *entry = D_801E9964;
    entry += index;
    return entry->type;
}

/**
 * @brief Compute status display x-position.
 *
 * @param index Status entry index.
 * @return Computed address.
 */
u8 *func_801E5848(s32 index) {
    MenustsStatusEntry *entry = D_801E9964;
    u8 *coordBase = D_801E99AC;
    entry += index;
    return coordBase + entry->xOff;
}

/**
 * @brief Compute status display y-position.
 *
 * @param index Status entry index.
 * @return Computed address.
 */
s32 func_801E586C(s32 index) {
    MenustsStatusEntry *entry = D_801E9964;
    u8 *coordBase = D_801E99AC;
    entry += index;
    return (s32)coordBase + entry->yOff;
}

/**
 * @brief Wrapper that calls getMagicNamePtr with @p a0 offset by 0x33.
 */
u8 *func_801E5890(s32 a0) {
    return getMagicNamePtr(a0 + 0x33);
}

/**
 * @brief Wrapper that calls getSpellDesc with @p a0 offset by 0x33.
 */
void func_801E58B0(s32 a0) {
    getSpellDesc(a0 + 0x33);
}

/** @brief Look up string @p a0 in menu text category 7. */
u8 *func_801E58D0(s32 a0) {
    return func_801F08D4(1, 7, a0, 0);
}

/** @brief Look up string @p a0 in menu text category 7, with the last flag set. */
u8 *func_801E58FC(s32 a0) {
    return func_801F08D4(1, 7, a0, 1);
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E5928);

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E5D28);

void func_801E61B0(StatusMenuTask *ctx, s32 ot, s32 pkt) {
    s32 xOffset = func_801E5800(4096 - ctx->openProgress) * 384 / 4096;

    g_gameState.mainData.fieldD20 ^= 0x8000; /* unknown status drawing flag */
    func_801E5D28(ctx, ot, pkt, -xOffset);
    g_gameState.mainData.fieldD20 ^= 0x8000; /* unknown status drawing flag */
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E6254);

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E62A8);

s32 DrawHelpPanel(s32 ot, s32 pkt, s32 x, s32 y, u8 *text) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    u8 buf[128];
    s32 tx;
    s32 ty;

    if (text != NULL) {
        tx = x + 10;
        ty = y + 9;
        decodeMessage(text, buf, -1);
        pkt = func_801F0FEC(ot, pkt, tx, ty, buf, 7);
    }
    cfg->iconType = 0x55;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 324;
    cfg->h = 26;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

/**
 * @brief Configure and draw a status menu panel border.
 *
 * Sets up g_menuDisplayCfg with no icon, position from a2/a3,
 * fixed size (0xF4 x 0x12), then draws via func_801EF9AC.
 *
 * @param a0 Display list pointer
 * @param a1 OT pointer
 * @param a2 X position
 * @param a3 Y position
 */
void func_801E6994(s32 a0, s32 a1, s16 a2, s16 a3) {

    s32 cfg = (s32)&g_menuDisplayCfg;

    *(u8 *)(cfg + 0x10) = 0;
    *(u8 *)(cfg + 0x11) = 0;
    *(s16 *)cfg = a2;
    *(s16 *)(cfg + 0x4) = 0xF4;
    *(s16 *)(cfg + 0x6) = 0x12;
    *(s16 *)(cfg + 0x2) = a3;
    func_801EF9AC(a0, a1, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E69E4);

s32 DrawGfListPanel(s32 ctx, s32 ot, s32 pkt, s32 x, s32 y, s32 tint) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 tx = x + 26;
    s32 ty = y + 9;
    s32 i;

    for (i = 0; i < GF_COUNT; i++) {
        pkt = func_801E69E4(ctx, ot, pkt, tx, ty, i);
    }
    cfg->iconType = 0x50;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 336;
    cfg->h = 119;
    return func_801EF9AC(ot, pkt, tint, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E6C68);

s32 func_801E6EA0(s32 ot, s32 pkt, s32 x, s32 y, s32 mode) {
    u8 strBuf[16];
    StatusEntry *entry = D_801E95CC;
    s32 i = 0;
    s32 digitBase = g_numberFormat.digits[0];
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    u8 *percent = func_801F6AFC(20);
    u8 *valueStr = &strBuf[2];
    s32 textX;
    s32 textY;

    while (1) {
        if (entry->statusId == 0xFF) {
            break;
        }
        textX = x + entry->x;
        textY = y + entry->y;
        pkt = drawIcon(ot, pkt, entry->statusId, textX, textY, g_menuTint[MENU_TINT_NORMAL]);
        textX += 54;
        textY += 4;
        intToDecStringShort(func_801F5104(D_801E9EE4.statusResistances[i]), strBuf, digitBase);
        replaceLeadingZeros(valueStr, 2, digitBase, *getMenuString(0xB));
        pkt = func_8002C56C(ot, pkt, textX, textY, valueStr, 7);
        pkt = func_8002C56C(ot, pkt, textX + 24, textY + 1, percent, 7);
        i++;
        entry++;
    }

    if (isMcBusy() == 4) {
        cfg->iconType = 0xFD;
    } else {
        cfg->iconType = 0xD1;
    }
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 194;
    cfg->h = 100;
    return func_801EF9AC(ot, pkt, mode, g_menuTint[MENU_TINT_NORMAL]);
}

s32 func_801E709C(s32 ot, s32 pkt, s32 x, s32 y, s32 mode) {
    u8 strBuf[16];
    StatusEntry *entry = D_801E95A8;
    s32 i = 0;
    s32 digitBase = g_numberFormat.digits[0];
    MenuDisplayConfig *cfgPtr = &g_menuDisplayCfg;
    u8 *percent = func_801F6AFC(20);
    s32 drawn = 0;

    while (1) {
        if (entry->statusId == 0xFF) {
            break;
        }
        if ((D_801E9EE4.atkElements >> i) & 1) {
            pkt = drawIcon(ot, pkt, entry->statusId, x + 10, y + 14, g_menuTint[MENU_TINT_NORMAL]);
            intToDecStringShort(D_801E9EE4.atkElementPercent, strBuf, digitBase);
            replaceLeadingZeros(&strBuf[2], 2, digitBase, *getMenuString(0xB));
            pkt = func_8002C56C(ot, pkt, x + 90, y + 18, &strBuf[2], 7);
            pkt = func_8002C56C(ot, pkt, x + 114, y + 19, percent, 7);
            drawn = 1;
            break;
        }
        i++;
        entry++;
    }

    if (drawn) {
        if (isMcBusy() == 4) {
            cfgPtr->iconType = 0xFE;
        } else {
            cfgPtr->iconType = 0xD2;
        }
        cfgPtr->iconSubType = 0;
        cfgPtr->w = 130;
        cfgPtr->x = x;
        cfgPtr->y = y;
        cfgPtr->h = 40;
        pkt = func_801EF9AC(ot, pkt, mode, g_menuTint[MENU_TINT_NORMAL]);
    }
    return pkt;
}

/** @brief Build status bitfield from character data flags. */
s32 func_801E7278(BattleCharData *cd) {
    s32 result = cd->atkPersistentStatus & 0x7F;
    s32 flags = cd->atkBattleStatus;

    if (flags & 0x1) result |= 0x80;
    if (flags & 0x4) result |= 0x100;
    if (flags & 0x8) result |= 0x200;
    if (flags & 0x200) result |= 0x400;
    if (flags & 0x4000) result |= 0x800;
    if (flags & 0x8000) result |= 0x1000;
    return result;
}

/**
 * @brief Render character status icons + atkStatusHit values.
 *
 * Walks D_801E95CC (status entry table, sentinel 0xFF) and for each
 * status flag set in the character's bitfield, draws the status text
 * icon and the (atkStatusHit - 100) numeric value, up to 3 entries.
 * Then draws the surrounding panel via func_801EF9AC if any entries
 * were drawn.
 *
 * @param displayList GPU display list pointer.
 * @param ot          Ordering table pointer (returned chained).
 * @param x           Panel base X position.
 * @param y           Panel base Y position.
 * @param mode        Render mode passed to func_801EF9AC.
 * @return Updated OT pointer.
 */
s32 func_801E72D8(s32 displayList, s32 ot, s32 x, s32 y, s32 mode) {
    u8 strBuf[16];
    StatusEntry *entry = D_801E95CC;
    s32 i = 0;
    s32 digitBase = g_numberFormat.digits[0];
    s32 drawn;
    s32 yStep;
    MenuDisplayConfig *cfgPtr;
    u8 *strBuf2;
    void *bgBuf;
    s32 statusFlags;
    s32 yPos;

    cfgPtr = &g_menuDisplayCfg;
    bgBuf = func_801F6AFC(0x14);
    drawn = i;
    statusFlags = func_801E7278(&D_801E9EE4);
    strBuf2 = &strBuf[2];
    yStep = 0xA;

    while (1) {
        s32 mask;
        if (entry->statusId == 0xFF) break;
        mask = 1 << i;
        if (statusFlags & mask) {
            if (drawn >= 3) break;
            yPos = y + yStep;
            ot = drawIcon(displayList, ot, entry->statusId, x + 0xA, yPos, g_menuTint[MENU_TINT_NORMAL]);
            drawn++;
            yPos += 4;
            intToDecStringShort(D_801E9EE4.atkStatusHitChance - 100, strBuf, digitBase);
            replaceLeadingZeros(strBuf2, 2, digitBase, *getMenuString(0xB));
            ot = func_8002C56C(displayList, ot, x + 0x5A, yPos, strBuf2, 7);
            ot = func_8002C56C(displayList, ot, x + 0x72, yPos + 1, bgBuf, 7);
            yStep += 0xE;
        }
        i++;
        entry++;
    }

    if (drawn != 0) {
        if (isMcBusy() == 4) {
            *(u8 *)((s32)cfgPtr + 0x10) = 0xFC;
        } else {
            *(u8 *)((s32)cfgPtr + 0x10) = 0xD0;
        }
        cfgPtr->iconSubType = 0;
        cfgPtr->x = x;
        cfgPtr->y = y;
        cfgPtr->w = 0x82;
        cfgPtr->h = 0x38;
        ot = func_801EF9AC(displayList, ot, mode, g_menuTint[MENU_TINT_NORMAL]);
    }

    return ot;
}

s32 DrawLimitBreakList(s32 ot, s32 pkt, s32 x, s32 y, s32 unused, s32 character) {
    LimitBreakRange *range = D_801E9604;
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 textX;
    s32 textY;
    s32 clut;
    s32 i;
    s32 last;

    range += character;
    x += 24;
    y += 187;
    textY = y + 9;
    textX = x + 26;
    if (range->first == 0xFF) {
        return pkt;
    }
    clut = 7;
    if (func_801F79F8(SEALED_LIMIT_BREAK)) {
        clut = 1;
    }
    i = range->first;
    last = range->last;
    for (; i <= last; i++) {
        pkt = func_801F0FEC(ot, pkt, textX, textY, getTempLimitBreakName(i), clut);
        textY += 13;
    }
    cfg->iconType = 0x4E;
    cfg->w = 158;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->h = 28;
    return pkt;
}

/**
 * @brief Compute centered X position after subtracting rendered width.
 * @param a0 Base X position
 * @param a1 Total available width
 * @param a2 Text or item to measure via getFirstLineWidth
 * @return Base X + (available width - rendered width) / 2
 */
s32 func_801E7644(s32 a0, s32 a1, u8 *a2) {
    s32 rendered = getFirstLineWidth(a2);
    return a0 + (a1 - rendered) / 2;
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E7690);

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E7B20);

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E7D04);

s32 func_801E811C(s32 ot, s32 pkt, s32 x, s32 y) {
    s32 next;
    s32 textX;
    s32 textY;

    x += 24;
    y += 187;
    textX = x + 26;
    textY = y + 9;
    next = func_801F0FEC(ot, pkt, textX, textY, func_801E5848(8), 7);
    g_menuDisplayCfg.iconType = 0x4E;
    g_menuDisplayCfg.iconSubType = 0;
    g_menuDisplayCfg.x = x;
    g_menuDisplayCfg.y = y;
    g_menuDisplayCfg.w = 158;
    g_menuDisplayCfg.h = 28;
    return next;
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E81B8);

s32 func_801E8598(s32 unused, s32 ot, s32 pkt, s32 x, s32 y) {
    s32 learned;
    s32 color = 7;
    s32 n = 0;
    MenuDisplayConfig *cfg;
    s32 i;
    s32 bit;
    s32 textX;
    s32 textY;

    x += 24;
    y += 161;
    cfg = &g_menuDisplayCfg;
    learned = g_gameState.mainData.limitBreaks.selphieLimits;
    if (func_801F79F8(SEALED_LIMIT_BREAK)) {
        color = 1;
    }
    for (i = 0; i < 6; i++) {
        bit = 1 << i;
        if (learned & bit) {
            textX = x + 25;
            textY = y + 8;
            textX += (n % 2) * 160;
            textY += (n / 2) * 13;
            pkt = func_801F0FEC(ot, pkt, textX, textY, func_801E5890(i), color);
            n++;
        }
    }
    cfg->iconType = 0x4E;
    cfg->w = 336;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->h = 55;
    return pkt;
}

s32 func_801E86F0(s32 unused, s32 ot, s32 pkt, s32 x, s32 y) {
    s32 learned;
    MenuDisplayConfig *cfg;
    s32 n = 0;
    s32 color = 7;
    s32 i;
    s32 bit;
    s32 textX;
    s32 textY;

    learned = g_gameState.mainData.limitBreaks.quistisLimits;
    x += 24;
    cfg = &g_menuDisplayCfg;
    y += 96;
    if (func_801F79F8(SEALED_LIMIT_BREAK)) {
        color = 1;
    }
    for (i = 0; i < 16; i++) {
        bit = 1 << i;
        if (learned & bit) {
            textX = x + 26 + (n % 2) * 180;
            textY = y + 9 + (n / 2) * 13;
            pkt = func_801F0FEC(ot, pkt, textX, textY, getBlueMagicName(i), color);
            n++;
        }
    }
    cfg->iconType = 0x4E;
    cfg->w = 336;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->h = 119;
    return pkt;
}

/**
 * @brief Status menu render wrapper with stat type 6.
 * @param a0 Unused parameter
 * @param a1 First render parameter
 * @param a2 Second render parameter
 * @param a3 Third render parameter
 * @param arg5 Fourth render parameter
 * @param arg6 Fifth render parameter
 */
void func_801E8850(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5, s32 arg6) {
    DrawLimitBreakList(a1, a2, a3, arg5, arg6, 6);
}

/**
 * @brief Status menu render wrapper with stat type 7.
 * @param a0 Unused parameter
 * @param a1 First render parameter
 * @param a2 Second render parameter
 * @param a3 Third render parameter
 * @param arg5 Fourth render parameter
 * @param arg6 Fifth render parameter
 */
void func_801E8890(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5, s32 arg6) {
    DrawLimitBreakList(a1, a2, a3, arg5, arg6, 7);
}

/**
 * @brief Status menu render wrapper with stat type 8.
 * @param a0 Unused parameter
 * @param a1 First render parameter
 * @param a2 Second render parameter
 * @param a3 Third render parameter
 * @param arg5 Fourth render parameter
 * @param arg6 Fifth render parameter
 */
void func_801E88D0(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5, s32 arg6) {
    DrawLimitBreakList(a1, a2, a3, arg5, arg6, 8);
}

/**
 * @brief Status menu render wrapper with stat type 9.
 * @param a0 Unused parameter
 * @param a1 First render parameter
 * @param a2 Second render parameter
 * @param a3 Third render parameter
 * @param arg5 Fourth render parameter
 * @param arg6 Fifth render parameter
 */
void func_801E8910(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5, s32 arg6) {
    DrawLimitBreakList(a1, a2, a3, arg5, arg6, 9);
}

/**
 * @brief Status menu render wrapper with stat type 0xA.
 * @param a0 Unused parameter
 * @param a1 First render parameter
 * @param a2 Second render parameter
 * @param a3 Third render parameter
 * @param arg5 Fourth render parameter
 * @param arg6 Fifth render parameter
 */
void func_801E8950(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5, s32 arg6) {
    DrawLimitBreakList(a1, a2, a3, arg5, arg6, 10);
}

/**
 * @brief Dispatch a status rendering operation through a function table.
 *
 * Looks up a function pointer from D_801E961C[a1], calls it with
 * (a0, a2, a3, stackArg1, stackArg2), then passes the result and
 * other parameters to func_801EF9AC for GPU display.
 *
 * @param a0 Status entry data pointer
 * @param a1 Function table index
 * @param a2 Parameter passed as a1 to table function, then as a0 to func_801EF9AC
 * @param a3 Parameter passed as a2 to table function
 * @param stackArg1 Passed as a3 to table function, then as stack arg to func_801EF9AC
 * @param stackArg2 Passed as stack arg to table function, then as a2 to func_801EF9AC
 */
void func_801E8990(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5, s32 arg6, s32 arg7) {
    s32 (*fn)(s32, s32, s32, s32, s32, s32) = (void *)D_801E961C[a1];
    s32 result = fn(a0, a2, a3, arg5, arg6, arg7);
    func_801EF9AC(a2, result, arg7, g_menuTint[MENU_TINT_NORMAL]);
}

void *DrawStatRows(void *ot, void *pkt, s32 x, s32 y, u8 *stats) {
    StatRow *row = D_801E954C;
    s32 clut = 7; /* kept as a variable for the match */
    s32 rowX;
    s32 rowY;
    s32 xy;
    s32 value;

    while (1) {
        if (row->offset == 0xFFFF) {
            break;
        }
        rowX = x + row->x;
        rowY = y + row->y;
        pkt = drawIconClut(ot, pkt, row->icon, rowX, rowY, g_menuTint[MENU_TINT_NORMAL], clut == 0 ? 0x1C0 : 0x80);
        rowX += 56;
        xy = (rowY << 16) | (rowX & 0xFFFF);
        value = stats[row->offset];
        if (row->flags & STAT_ROW_CONV_A) {
            value = func_801F7BAC(value);
        }
        if (row->flags & STAT_ROW_CONV_B) {
            value = func_801F7BE4(value);
        }
        pkt = drawNumber(ot, pkt, xy, value, g_menuTint[MENU_TINT_NORMAL], clut);
        if (row->flags & STAT_ROW_SUFFIX) {
            pkt = func_8002C56C(ot, pkt, rowX, rowY + 2, func_801F6AFC(20), clut);
        }
        row++;
    }
    return pkt;
}

s32 func_801E8BAC(s32 ot, s32 pkt, s32 x, s32 y, CharMenuInfo *info) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 tint = g_menuTint[MENU_TINT_NORMAL];
    s32 dy;
    s32 color = 7;
    s32 i;

    x += 200;
    y += 152;
    for (i = 0, dy = 7; i < 4; i++) {
        s32 abilityId = info->abilities[i].abilityId;

        if (abilityId != 0) {
            s32 ty = y + dy;

            pkt = drawIcon(ot, pkt, info->abilities[i].icon, x + 10, ty - 2, tint);
            pkt = func_801F0FEC(ot, pkt, x + 24, ty, getAbilityName(abilityId), color);
        }
        dy += 13;
    }
    cfg->iconType = 0x5E;
    cfg->w = 154;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->h = 64;
    return func_801EF9AC(ot, pkt, 0x1000, tint);
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E8CE4);

/**
 * @brief Conditionally transform a value before passing to the status renderer.
 *
 * If the signed byte at a0+0x3B is non-negative, calls func_801F6FE4
 * with (a1, a2, 1, 0x1000) and uses the result as a2. Then calls
 * func_801E8CE4 with the original a0, a1, and the (possibly modified) a2.
 *
 * @param a0 Pointer to status entry structure.
 * @param a1 First render parameter.
 * @param a2 Second render parameter (may be replaced by func_801F6FE4 result).
 */
void func_801E9118(u8 *a0, s32 a1, s32 a2) {
    s8 val = *(s8 *)(a0 + 0x3B);
    if (val >= 0) {
        a2 = func_801F6FE4(a1, a2, 1, 0x1000);
    }
    func_801E8CE4(a0, a1, a2);
}

void func_801E9178(void) {
    s32 first = 0xFF;
    s32 last = 0;
    ShotEntry *shot = g_kernel.shot;
    u8 *slot;
    s32 ammo;
    s32 i;

    for (i = 0; i < 8; i++) {
        D_801EA284[i] = 0;
    }
    for (i = 0; i < 8; i++, shot++) {
        ammo = shot->ammoItem;
        if (ammo < first) {
            first = ammo;
        }
        if (last < ammo) {
            last = ammo;
        }
    }
    /* Byte-wise inventory traversal is needed for the match. */
    slot = &g_gameState.mainData.itemSlots[0].id;
    for (i = 0; i < ITEM_SLOT_COUNT; i++) {
        s32 id = *slot++;
        s32 count = *slot++;

        if (count != 0 && id >= first && id <= last) {
            id -= first;
            D_801EA284[id] = count;
        }
    }
    D_801EA28C = first;
}

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E923C);

INCLUDE_ASM("asm/ovl/menusts/nonmatchings/menusts", func_801E936C);

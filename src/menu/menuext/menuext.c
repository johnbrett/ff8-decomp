#include "common.h"
#include "battle_results/number.h"
#include "menu.h"
#include "menumain.h"
#include "character.h"
#include "menuext.h"
#include "gamestate.h"
#include "ui/icon.h"
#include "ability_list.h"

typedef struct {
    /* 0x00 */ u16 nameOffset;
    /* 0x02 */ u16 yield;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 srcId;
    /* 0x06 */ u8 cost;
    /* 0x07 */ u8 dstId;
} ExtEntry;

typedef struct {
    /* 0x00 */ u8 pad00[36];
    /* 0x24 */ ExtEntry *entries;
    /* 0x28 */ u8 pad28[8];
    /* 0x30 */ u8 *unk30;
    /* 0x34 */ u8 *unk34;
    /* 0x38 */ u8 pad38[2];
    /* 0x3A */ u16 scroll;
    /* 0x3C */ u8 pad3C[6];
    /* 0x42 */ u8 pageStart;
    /* 0x43 */ u8 pageEnd;
    /* 0x44 */ u8 pad44;
    /* 0x45 */ u8 mode;
    /* 0x46 */ u8 entryCount;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ u8 charIdx;
    /* 0x49 */ u8 pad49[2];
    /* 0x4B */ u8 magicId;
    /* 0x4C */ u8 pad4C;
    /* 0x4D */ u8 entryIdx;
    /* 0x4E */ s8 srcCount;
    /* 0x4F */ s8 unk4F;
    /* 0x50 */ s8 dstCount;
    /* 0x51 */ u8 pad51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 state; /* 0xFF = inactive */
} ExtMenuCtx;

extern u8 *getMagicNamePtr(s32 magicId);
s32 func_801E5B88(s32, ExtEntry *, s32, s32, s32, s32);
s32 func_801E76D4(s32, s32, s32, s32, s32);
s32 func_801E7858(s32, s32, s32, s32, s32);

extern u8 D_801E8C10[];
extern u8 D_801E8C20[];
extern u8 D_801E9600[];
s32 func_801E7D88(s32, s32, s32, s32, s32);

/**
 * @brief Clear 8 bytes of extension state at D_801E8C10.
 *
 * Iterates backwards from index 7 to 0, setting each byte to zero.
 */
void func_801E5800(void) {
    s32 i = 7;
    s32 base = (s32)D_801E8C10;
    u8 *ptr = (u8 *)(base + 7);
top:
    *ptr = 0;
    i--;
    ptr--;
    if (i >= 0) goto top;
}

/**
 * @brief Clear D_801E8C20 array (0x6E entries of 2 bytes each) to zero.
 */
void func_801E5828(s32 a0) {
    s32 i;
    u8 *ptr;

    i = 0;
    ptr = D_801E8C20;

    for (; i < 0x6E; i++) {
        ptr[0] = 0;
        ptr[1] = 0;
        ptr += 2;
    }
}

/** @brief Look up string @p a0 in menu text category 2. */
u8 *func_801E5854(s32 a0) {
    return func_801F08D4(1, 2, a0, 0);
}

s32 func_801E5880(s32 abilityId) {
    AbilityListEntry list[22];
    AbilityListEntry *entry;
    s32 best = 0;
    s32 count;
    s32 gf;

    for (gf = 0; gf < GF_COUNT; gf++) {
        if (g_gameState.gfs[gf].exists & GF_EXISTS) {
            count = func_800369CC(gf, list, 0);
            for (entry = list; count > 0; count--, entry++) {
                if (entry->slotIndex == abilityId && best < g_battleChars.levelEntries[gf].level) {
                    best = g_battleChars.levelEntries[gf].level;
                }
            }
        }
    }
    return best;
}

/**
 * @brief Return GF/summon data address if enabled, else return 0.
 * @param a0 Enable flag (non-zero to load D_801E8D80)
 * @return Address of D_801E8D80 after calling copyString, or 0
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E595C);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E59A0);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5A1C);

/**
 * @brief Return pointer to extended menu data area.
 *
 * @return Address of D_801E9600.
 */
s32 func_801E5A88(void) {
    return (s32)D_801E9600;
}

/**
 * @brief Copy extension string data from table to output buffer.
 *
 * Gets the base address from func_801E5A88, adds the offset from *a1,
 * then copies bytes until a sentinel value of 2 is found.
 * Terminates the output by calling copyString.
 *
 * @param a0 Unused
 * @param a1 Pointer to u16 offset into the string table
 * @param a2 Output buffer pointer
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5A94);

/**
 * @brief Filter string data from extension table, removing sentinel bytes.
 *
 * Calls func_801E5A88 to get the base address, adds the u16 offset from *a1,
 * skips past leading sentinel bytes (value 2), then copies non-sentinel,
 * non-zero bytes into D_801E8D00. Returns pointer to D_801E8D00.
 *
 * @param a0 Unused
 * @param a1 Pointer to u16 offset into string table
 * @return Pointer to filtered string in D_801E8D00
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5AF8);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5B88);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5C08);

/**
 * @brief Render extension entry at Y position computed from row modulo 11.
 * @param a0 Render context pointer.
 * @param a1 Row index (modulo 11, multiplied by 13, offset by 0x41 for Y).
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5CF8);

/**
 * @brief Render GF/summon entry at computed Y position with width 0x26.
 * @param a0 X position parameter
 * @param a1 Row index (multiplied by 13 and offset by 0x42 for Y position)
 */
void func_801E5D60(s32 a0, s32 a1) {
    func_801F0A34(a0, 0, 0x26, a1 * 13 + 0x42);
}

/**
 * @brief Render GF/summon entry at computed Y position with width 0xC8.
 * @param a0 X position parameter
 * @param a1 Row index (multiplied by 13 and offset by 0x42 for Y position)
 */
void func_801E5D98(s32 a0, s32 a1) {
    func_801F0A34(a0, 0, 0xC8, a1 * 13 + 0x42);
}

/**
 * @brief Render extension entry at Y position computed from row modulo 4.
 * @param a0 X position parameter
 * @param a1 Row index (modulo 4, multiplied by 13, offset by 0x43 for Y)
 */
void func_801E5DD0(s32 a0, s32 a1) {
    func_801F0A34(a0, 0, 0xD4, (a1 % 4) * 13 + 0x43);
}

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5E20);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E5E88);

/**
 * @brief Dispatches render call based on type byte at offset 0x45
 *
 * Reads a type indicator from the data structure. If type is 0, calls
 * func_801E5D98; if type is 2, calls func_801E5DD0. Both use the byte
 * at offset 0x4A as the row parameter.
 *
 * @param a0 Pointer to data structure
 */
void func_801E5EF0(u8 *a0) {
    switch (a0[0x45]) {
    case 0:
        func_801E5D98(0, a0[0x4A]);
        break;
    case 2:
        func_801E5DD0(0, a0[0x4A]);
        break;
    }
}

/**
 * @brief Search a 152-byte entry for a matching id, return its value.
 *
 * Computes the entry address as g_gameState.chars[a0].magic, then searches
 * up to 32 byte-pairs for a match with a1. Returns the value byte
 * following the matched id, or 0 if not found.
 *
 * @param a0 Entry index (multiplied by 152 for offset)
 * @param a1 Target id to find
 * @return Value byte after matched id, or 0 if not found
 */
s32 func_801E5F48(s32 a0, s32 a1) {
    u8 *slot = &g_gameState.chars[a0].magic[0].magicId;
    s32 i;

    for (i = 0; i < 32; i++, slot++) {
        s32 id = *slot++;
        
        if (a1 == id) {
            s32 quantity = *slot; 
            if (quantity != 0) {
                return quantity;
            }
        }
    }
    
    return 0;
}

/**
 * @brief Search byte-pair table for matching id, return its value.
 *
 * Iterates through up to 0xC6 byte-pairs. Each pair is (id, value).
 * If a pair's id matches a0, returns the value byte. Returns 0 if
 * no match is found.
 *
 * @param a0 Target id to find
 * @param a1 Pointer to byte-pair table
 * @return Value byte after matched id, or 0 if not found
 */
s32 func_801E5FA8(s32 a0, u8 *a1) {
    s32 i = 0;
top:
    {
        s32 id = a1[0];
        a1++;
        if (a0 != id) goto skip;
        {
            s32 val = a1[0];
            if (val != 0) {
                return val;
            }
        }
    }
skip:
    i++;
    a1++;
    if (i < 0xC6) goto top;
    return 0;
}

/**
 * @brief Build a filtered list of valid extension entries.
 *
 * Iterates through entries 0 to 0x6D, calling func_80023B14 for each.
 * If the result is positive, stores the 1-based entry index and the
 * result value as consecutive bytes into D_801E8C20. Returns the count
 * of valid entries found.
 *
 * @return Number of valid entries found.
 */
s32 func_801E5FE8(void) {
    u8 *ptr = D_801E8C20;
    s32 count = 0;
    s32 i = count;

    do {
        s32 result = func_80023B14(i);
        if (result > 0) {
            *ptr = i + 1;
            ptr++;
            *ptr = result;
            ptr++;
            count++;
        }
        i++;
    } while (i < 0x6E);

    return count;
}

/**
 * @brief Compute page count for extension list and store to context.
 *
 * Calls func_801E5828 to set up the extension data, then func_801E5FE8
 * to get the total item count. Computes ceiling division by 11 for page
 * count and stores to offset 0x52. Clamps minimum to 1.
 *
 * @param a0 Extension menu context pointer.
 */
void func_801E6060(u8 *a0) {
    s32 val;
    s32 pages;
    func_801E5828(a0);
    val = func_801E5FE8();
    pages = (val + 10) / 11;
    a0[0x52] = pages;
    if ((u8)pages == 0) {
        a0[0x52] = 1;
    }
}

/**
 * @brief Wrapper that calls func_80023B14.
 */
s32 func_801E60C4(s32 id) {
    return func_80023B14(id);
}

/** @brief Call addItemToInventory then func_800370AC with same argument. */
void func_801E60E4(s32 a0) {
    addItemToInventory(a0);
    func_800370AC(a0);
}

/**
 * @brief Decrease compatibility value for a matching entry in table.
 *
 * Searches a byte-pair table (id, value) for an entry matching a1.
 * Subtracts a2 from the value, clamping to 0. If value reaches 0,
 * clears the id byte as well. Stops after the first match.
 *
 * @param a0 Pointer to byte-pair table (id byte followed by value byte)
 * @param a1 Target id to match
 * @param a2 Amount to subtract from value
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E6114);

/**
 * @brief Advance through extension entries up to a1 times.
 *
 * Calls decrementItem with a0 in a loop up to a1 iterations.
 * Stops early if decrementItem returns a negative value.
 *
 * @param a0 Extension data pointer
 * @param a1 Maximum number of entries to advance
 */
void func_801E6168(s32 a0, s32 a1) {
    while (a1 > 0) {
        if (decrementItem(a0) < 0) {
            break;
        }
        a1--;
    }
}

s32 GetMaxConvertCount(ExtMenuCtx *ctx) {
    s32 dstCount;
    ExtEntry *entry = &ctx->entries[ctx->entryIdx];
    s32 srcCount;
    s32 srcId = entry->srcId;
    s32 dstId = entry->dstId;
    s32 yield = entry->yield;
    s32 cost = entry->cost;
    s32 charIdx = ctx->charIdx;

    switch (ctx->mode) {
    case 0:
        srcCount = func_801E5FA8(srcId, ctx->unk30);
        dstCount = func_801E5F48(charIdx, dstId);
        break;
    case 1:
        srcCount = func_801E5FA8(srcId, ctx->unk30);
        dstCount = func_801E5FA8(dstId, ctx->unk30);
        break;
    case 2:
        srcCount = func_801E5F48(charIdx, srcId);
        dstCount = func_801E5F48(charIdx, dstId);
        break;
    case 3:
        srcCount = func_801E5FA8(srcId, ctx->unk30);
        dstCount = func_801E5FA8(dstId, ctx->unk30);
        break;
    case 4:
        srcCount = func_801E60C4(srcId);
        dstCount = func_801E5FA8(dstId, ctx->unk34);
        break;
    }
    ctx->srcCount = srcCount;
    ctx->dstCount = dstCount;
    if (dstCount == 100) {
        return 0;
    }
    dstCount = 100 - dstCount;
    if (yield == 0) {
        yield = 1;
    }
    srcCount /= cost;
    dstCount = (dstCount + yield - 1) / yield;
    return dstCount > srcCount ? srcCount : dstCount;
}

s32 func_801E6338(s32 spellId, s32 charMask) {
    CharacterData *ch;
    s32 fullMask = 0;
    s32 bit;
    s32 used;
    s32 c;
    s32 i;

    for (c = 0; c < 8; c++) {
        bit = 1 << c;
        if (charMask & bit) {
            ch = &g_gameState.chars[c];
            used = 0;
            D_801E8C10[c] = 0;
            for (i = 0; i < MAGIC_SLOT_COUNT; i++) {
                s32 id = ch->magic[i].magicId;
                s32 qty = ch->magic[i].quantity;

                if (id != 0 && qty != 0) {
                    used |= 1 << i;
                }
                if (spellId == id && qty != 0) {
                    D_801E8C10[c] = ch->magic[i].quantity;
                    used = 0;
                }
            }
            if (used == -1) {
                D_801E8C10[c] = 0xFF;
                fullMask |= 1 << c;
            }
        }
    }
    return fullMask != charMask;
}

/**
 * @brief Evaluate an extension entry's compatibility level.
 *
 * If the entry index is 0, returns 2 immediately. Otherwise, takes the absolute
 * value of the index, looks up a byte from the table at a1, calls func_801E5FA8,
 * and returns: 1 if result >= 100, 2 if entry index was negative, 0 otherwise.
 *
 * @param a0 Entry index (0 = no entry, negative = reverse lookup)
 * @param a1 Table base pointer
 * @param a2 Parameter passed to func_801E5FA8
 * @return 2 if no entry or negative index with low compat, 1 if high compat, 0 otherwise
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E63F4);

/**
 * @brief Look up entry by absolute index, store type byte, and dispatch.
 *
 * Takes an index (negated if negative), decrements by 1, looks up an 8-byte
 * entry from the table at a0+0x24, stores the type byte (offset 7) to a0+0x4B,
 * then calls func_801E6338 with that type and the a2 parameter.
 *
 * @param a0 Menu context pointer
 * @param a1 Entry index (absolute value used, decremented by 1)
 * @param a2 Parameter passed through to func_801E6338
 * @return 3 if func_801E6338 returns 0, otherwise 0
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E6458);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E64B4);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E6748);

/**
 * @brief Return direction indicator based on sign of input.
 *
 * @param a0 Input value
 * @return 0 if a0 == 0, 7 if a0 > 0, 1 if a0 < 0
 */
s32 func_801E76A8(s32 a0) {
    s32 v0;
    if (a0 != 0) goto L1;
    v0 = 0;
L1:
    if (a0 <= 0) goto L2;
    v0 = 7;
L2:
    if (a0 >= 0) goto L3;
    v0 = 1;
L3:
    return v0;
}

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E76D4);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E7858);

s32 func_801E79C8(ExtMenuCtx *ext, s32 ctx, s32 dl, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 arrowX;

    if (ext->mode != 4) {
        cfg->iconType = 0x4C;
        arrowX = 28;
    } else {
        cfg->iconType = 0x59;
        arrowX = 40;
    }
    cfg->w = 166;
    cfg->h = 160;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->columnCount = 11;
    cfg->pageStart = ext->pageStart;
    cfg->pageEnd = ext->pageEnd;
    cfg->scrollOffset = ext->scroll;
    cfg->dataPtr = (s32)ext;
    if (ext->unk52 >= 2) {
        dl = func_801F5EFC(ctx, dl, x + arrowX, y, g_menuTint[MENU_TINT_NORMAL], ext->pageStart);
        dl = func_801F5F60(ctx, dl, g_menuTint[MENU_TINT_NORMAL], 3);
    }
    if (ext->mode == 4) {
        dl = func_801EFBB4(ctx, dl, func_801E7858);
    } else {
        dl = func_801EFBB4(ctx, dl, func_801E76D4);
    }
    return dl;
}

s32 func_801E7B00(s32 ctx, s32 dl, s32 page, s32 row, s32 xOffset) {
    ExtMenuCtx *ext;
    s32 charId;
    s32 magicId;
    s32 quantity;
    s32 x;
    s32 y;
    s32 textY;
    s32 color;

    magicId = page * 4 + row;
    charId = g_menuDisplayCfg.itemId;
    ext = (ExtMenuCtx *)g_menuDisplayCfg.dataPtr;
    quantity = g_gameState.chars[charId].magic[magicId].quantity;
    magicId = g_gameState.chars[charId].magic[magicId].magicId;
    x = g_menuDisplayCfg.x + xOffset;
    y = g_menuDisplayCfg.y + row * 13;

    if (quantity != 0 && magicId != 0) {
        if (func_801F1CE8(charId, magicId)) {
            textY = y + 7;
            dl = drawIcon(ctx, dl, ICON_JUNCTION_MARK, x + 97, textY, g_menuTint[MENU_TINT_NORMAL]);
        }
        color = func_801E76A8(func_801E5B88(ext->mode, ext->entries, ext->entryCount, magicId, quantity, ext->unk47));
        /* Reusing page for text X coordinates is required for the match. */
        page = x + 12;
        textY = y + 7;
        dl = func_801F0FEC(ctx, dl, page, textY, getMagicNamePtr(magicId), color);
        page = x + 142;
        dl = drawNumberMenuTint(ctx, dl, (textY << 16) | (page & 0xFFFF), quantity, color);
    }
    return dl;
}

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E7C9C);

/**
 * @brief Render text entry from data table at computed position.
 *
 * Looks up a pointer from the g_menuDisplayCfg table at index a2, decodes it
 * with decodeMessage, then renders at position computed from g_menuDisplayCfg
 * base coordinates plus offsets.
 *
 * @param a0 Render context
 * @param a1 Return value if no entry found
 * @param a2 Table index for entry lookup
 * @param a3 Unused
 * @param arg5 X offset added to base position
 * @return Result of func_801F0FEC if entry exists, otherwise a1
 */
INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E7D88);

/**
 * @brief Configure display parameters and invoke callback for extension rendering.
 *
 * Sets up g_menuDisplayCfg display configuration with the given position and size,
 * stores the pointer at a0+0x28 as the data source, reads scroll offset from
 * a0+0x3A, then calls func_801EFBB4 with func_801E7D88 as the render callback.
 *
 * @param a0 Pointer to source data structure
 * @param a1 First callback parameter (passed as a0 to func_801EFBB4)
 * @param a2 Second callback parameter (passed as a1 to func_801EFBB4)
 * @param a3 X position for the display configuration
 * @param arg5 Y position for the display configuration
 */
void func_801E7E38(u8 *a0, s32 a1, s32 a2, s32 a3, s32 arg5) {
    s32 cfg = (s32)&g_menuDisplayCfg;
    *(u8 *)(cfg + 0x10) = 0x55;
    *(u8 *)(cfg + 0x11) = 0;
    *(s16 *)&g_menuDisplayCfg = a3;
    *(s16 *)(cfg + 0x04) = 0x144;
    *(s16 *)(cfg + 0x06) = 0x1A;
    *(u8 *)(cfg + 0x13) = 1;
    *(u8 *)(cfg + 0x16) = 0;
    *(u8 *)(cfg + 0x17) = 1;
    *(s16 *)(cfg + 0x02) = arg5;
    *(s16 *)(cfg + 0x14) = *(u16 *)(a0 + 0x3A);
    *(s32 *)(cfg + 0x20) = (s32)(a0 + 0x28);
    {
        func_801EFBB4(a1, a2, func_801E7D88);
    }
}

extern u8 *getCharName(s32 charId);

/**
 * @brief Render a character/magic equipment row + selection highlight.
 *
 * If @p ctx->state is < 0xFF, draws the character name, the equipped
 * magic name, and a colored count indicator pulled from D_801E8C10
 * (treated as 0 when 0xFF). Always finishes by configuring the panel
 * box (size 0xA8 × 0x28 at @p x,@p y) and dispatching the draw via
 * func_801EF9AC with g_menuTint[MENU_TINT_NORMAL].
 *
 * @param ctx        Extension menu context (charIdx/magicId at +0x48/0x4B).
 * @param renderCtx  Render context handle.
 * @param cursorY    Current OT cursor position.
 * @param x          Panel X position.
 * @param y          Panel Y position (5th arg, on stack).
 * @return           Final OT cursor position from func_801EF9AC.
 */
s32 func_801E7EB4(ExtMenuCtx *ctx, s32 renderCtx, s32 cursorY, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;

    if (ctx->state < 0xFF) {
        CharacterData *charEntry;
        s32 byteVal;
        s32 textY;
        s32 textX;
        s32 textAttr;

        textAttr = func_801F3FB4(func_801F57A4(ctx->charIdx) & 0xFFFF);
        textX = x + 8;
        textY = y + 8;
        charEntry = &g_gameState.chars[ctx->charIdx];
        cursorY = func_801F0FEC(renderCtx, cursorY, textX, textY,
                                getCharName(charEntry->characterId), textAttr);

        textAttr = 7;
        textX = x + 0x22;
        textY = y + 0x18;
        cursorY = func_801F0FEC(renderCtx, cursorY, textX, textY,
                                getMagicNamePtr(ctx->magicId), textAttr);

        byteVal = D_801E8C10[ctx->charIdx];
        textX = x + 0x88;
        if (byteVal == 0xFF) {
            byteVal = 0;
        }
        cursorY = drawNumberMenuTint(renderCtx, cursorY,
                                         ((textY << 15) << 1) | (textX & 0xFFFF),
                                         byteVal, textAttr);
    }

    cfg->iconType = 0;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 0xA8;
    cfg->h = 0x28;
    return func_801EF9AC(renderCtx, cursorY, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E8058);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E81C8);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E82B4);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E8598);

INCLUDE_ASM("asm/ovl/menuext/nonmatchings/menuext", func_801E8840);

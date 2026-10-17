#include "common.h"
#include "menupty.h"
#include "gamestate.h"

#include "menu.h"
#include "menumain.h"
#include "card.h"
#include "overlay.h"
#include "render.h"

#define MENUPTY_TEXT_SECTION 4
#define PARTY_CURSOR_DRAW_FLAG 0x01
#define PARTY_CURSOR_SHIFT 0x02

typedef struct {
    /* 0x00 */ u8 pad00[32];
    /* 0x20 */ u8 *helpText;
    /* 0x24 */ u16 memberMask;
    /* 0x26 */ s16 brightness;
    /* 0x28 */ u8 pad28[2];
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 partyCursor;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 party[3];
    /* 0x3B */ u8 memberOrder[8];
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
} PartyMenuCtx;

typedef struct {
    /* 0x00 */ u8 pad00[32];
    /* 0x20 */ u8 *helpText;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 brightness;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u8 pad2A[14];
    /* 0x38 */ u16 unk38;
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u8 pad40[4];
    /* 0x44 */ u8 party[3];
} PartyScreenCtx;

extern u8 D_801E9702;
static const u8 D_801E9538[8];
s32 func_801E6F54(s32, s32, s32, s32, CharMenuInfo *);
s32 func_801E708C(s32, s32, s32, s32, s32);
s32 func_801E6B6C(PartyScreenCtx *, s32, s32, s32, s32, s32);
s32 func_801E59AC(PartyScreenCtx *);
s32 func_801E6948(PartyScreenCtx *, s32, s32, s32, s32);
s32 func_801E72BC(PartyScreenCtx *, s32, s32);
s32 func_801E6DDC(PartyScreenCtx *, s32, s32, s32, s32);
s32 func_801E8A10(PartyMenuCtx *, s32, s32, s32, s32, s32);
s32 func_801E9074(PartyMenuCtx *, s32, s32);
s32 func_801E8C8C(PartyMenuCtx *, s32, s32, s32, s32);
s32 func_801E8E00(PartyMenuCtx *, s32, s32, s32, s32);
s32 func_801E7A1C(PartyMenuCtx *);
void func_801E7B9C(PartyMenuCtx *);
s32 func_801E92B8(void);

static const s16 D_801E9528[4];
static const s16 D_801E9530[4];
extern u8 D_801E9540;

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E5800);

/**
 * @brief Render party member stat label at computed position.
 *
 * Decompresses coordinate table from D_801E9528, looks up a position
 * by the byte at a0+0x40, adds 0x32, and renders at that x-coordinate
 * with y=0xD.
 *
 * @param a0 Party context pointer.
 * @param a1 Render context pointer.
 */
void func_801E58EC(u8 *a0, s32 a1) {
    s16 buf[36];
    func_801F5984(D_801E9528, buf, 4);
    func_801F0A34(a1, 0, buf[a0[0x40]] + 0x32, 0xD);
}

/** @brief Draw inner panel with section id 0x4 and clear flag. */
s32 func_801E5954(s32 a0) {
    return func_801F08D4(1, 4, a0, 0);
}

/** @brief Draw inner panel with section id 0x4 and set flag. */
u8 *func_801E5980(s32 a0) {
    return func_801F08D4(1, 4, a0, 1);
}

/**
 * @brief Look up a party member attribute byte from a conditional table.
 *
 * If byte at a0+0x41 is non-zero, uses the index at a0+0x43 to read
 * from offset 0x47. Otherwise uses the index at a0+0x42 to read
 * from offset 0x44.
 *
 * @param a0 Party context pointer.
 * @return Attribute byte value.
 */
INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E59AC);

/**
 * @brief Compute party display offset based on mode flag.
 *
 * Returns a0 + a2 + 0x44 if a1 is zero, or a0 + a2 + 0x47 otherwise.
 *
 * @param a0 Base offset.
 * @param a1 Mode flag (0 = normal, non-zero = alternate).
 * @param a2 Additional offset.
 * @return Computed display position.
 */
s32 func_801E59EC(s32 a0, s32 a1, s32 a2) {
    s32 v0;
    if (a1 != 0) {
        v0 = a0 + 0x47;
    } else {
        v0 = a0 + 0x44;
    }
    return v0 + a2;
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E5A08);

void SwapJunctions(s32 charA, s32 charB) {
    CharacterData tmp;
    CharacterData *a = &g_gameState.chars[charA];
    CharacterData *b = &g_gameState.chars[charB];
    u16 junctedGfs;
    s32 i;

    for (i = 0; i < MAGIC_SLOT_COUNT; i++) {
        tmp.magic[i].magicId = b->magic[i].magicId;
        tmp.magic[i].quantity = b->magic[i].quantity;
        b->magic[i].magicId = a->magic[i].magicId;
        b->magic[i].quantity = a->magic[i].quantity;
        a->magic[i].magicId = tmp.magic[i].magicId;
        a->magic[i].quantity = tmp.magic[i].quantity;
    }
    for (i = 0; i < 4; i++) {
        tmp.commands[i] = b->commands[i];
        b->commands[i] = a->commands[i];
        a->commands[i] = tmp.commands[i];
    }
    for (i = 0; i < 4; i++) {
        tmp.abilities[i] = b->abilities[i];
        b->abilities[i] = a->abilities[i];
        a->abilities[i] = tmp.abilities[i];
    }
    junctedGfs = b->junctedGfs;
    b->junctedGfs = a->junctedGfs;
    a->junctedGfs = junctedGfs;
    for (i = 0; i < 20; i++) {
        tmp.junctions[i] = b->junctions[i];
        b->junctions[i] = a->junctions[i];
        a->junctions[i] = tmp.junctions[i];
    }
}

s32 func_801E5CE8(s32 charA, s32 charB) {
    BattleCharData stats;
    u16 hpA = g_gameState.chars[charA].currentHp;
    u16 hpB = g_gameState.chars[charB].currentHp;
    s32 newHpA;
    s32 newHpB;

    SwapJunctions(charA, charB);
    func_801F537C(charA, &stats);
    newHpA = stats.currentHp;
    func_801F537C(charB, &stats);
    newHpB = stats.currentHp;
    SwapJunctions(charA, charB);
    g_gameState.chars[charA].currentHp = hpA;
    g_gameState.chars[charB].currentHp = hpB;
    func_801F5440();
    if (newHpB < hpB) {
        return charB;
    }
    if (newHpA < hpA) {
        return charA;
    }
    return PARTY_SLOT_EMPTY;
}

void func_801E5DE4(s32 charA, s32 charB) {
    SwapJunctions(charA, charB);
    func_801F5440();
}

void func_801E5E0C(PartyScreenCtx *ctx) {
    u8 joined[3];
    s32 newMask = 0;
    s32 count;
    s32 member;
    s32 bit;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        member = ctx->party[i];
        g_gameState.mainData.party.partyMembers[i] = member;
        if (member != PARTY_SLOT_EMPTY) {
            newMask |= 1 << member;
        }
    }
    for (i = 0; i < 3; i++) {
        member = g_gameState.battleParty[i];
        if (member != PARTY_SLOT_EMPTY && !((ctx->unk28 >> member) & 1)) {
            g_gameState.battleParty[i] = PARTY_SLOT_EMPTY;
        }
    }
    newMask &= ~ctx->unk28;
    count = 0;
    for (i = 0; i < 3; i++) {
        member = ctx->party[i];
        if (member != PARTY_SLOT_EMPTY) {
            bit = 1 << member;
            if (newMask & bit) {
                joined[count++] = member;
            }
        }
    }
    for (i = 0, j = 0; i < 3; i++) {
        if (g_gameState.battleParty[i] == PARTY_SLOT_EMPTY) {
            if (j == count) {
                break;
            }
            g_gameState.battleParty[i] = joined[j++];
        }
    }
    if (D_801E9540 == 0 && ctx->unk38 == 3) {
        SetModeBit0();
    }
    func_801F22A8();
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E5F94);

s32 func_801E6898(PartyScreenCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    s32 enabled = ctx->unk38;

    x += 24;
    y += 10;
    pkt = func_801F5A38(ot, pkt, x + 26, y + 6, MENUPTY_TEXT_SECTION, D_801E9528, enabled);
    g_menuDisplayCfg.iconType = 0;
    g_menuDisplayCfg.iconSubType = 0;
    g_menuDisplayCfg.x = x;
    g_menuDisplayCfg.y = y;
    g_menuDisplayCfg.w = 244;
    g_menuDisplayCfg.h = 18;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E6948);

s32 func_801E69F4(PartyScreenCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y, s32 slot) {
    s32 charIdx = ctx->party[slot];

    if (charIdx == PARTY_SLOT_EMPTY) {
        return pkt;
    }
    return func_801F64A4(ot, pkt, x - 32, y + (slot * 50 - 49), &g_gameState.chars[charIdx], &g_charMenuInfo[charIdx], 0);
}

s32 func_801E6AA0(PartyScreenCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 i;

    x += 24;
    y += 56;
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        pkt = func_801E69F4(ctx, ot, pkt, x, y, i);
    }
    cfg->iconType = 0;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 168;
    cfg->h = 160;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E6B6C);

s32 func_801E6C68(PartyScreenCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 i;

    x += 192;
    y += 56;
    for (i = 0; i < CHARACTER_COUNT; i++) {
        pkt = func_801E6B6C(ctx, ot, pkt, x, y, i);
    }
    cfg->iconType = 0;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 170;
    cfg->h = 120;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

/**
 * @brief Render a text label with color and position using drawNumberMenuTint.
 *
 * Calls func_801F6AFC(0x12) for font, func_801F0FEC to render text,
 * then drawNumberMenuTint to combine color/position.
 *
 * @param a0 Color/attribute value.
 * @param a1 Render context pointer.
 * @param a2 X position base.
 * @param a3 Y position base.
 * @param stackArg0 Width parameter.
 * @param stackArg1 Height parameter.
 */
INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E6D34);

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E6DDC);

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E6F54);

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E708C);

s32 func_801E71A0(s32 ot, s32 pkt, s32 x, s32 y, s32 charIdx) {
    CharacterData *chr = &g_gameState.chars[charIdx];
    CharMenuInfo *info = &g_charMenuInfo[charIdx];

    pkt = func_801F64A4(ot, pkt, x, y, chr, info, 1);
    pkt = func_801F6234(ot, pkt, x + 208, y + 57, info->statusFlags);
    pkt = func_801F605C(ot, pkt, x + 270, y + 56, info);
    pkt = func_801F66B0(ot, pkt, x, y, D_801E9702);
    pkt = func_801E6F54(ot, pkt, x, y, info);
    return func_801E708C(ot, pkt, x, y, chr->junctedGfs);
}

s32 func_801E72BC(PartyScreenCtx *a0, s32 a1, s32 a2) {
    s32 result = func_801E5954(7);

    return func_801F4274(a1, a2, result, 0xC0, 0x6B, 0x1000);
}

s32 func_801E7318(PartyScreenCtx *ctx, s32 ot, s32 pkt) {
    s32 member;
    s32 x = 0;
    s32 y = 0;

    func_801F1AFC();
    setMenuBrightness(ctx->brightness);
    pkt = func_801E6898(ctx, ot, pkt, x, y);
    pkt = func_801E6948(ctx, ot, pkt, x, y);
    if (ctx->unk3E != 0) {
        pkt = func_801E72BC(ctx, ot, pkt);
    }
    if (ctx->unk3F != PARTY_SLOT_EMPTY) {
        pkt = func_801F6FE4(ot, pkt, 1, 0x1000);
    }
    if (ctx->unk3A != 0) {
        setMenuBrightness(ctx->brightness * ctx->unk3A / 0x1000);
        pkt = func_801E6AA0(ctx, ot, pkt, x, y);
        pkt = func_801E6C68(ctx, ot, pkt, x, y);
        pkt = func_801E6DDC(ctx, ot, pkt, x, y);
    }
    if (ctx->unk3C != 0) {
        member = func_801E59AC(ctx);
        if (member != PARTY_SLOT_EMPTY) {
            setMenuBrightness(ctx->unk3C * ctx->brightness / 0x1000);
            pkt = func_801E71A0(ot, pkt, x, y, member);
        }
    }
    func_801F1B10();
    return pkt;
}

/**
 * @brief Build bitmask of characters with specific status flag.
 *
 * For each of 8 character slots, checks if the input bitmask has the
 * character's bit set AND the character's status halfword at g_gameState.chars
 * (stride 152) has bit 2 set. Returns a combined bitmask.
 *
 * @param a0 Input character bitmask.
 * @return Filtered bitmask of characters matching the criteria.
 */
s32 func_801E74DC(s32 arg0) {
    s32 i;
    s32 bit;
    s32 result;
    CharacterData* charData;
    
    charData = g_gameState.chars;
    result = 0;
    
    for (i = 0; i < 8; i++) {
        bit = 1 << i;
        if ((arg0 & bit) && (charData->exists & 4)) {
            result |= bit;
        }
        
        charData++;
    } 
    
    return result;
}

/**
 * @brief Build bitmask of characters with alternate status flag.
 *
 * Same as func_801E74DC but checks bit 1 of the status halfword
 * instead of bit 2.
 *
 * @param a0 Input character bitmask.
 * @return Filtered bitmask of characters matching the criteria.
 */
s32 func_801E7530(s32 arg0) {
    s32 i;
    s32 bit;
    s32 result;
    CharacterData* charData;
    
    charData = g_gameState.chars;
    result = 0;
    
    for (i = 0; i < 8; i++) {
        bit = 1 << i;
        if ((arg0 & bit) && (charData->exists & 2)) {
            result |= bit;
        }
        
        charData++;
    } 
    
    return result;
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E7584);

/**
 * @brief Initialize party menu and conditionally reset cursor.
 *
 * Clears D_801E9540 flag, calls func_801EFFB8. If result is 1,
 * calls resetCardSlots(0) to reset cursor position. Then calls
 * func_801E7584 with the party context.
 *
 * @param a0 Party context pointer.
 */
void func_801E77AC(u8 *a0) {
    s32 result;
    D_801E9540 = 0;
    result = func_801EFFB8();
    if (result == 1) {
        resetCardSlots(0);
    }
    func_801E7584(a0);
}

/**
 * @brief Initialize party menu: set mode 0x35, configure display, enable flag.
 *
 * Sets up the party menu display by calling initialization functions,
 * configuring display areas, setting the active flag D_801E9540 to 1,
 * then entering the main party menu handler.
 *
 * @param a0 Menu context pointer
 */
void func_801E77F8(s32 a0) {

    func_801F1DBC(0x35);
    func_801E2ABC(a0);
    func_801F1210(0x801D1000, 0x801CD000);
    D_801E9540 = 1;
    func_801E7584(a0);
}

/**
 * @brief Render party stat with computed y-position from character lookup.
 *
 * @param a0 Render context pointer.
 * @param a1 Character slot index.
 */
void func_801E7854(s32 a0, s32 a1) {
    s32 ctx = a0;
    s32 slot = a1;
    s32 v0 = func_801F0028();
    v0 = getBitRank(v0, slot);
    func_801F0A34(ctx, 0, 0x36, v0 * 50 + 0x4C);
}

void func_801E78BC(s32 flags, s32 inParty, s32 slot, s32 index) {
    s32 x;
    s32 y;

    if (inParty == 0) {
        x = (index % 4) * 38 + 208;
        y = (index / 4) * 55 + 78;
    } else {
        x = 142;
        slot = getBitRank(func_801F0028(), slot);
        y = slot * 50 + 76;
    }
    if (flags & PARTY_CURSOR_SHIFT) {
        x -= 4;
        y -= 4;
    }
    func_801F0A34(flags & PARTY_CURSOR_DRAW_FLAG, 0, x, y);
}

/**
 * @brief Render party member stat label at computed position.
 *
 * @param a0 Render context pointer.
 * @param a1 Party context pointer.
 */
void func_801E7990(s32 a0, u8 *a1) {
    s32 ctx = a0;
    u8 *party = a1;
    s16 buf[36];
    func_801F5984(D_801E9530, buf, 4);
    func_801F0A34(ctx, 0, buf[party[0x2E]] + 0x32, 0xD);
}

s32 func_801E79F8(PartyMenuCtx *ctx, s32 a1, s32 a2, s32 a3) {
    if (a1 == 0) {
        return ctx->memberOrder[a3];
    }
    return ctx->party[a2];
}

s32 func_801E7A1C(PartyMenuCtx *ctx) {
    s32 member;

    if (ctx->unk43 == 3) {
        member = func_801E79F8(ctx, ctx->unk33, ctx->unk37, ctx->unk36);
    } else {
        member = func_801E79F8(ctx, ctx->unk32, ctx->unk35, ctx->unk34);
    }
    return member;
}

void CommitPartySelection(PartyMenuCtx *ctx) {
    CharacterData *chars = g_gameState.chars;
    u8 *battleParty;
    s32 i;
    s32 count;
    s32 swap;

    g_gameState.mainData.partyLockFlag |= PARTY_LOCK_LOCKED;
    chars[0].characterId = 0;
    battleParty = g_gameState.battleParty;
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        *battleParty++ = PARTY_SLOT_EMPTY;
        g_gameState.mainData.party.partyMembers[i] = PARTY_SLOT_EMPTY;
    }
    battleParty = g_gameState.battleParty;
    count = 0;
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if ((func_801F0028() >> i) & 1) {
            s32 member = ctx->party[i];

            if (member != PARTY_SLOT_EMPTY) {
                /* Alternate party character IDs start at 8. */
                chars[member].characterId = i + 8;
                g_gameState.mainData.party.partyMembers[count++] = member;
                *battleParty++ = i + 8;
            }
        }
    }
    swap = g_gameState.mainData.party.partyMembers[1];
    g_gameState.mainData.party.partyMembers[1] = g_gameState.mainData.party.partyMembers[0];
    g_gameState.mainData.party.partyMembers[0] = swap;
    func_80036C74();
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E7B9C);

/* Party slot coordinate tables */
static const s16 D_801E9528[4] = {2, 3, -1, 0};
static const s16 D_801E9530[4] = {1, 3, -1, 0};

s32 func_801E88B4(PartyMenuCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    s32 enabled = ctx->unk44;

    x += 24;
    y += 10;
    pkt = func_801F5A38(ot, pkt, x + 26, y + 6, MENUPTY_TEXT_SECTION, D_801E9530, enabled);
    g_menuDisplayCfg.iconType = 0;
    g_menuDisplayCfg.iconSubType = 0;
    g_menuDisplayCfg.x = x;
    g_menuDisplayCfg.y = y;
    g_menuDisplayCfg.w = 244;
    g_menuDisplayCfg.h = 18;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

s32 func_801E8964(PartyMenuCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    pkt = func_801F0FEC(ot, pkt, x + 40, y + 38, ctx->helpText, 7);
    g_menuDisplayCfg.iconType = 0x55;
    g_menuDisplayCfg.iconSubType = 0;
    g_menuDisplayCfg.x = x + 30;
    g_menuDisplayCfg.y = y + 29;
    g_menuDisplayCfg.w = 324;
    g_menuDisplayCfg.h = 26;
    return func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E8A10);

s32 func_801E8AEC(PartyMenuCtx *ctx, s32 ot, s32 pkt, s32 x, s32 y) {
    MenuDisplayConfig *cfg = &g_menuDisplayCfg;
    s32 tx;
    s32 ty;
    s32 i;

    x += 24;
    tx = x;
    y += 56;
    ty = y;
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if ((func_801F0028() >> i) & 1) {
            pkt = func_801E8A10(ctx, ot, pkt, tx, ty, i);
            ty += 50;
        }
    }
    cfg->iconType = 0;
    cfg->iconSubType = 0;
    cfg->x = x;
    cfg->y = y;
    cfg->w = 168;
    cfg->h = 160;
    pkt = func_801EF9AC(ot, pkt, 0x1000, g_menuTint[MENU_TINT_NORMAL]);
    return pkt;
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E8BF4);

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E8C8C);

s32 func_801E8D58(s32 value, s32 ot, s32 pkt, s32 x, s32 y, s32 color) {
    pkt = func_801F0FEC(ot, pkt, x, y, func_801F6AFC(0x12), color);
    x += 51;
    return drawNumberMenuTint(ot, pkt, (y << 16) | (x & 0xFFFF), value, color);
}

INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E8E00);

s32 func_801E9074(PartyMenuCtx *ctx, s32 a1, s32 a2) {
    s32 result = func_801E5954(8);
    return func_801F4274(a1, a2, result, 0xC0, 0x6B, 0x1000);
}

s32 func_801E90D0(PartyMenuCtx *ctx, s32 ot, s32 pkt) {
    s32 member;
    s32 x = 0;
    s32 y = 0;

    func_801F1AFC();
    setMenuBrightness(ctx->brightness);
    if (ctx->unk30 != 0) {
        pkt = func_801E9074(ctx, ot, pkt);
    }
    if (ctx->unk2F != PARTY_SLOT_EMPTY) {
        pkt = func_801F6FE4(ot, pkt, 1, 0x1000);
    }
    pkt = func_801E88B4(ctx, ot, pkt, x, y);
    pkt = func_801E8964(ctx, ot, pkt, x, y);
    setMenuBrightness(ctx->brightness * ctx->unk2A / 0x1000);
    if (ctx->unk2A != 0) {
        pkt = func_801E8AEC(ctx, ot, pkt, x, y);
        pkt = func_801E8C8C(ctx, ot, pkt, x, y);
        pkt = func_801E8E00(ctx, ot, pkt, x, y);
    }
    if (ctx->unk2C != 0) {
        if (ctx->unk43 == 2) {
            member = ctx->party[ctx->partyCursor];
        } else {
            member = func_801E7A1C(ctx);
        }
        if (member != PARTY_SLOT_EMPTY) {
            setMenuBrightness(ctx->unk2C * ctx->brightness / 0x1000);
            pkt = func_801E71A0(ot, pkt, x, y, member);
        }
    }
    func_801F1B10();
    return pkt;
}

/**
 * @brief Build a bitmask of party-eligible characters.
 *
 * Iterates through all 8 character slots in g_gameState (stride 152).
 * For each character, checks bit 3 of the halfword at offset 0x524.
 * If set, the corresponding bit in the result mask is set.
 *
 * @return Bitmask where bit N is set if character N is party-eligible.
 */
INCLUDE_ASM("asm/ovl/menupty/nonmatchings/menupty", func_801E92B8);

static const u8 D_801E9538[8] = {10, 13, PARTY_SLOT_EMPTY};

void func_801E92FC(void) {
    PartyMenuCtx *ctx = func_801F179C(func_801E7B9C, func_801E90D0);
    u8 *order;
    s32 party;
    s32 i;

    func_801F0948(0);
    resetCardSlots(1);
    g_gameState.mainData.partyLockFlag &= ~PARTY_LOCK_LOCKED;
    if (ctx != NULL) {
        ctx->unk2E = 0;
        ctx->unk44 = 3;
        ctx->brightness = 0;
        ctx->helpText = func_801E5980(D_801E9530[ctx->unk2E]);
        ctx->unk30 = 0;
        g_gameState.chars[0].characterId = 0;
        ctx->memberMask = func_801E92B8();
        party = func_801F0028() & 6;
        ctx->unk2F = PARTY_SLOT_EMPTY;
        ctx->unk2A = 0x1000;
        ctx->unk2C = 0;
        ctx->partyCursor = findNthSetBit(party, 0);
        ctx->party[0] = 0;
        ctx->party[1] = PARTY_SLOT_EMPTY;
        ctx->party[2] = PARTY_SLOT_EMPTY;
        ctx->memberMask &= ~1;
        for (i = 0; i < 8; i++) {
            ctx->memberOrder[i] = PARTY_SLOT_EMPTY;
        }
        order = ctx->memberOrder;
        for (i = 0; i < 8; i++) {
            if ((ctx->memberMask >> i) & 1) {
                *order++ = i;
            }
        }
        func_801E7B9C(ctx);
    }
    if (func_801EFFB8() == 22) {
        func_801F5440();
        func_801F1D34(D_801E9538);
        func_801F1DB0(ctx->brightness);
    }
}

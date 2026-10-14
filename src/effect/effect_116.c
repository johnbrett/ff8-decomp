/**
 * @file effect_116.c
 * @brief Quezacotl Summon (Thunder Storm)
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/libgpu.h"

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 colour;
    /* 0x08 */ DVECTOR xy0;
    /* 0x0C */ DVECTOR xy1;
    /* 0x10 */ DVECTOR xy2;
    /* 0x14 */ DVECTOR xy3;
} ScreenTintQuad;

extern void *D_801B17FC;

static void DrawFullScreenTint(u32 *colour);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80190000);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80190020);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80190040);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80190060);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801900A0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801901C0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801901F8);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801902A4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019035C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019041C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801904B0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019054C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801905E8);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80190A80);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80190FC0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80191030);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80191318);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80191658);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801919E4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80191DC8);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801920EC);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192490);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192850);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192C98);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192EC4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192EE8);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192F64);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80192FE4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80193060);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801930F0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80193214);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801932A4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801933A8);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019389C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80193E08);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80193F88);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80193FF0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194058);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194264);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194884);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194900);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194930);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194990);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194A88);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194B64);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194C58);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194D10);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194D74);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194DB8);

static void DrawFullScreenTint(u32 *colour) {
    DR_TPAGE *mode;
    ScreenTintQuad *quad;

    mode = D_801B17FC;
    D_801B17FC = mode + 1;
    setlen(mode, 1);
    mode->code[0] = 0xE10002A0;
    addPrim(&D_800FA5E8->frontOT[3], mode);
    quad = D_801B17FC;
    D_801B17FC = quad + 1;
    quad->xy1.vx = quad->xy3.vx = 320;
    quad->xy2.vx = quad->xy0.vx = 0;
    quad->xy0.vy = quad->xy1.vy = 0;
    quad->xy2.vy = quad->xy3.vy = 216;
    quad->colour = *colour;
    setlen(quad, 5);
    setcode(quad, 0x2A);
    addPrim(&D_800FA5E8->frontOT[3], quad);
    mode = D_801B17FC;
    D_801B17FC = mode + 1;
    setlen(mode, 1);
    mode->code[0] = 0xE10002C0;
    addPrim(&D_800FA5E8->frontOT[3], mode);
}

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80194F7C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80195104);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801951BC);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80196344);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801964F4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80196744);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801969AC);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801969F0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80196A6C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80196C80);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80196ED4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019715C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80197248);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019727C);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801972C4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801974D8);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801976D4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80197788);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801977B4);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80197FD0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80198184);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80198398);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_801985E0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80198988);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80198C34);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80199278);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_80199390);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019AFE0);

INCLUDE_ASM("asm/ovl/effect_116/nonmatchings/effect_116", func_8019B25C);

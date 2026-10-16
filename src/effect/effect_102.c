/**
 * @file effect_102.c
 * @brief Thundara
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object16.h"

extern s32 D_801CBFDC[];
extern s32 D_801CC6C4[];

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A0044);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A00E4);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A016C);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A0320);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A03CC);

s32 func_801A0508(SVECTOR *pos, s32 y, s32 frame, s32 duration, u32 *ot, s32 mode, s32 head) {
    MATRIX matrix;
    s32 sine;
    s32 scale;
    BattleEffectPrim *prim;
    s32 result;

    sine = rsin((frame << 10) / duration);
    prim = func_800B3698(sizeof(BattleEffectPrim));
    scale = sine >> 2;
    matrix.m[0][0] = scale + 512;
    matrix.m[0][1] = 0;
    matrix.m[0][2] = 0;
    matrix.m[1][0] = 0;
    matrix.m[1][1] = sine * 2 - scale - (sine >> 3) + 256;
    matrix.m[1][2] = 0;
    matrix.m[2][0] = 0;
    matrix.m[2][1] = 0;
    matrix.m[2][2] = scale + 512;
    matrix.t[0] = pos->vx;
    matrix.t[1] = y;
    matrix.t[2] = pos->vz;
    CompMatrix(&D_800F02C8, &matrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    prim->dispatch = D_801CBFDC;
    prim->bgB = 0;
    prim->bgG = 0;
    prim->bgR = 0;
    prim->depth = sine;
    prim->flags = 0xF3;
    result = func_800CBC68(prim, ot, mode, head);
    func_800B36B8(sizeof(BattleEffectPrim));
    return result;
}

s32 func_801A0644(SVECTOR *pos, s32 y, s32 frame, s32 duration, u32 *ot, s32 mode, s32 head) {
    MATRIX matrix;
    s32 sine;
    BattleEffectPrim *prim;
    s32 result;

    sine = rsin((frame << 10) / duration);
    prim = func_800B3698(sizeof(BattleEffectPrim));
    matrix.m[0][0] = sine;
    matrix.m[0][1] = 0;
    matrix.m[0][2] = 0;
    matrix.m[1][0] = 0;
    matrix.m[1][1] = sine;
    matrix.m[1][2] = 0;
    matrix.m[2][0] = 0;
    matrix.m[2][1] = 0;
    matrix.m[2][2] = sine;
    matrix.t[0] = pos->vx;
    matrix.t[1] = y;
    matrix.t[2] = pos->vz;
    CompMatrix(&D_800F02C8, &matrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    prim->dispatch = D_801CC6C4;
    prim->bgB = 0;
    prim->bgG = 0;
    prim->bgR = 0;
    prim->depth = sine;
    prim->flags = 0xF3;
    result = func_800CBC68(prim, ot, mode, head);
    func_800B36B8(sizeof(BattleEffectPrim));
    return result;
}

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A0764);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A0FF0);

INCLUDE_ASM("asm/ovl/effect_102/nonmatchings/effect_102", func_801A1258);

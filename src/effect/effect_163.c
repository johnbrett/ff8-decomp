/**
 * @file effect_163.c
 * @brief Rough Divide
 */
#include "common.h"
#include "effect.h"
#include "battle/bc_object9.h"

typedef struct {
    /* 0x00 */ u8 pad000[12];
    /* 0x0C */ s16 frame;
    /* 0x0E */ s16 unk00E;
    /* 0x10 */ SVECTOR pos;
} RoughDivideTask;

extern u8 D_801EFA18[];
extern s32 D_801EEBCC;
extern s16 D_801EFDAC[];
extern SVECTOR D_801EFA30;

s32 func_801B5158(RoughDivideTask *task);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B0000);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B01B4);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B06BC);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B0CBC);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B1204);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B186C);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B1B04);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B1B30);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B1BE8);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B1CB4);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B23E0);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B2430);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B2644);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B26D0);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B2B94);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B3028);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B35D4);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B3BA8);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B42A4);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B42D8);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B44A0);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B458C);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B4B18);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B4B90);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B5158);

static void func_801B585C(void) {
    RoughDivideTask *task = func_800B2A84(D_801EFA18, func_801B5158);

    task->unk00E = 1;
    task->frame = 0;
    task->pos.vx = D_800EF2D0[D_801EEBCC].pos.vx;
    task->pos.vy = 0;
    task->pos.vz = D_801EFDAC[0];
    D_801EFA30 = task->pos;
}

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B5900);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B5D58);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B5EDC);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B5FD0);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B61B0);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B6378);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B64F4);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B65D4);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B67D0);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B69D8);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B6F84);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B74D8);

INCLUDE_ASM("asm/ovl/effect_163/nonmatchings/effect_163", func_801B7530);

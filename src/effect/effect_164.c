/**
 * @file effect_164.c
 * @brief Blasting Zone
 */
#include "common.h"
#include "effect.h"
#include "battle/bc_object9.h"

typedef struct {
    /* 0x00 */ u8 pad000[12];
    /* 0x0C */ s16 frame;
    /* 0x0E */ u8 pad00E[2];
    /* 0x10 */ SVECTOR pos;
    /* 0x18 */ u8 pad018[4];
    /* 0x1C */ s16 unk01C;
    /* 0x1E */ s16 unk01E;
} BlastingZoneTask;

extern u8 D_801EE660[];
extern SVECTOR D_801EE678;
extern s32 D_801ED828;

s32 func_801B6FC4(BlastingZoneTask *task);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B0000);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B02A8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B07B0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B0DB0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B12F8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B1960);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B1BF8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B1ED0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B2200);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B2594);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B2984);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B2DE0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B3330);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B3840);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B3E50);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B4094);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B40C8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B4118);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B4210);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B50F0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B5160);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B518C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B51BC);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B51F0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B52A8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B5374);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B5454);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B55F4);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B5694);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B5848);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B58E4);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B5DF4);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B6208);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B6414);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B6570);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B6748);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B68F4);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B6B24);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B6FC4);

static void func_801B70E0(void) {
    BlastingZoneTask *task = func_800B2A84(D_801EE660, func_801B6FC4);

    task->frame = 0;
    task->pos = D_801EE678;
    task->pos.pad = D_800EF2D0[D_801ED828].unk026 * 125 >> 8;
    task->unk01E = 128;
    task->unk01C = 128;
}

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B7184);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B732C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B7374);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B74D8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B753C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B76CC);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B772C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B7924);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B7A38);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B7D40);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B7F88);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8170);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8418);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8624);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8680);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8964);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8A24);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8BC0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8C54);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8DFC);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B8E90);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B931C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B94B0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B966C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B96A8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B9B68);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B9D0C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B9D64);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801B9FC8);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801BA01C);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801BA4B0);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801BA574);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801BA5CC);

INCLUDE_ASM("asm/ovl/effect_164/nonmatchings/effect_164", func_801BAD00);

/**
 * @file effect_172.c
 * @brief Morph
 */
#include "common.h"
#include "psxsdk/libgte.h"

extern SVECTOR D_801C3608[];
extern SVECTOR D_801D7644[];
extern s32 D_801D7224[];

#define MORPH_VERTEX_COUNT 261

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A00F4);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A0CE4);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A0FB0);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A1234);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A13C8);

void func_801A144C(s32 amplitude) {
    SVECTOR *source = D_801C3608;
    s32 i;
    s32 angle;
    s32 cosine;
    s32 sine;

    for (i = 0; i < MORPH_VERTEX_COUNT; i++) {
        angle = amplitude * rsin(D_801D7224[i] * 3) >> 12;
        cosine = rcos(angle);
        sine = rsin(angle);
        D_801D7644[i].vx = (source->vx * cosine >> 12) +
                          (source->vy * sine >> 12);
        D_801D7644[i].vy = (source->vx * -sine >> 12) +
                          (source->vy * cosine >> 12);
        D_801D7644[i].vz = source++->vz;
    }
}

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A1578);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A16A4);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A1814);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A1988);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A1DC0);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A1FEC);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A21EC);

INCLUDE_ASM("asm/ovl/effect_172/nonmatchings/effect_172", func_801A2400);

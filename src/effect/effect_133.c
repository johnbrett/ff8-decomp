/**
 * @file effect_133.c
 * @brief Hypnotize
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/inline_c.h"
#include "effect/lib/pose.h"

typedef struct {
    /* 0x00 */ MATRIX m;
    /* 0x20 */ s32 depthOffset;
    /* 0x24 */ SVECTOR *vertices;
} HypnotizeDrawRequest;

typedef union {
    /* 0x00 */ SVECTOR vector;
    /* 0x00 */ struct {
        /* 0x00 */ s16 x;
        /* 0x02 */ s16 y;
        /* 0x04 */ s16 z;
        /* 0x06 */ u16 scale;
    } fields;
} HypnotizeScaledPosition;

typedef struct {
    /* 0x00 */ u8 unk000[12];
    /* 0x0C */ HypnotizeScaledPosition pos;
    /* 0x14 */ s32 pose[1];
} HypnotizeModel;

typedef struct {
    /* 0x000 */ u8 unk000[0xE04];
    /* 0xE04 */ SVECTOR vertices[1];
} HypnotizeResources;

extern HypnotizeResources *D_801D776C;
extern void func_801A21E4(s32 *pose, EffectPartPose *part, void *request);

static s32 DrawHypnotizeModel(HypnotizeModel *model);

INCLUDE_ASM("asm/ovl/effect_133/nonmatchings/effect_133", func_801A2EF0);

INCLUDE_ASM("asm/ovl/effect_133/nonmatchings/effect_133", func_801A2FC4);

INCLUDE_ASM("asm/ovl/effect_133/nonmatchings/effect_133", func_801A306C);

static s32 DrawHypnotizeModel(HypnotizeModel *model) {
    HypnotizeDrawRequest request;

    gte_lddp(model->pos.fields.scale);
    gte_ldsv(D_800F02C8.m[0]);
    gte_gpf1();
    gte_stsv(request.m.m[0]);
    gte_ldsv(D_800F02C8.m[1]);
    gte_gpf1();
    gte_stsv(request.m.m[1]);
    gte_ldsv(D_800F02C8.m[2]);
    gte_gpf1();
    gte_stsv(request.m.m[2]);
    gte_SetRotMatrix(&D_800F02C8);
    gte_ldv0(&model->pos.vector);
    gte_mvmva(1, 0, 0, 3, 0);
    gte_stlvnl(request.m.t);
    request.depthOffset = -128;
    request.m.t[0] += D_800F02C8.t[0];
    request.m.t[1] += D_800F02C8.t[1];
    request.m.t[2] += D_800F02C8.t[2];
    request.vertices = D_801D776C->vertices;
    return effectPoseWalk(model->pose, func_801A21E4, &request) == 0 ? 2 : 0;
}

INCLUDE_ASM("asm/ovl/effect_133/nonmatchings/effect_133", func_801A3340);

INCLUDE_ASM("asm/ovl/effect_133/nonmatchings/effect_133", func_801A3720);

INCLUDE_ASM("asm/ovl/effect_133/nonmatchings/effect_133", func_801A3980);

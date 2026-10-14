/**
 * @file effect_277.c
 * @brief Funguar Laser
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/inline_c.h"
#include "effect/lib/pose.h"

typedef struct {
    /* 0x00 */ BattleMatrix m;
    /* 0x20 */ s32 depthOffset;
    /* 0x24 */ SVECTOR *vertices;
} FunguarLaserDrawRequest;

typedef struct {
    /* 0x000 */ u8 unk000[3876];
    /* 0xF24 */ SVECTOR vertices[1];
} FunguarLaserResources;

extern FunguarLaserResources *D_801D46E4;
extern void func_801A2274(s32 *pose, EffectPartPose *part, void *request);

static s32 DrawFunguarLaserModel(MATRIX *rotation, SVECTOR *offset,
                                 SVECTOR *position, s32 *pose);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A3008);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A30E4);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A31D8);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A3240);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A3360);

static s32 DrawFunguarLaserModel(MATRIX *rotation, SVECTOR *offset,
                                 SVECTOR *position, s32 *pose) {
    FunguarLaserDrawRequest request;
    u32 a;
    u32 b;
    u32 c;
    u32 d;
    u16 e;

    gte_SetRotMatrix(rotation);
    gte_ldv0(position);
    gte_mvmva(1, 0, 0, 3, 0);
    gte_stsv(position);
    position->vx += offset->vx;
    position->vy += offset->vy;
    position->vz += offset->vz;
    gte_SetRotMatrix(&D_800F02C8.matrix);
    gte_ldv0(position);
    gte_mvmva(1, 0, 0, 3, 0);
    gte_stlvnl(request.m.matrix.t);
    request.depthOffset = 0;
    request.m.matrix.t[0] += D_800F02C8.matrix.t[0];
    request.m.matrix.t[1] += D_800F02C8.matrix.t[1];
    request.m.matrix.t[2] += D_800F02C8.matrix.t[2];
    a = D_800F02C8.rotation.pairs[0];
    b = D_800F02C8.rotation.pairs[1];
    c = D_800F02C8.rotation.pairs[2];
    d = D_800F02C8.rotation.pairs[3];
    e = D_800F02C8.rotation.last;
    request.m.rotation.pairs[0] = a;
    request.m.rotation.pairs[1] = b;
    request.m.rotation.pairs[2] = c;
    request.m.rotation.pairs[3] = d;
    request.m.rotation.last = e;
    request.vertices = D_801D46E4->vertices;
    return effectPoseWalk(pose, func_801A2274, &request);
}

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A3584);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A3D00);

INCLUDE_ASM("asm/ovl/effect_277/nonmatchings/effect_277", func_801A3FD8);

/**
 * @file effect_134.c
 * @brief Beam Laser
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/inline_c.h"
#include "effect/lib/pose.h"

typedef struct {
    /* 0x00 */ BattleMatrix m;
    /* 0x20 */ s32 depthOffset;
    /* 0x24 */ SVECTOR *vertices;
} BeamLaserDrawRequest;

typedef struct {
    /* 0x000 */ u8 unk000[3168];
    /* 0xC60 */ SVECTOR vertices[1];
} BeamLaserResources;

extern BeamLaserResources *D_801D2540;
extern void func_801A21E4(s32 *pose, EffectPartPose *part, void *request);

static s32 DrawBeamLaserModel(MATRIX *rotation, SVECTOR *offset,
                              SVECTOR *position, s32 *pose);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A2F48);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A2FB0);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3088);

static s32 DrawBeamLaserModel(MATRIX *rotation, SVECTOR *offset,
                              SVECTOR *position, s32 *pose) {
    BeamLaserDrawRequest request;
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
    request.vertices = D_801D2540->vertices;
    return effectPoseWalk(pose, func_801A21E4, &request);
}

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A32AC);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3A6C);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3DB0);

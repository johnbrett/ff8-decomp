/**
 * @file effect_302.c
 * @brief Snipe Laser
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/inline_c.h"

typedef struct {
    /* 0x00 */ BattleMatrix m;
    /* 0x20 */ s32 depthOffset;
    /* 0x24 */ SVECTOR *vertices;
} SnipeLaserDrawRequest;

typedef struct {
    /* 0x000 */ u8 unk000[5512];
    /* 0x1588 */ SVECTOR vertices[1];
} SnipeLaserResources;

extern SnipeLaserResources *D_801D4698;

static void TransformSnipeLaserPosition(MATRIX *rotation, SVECTOR *offset,
                                        SVECTOR *position, void *unused);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A0308);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A0648);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A09D4);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A0DB8);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A10DC);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1480);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1840);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1C88);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1EB4);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1ED8);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1F54);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A1FD4);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A2050);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A20E0);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A2170);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A2274);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A260C);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A278C);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A27F4);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A285C);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A2A4C);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A3008);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A3070);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A3190);

static void TransformSnipeLaserPosition(MATRIX *rotation, SVECTOR *offset,
                                        SVECTOR *position, void *unused) {
    SnipeLaserDrawRequest request; /* The original builds this request without submitting it. */
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
    request.vertices = D_801D4698->vertices;
}

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A3398);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A346C);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A3BFC);

INCLUDE_ASM("asm/ovl/effect_302/nonmatchings/effect_302", func_801A3EF0);

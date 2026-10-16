#include "common.h"
#include "effect/lib/project.h"
#include "effect/lib/project_packet.h"
#include "psxsdk/libgpu.h"

typedef struct {
    /* 0x00 */ u32 unk000[12];
    /* 0x30 */ u32 colour;
    /* 0x34 */ u32 texture0;
    /* 0x38 */ u32 texture1;
    /* 0x3C */ u32 *ot;
    /* 0x40 */ s32 otShift;
    /* 0x44 */ void *cursor;
    /* 0x48 */ u32 unk048;
    /* 0x4C */ u32 unk04C;
    /* 0x50 */ s32 depth;
} SimpleTextureProjectionContext;

static void ProjectSimpleTextureTriangle(SimpleTextureProjectionContext *context,
                                        EffectTextureVertex *a, EffectTextureVertex *b,
                                        EffectTextureVertex *c);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190000);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190294);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_8019031C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_8019034C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801903C0);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801904B0);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801905B8);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_8019064C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190750);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801907A4);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190950);

static void ProjectSimpleTextureTriangle(SimpleTextureProjectionContext *context,
                                        EffectTextureVertex *a, EffectTextureVertex *b,
                                        EffectTextureVertex *c) {
    EffectTextureTriangle *triangle = context->cursor;

    gte_ldv3(a, b, c);
    gte_rtpt();
    setlen(triangle, 7);
    triangle->colour = context->colour | 0x24000000;
    triangle->texture0.word = context->texture0;
    triangle->texture1.word = context->texture1;
    gte_stsxy3(&triangle->xy0, &triangle->xy1, &triangle->xy2);
    gte_avsz3();
    triangle->texture0.fields.uv = a->uv;
    triangle->texture1.fields.uv = b->uv;
    triangle->texture2.fields.uv = c->uv;
    gte_stotz(&context->depth);
    addPrim(&context->ot[context->depth >> context->otShift], triangle);
    context->cursor = triangle + 1;
}

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190BA4);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190C94);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80190DE0);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801910A0);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80191568);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80191688);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80191E20);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801920DC);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_8019228C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80192330);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80192364);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801923B4);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801924AC);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_8019338C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801933FC);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_801937CC);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80193B34);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80193DC8);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80193E9C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_8019401C);

INCLUDE_ASM("asm/ovl/effect_327/nonmatchings/effect_327_start", func_80194170);

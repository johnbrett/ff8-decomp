#include "effect/lib/project.h"
#include "psxsdk/libgpu.h"
#include "psxsdk/libgte.h"
#include "psxsdk/inline_c.h"

#include "effect/lib/project_packet.h"

void ProjectTextureTriangle(EffectProjectionContext *context, EffectTextureVertex *a,
                            EffectTextureVertex *b, EffectTextureVertex *c) {
    EffectTextureTriangle *triangle = context->cursor;
    u32 colour;

    gte_ldv3(a, b, c);
    gte_rtpt();
    setlen(triangle, 7);
    colour = (context->texture1 & EFFECT_PROJECT_SEMITRANS) | 0x24000000;
    triangle->colour = context->colour | colour;
    triangle->texture0.word = context->texture0;
    triangle->texture1.word = context->texture1 & EFFECT_PROJECT_TEXTURE_MASK;
    gte_stsxy3(&triangle->xy0, &triangle->xy1, &triangle->xy2);
    gte_avsz3();
    triangle->texture0.fields.uv = a->uv;
    triangle->texture1.fields.uv = b->uv;
    triangle->texture2.fields.uv = c->uv;
    gte_stotz(&context->depth);
    addPrim(&context->ot[context->depth >> context->otShift], triangle);
    context->cursor = triangle + 1;
}

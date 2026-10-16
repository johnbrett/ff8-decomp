#include "effect/lib/project.h"
#include "psxsdk/libgpu.h"
#include "psxsdk/libgte.h"
#include "psxsdk/inline_c.h"

#include "effect/lib/project_packet.h"

void EmitProjectedTextureTriangle(EffectProjectionContext *context) {
    EffectTextureTriangle *triangle = context->cursor;
    u32 colour;

    setlen(triangle, 7);
    colour = (context->texture1 & EFFECT_PROJECT_SEMITRANS) | 0x24000000;
    triangle->colour = context->colour | colour;
    triangle->texture0.word = context->texture0;
    triangle->texture1.word = context->texture1 & EFFECT_PROJECT_TEXTURE_MASK;
    gte_stsxy3(&triangle->xy0, &triangle->xy1, &triangle->xy2);
    gte_avsz3();
    triangle->texture0.fields.uv = context->vertices[0].position.uv;
    triangle->texture1.fields.uv = context->vertices[1].position.uv;
    triangle->texture2.fields.uv = context->vertices[2].position.uv;
    gte_stotz(&context->depth);
    addPrim(&context->ot[context->depth >> context->otShift], triangle);
    context->cursor = triangle + 1;
}

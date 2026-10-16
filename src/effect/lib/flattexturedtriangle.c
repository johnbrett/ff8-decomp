#include "effect/lib/flattexturedtriangle.h"
#include "psxsdk/libgpu.h"
#include "psxsdk/inline_c.h"

void EmitFlatTexturedTriangle(TriangleProjectionContext *context) {
    FlatTextureTriangle *triangle = context->cursor;

    setlen(triangle, 7);
    triangle->colour = context->colour | 0x24000000;
    triangle->texture0.word = context->texture0;
    triangle->texture1.word = context->texture1;
    gte_stsxy3(&triangle->xy0, &triangle->xy1, &triangle->xy2);
    gte_avsz3();
    triangle->texture0.fields.uv = context->vertices[0].uv;
    triangle->texture1.fields.uv = context->vertices[1].uv;
    triangle->texture2.fields.uv = context->vertices[2].uv;
    gte_stotz(&context->depth);
    addPrim(&context->ot[context->depth >> context->otShift], triangle);
    context->cursor = triangle + 1;
}

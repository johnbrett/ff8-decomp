#include "effect/lib/screen_primitives.h"
#include "battle.h"
#include "psxsdk/inline_c.h"

void DrawProjectedGradientLine(SVECTOR *start, SVECTOR *end, u32 colour) {
    s32 depth;
    ProjectedGradientLine *line;

    gte_SetRotMatrix(&D_800F02C8);
    gte_SetTransMatrix(&D_800F02C8);
    line = g_effectGradientLineCursor;
    gte_ldv3(start, end, end);
    gte_rtpt();
    line->colour0.word = colour;
    setlen(line, 4);
    line->colour1.word = colour;
    line->colour0.components.cd = 0x52;
    gte_stsxy3(&line->xy0, &line->xy1, &line->xy1);
    gte_avsz3();
    gte_stotz(&depth);
    addPrim(&D_800FA5E8->ot[depth >> 2], line);
    line++;
    g_effectGradientLineCursor = line;
}

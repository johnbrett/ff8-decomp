#ifndef EFFECT_LIB_SCREEN_PRIMITIVES_H
#define EFFECT_LIB_SCREEN_PRIMITIVES_H

#include "psxsdk/libgte.h"
#include "psxsdk/libgpu.h"

typedef union {
    /* 0x00 */ u32 word;
    /* 0x00 */ CVECTOR components;
} LineColour;

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ LineColour colour0;
    /* 0x08 */ DVECTOR xy0;
    /* 0x0C */ LineColour colour1;
    /* 0x10 */ DVECTOR xy1;
} ProjectedGradientLine;

extern ProjectedGradientLine *g_effectGradientLineCursor;

POLY_F4 *DrawScreenTint(s32 r, s32 g, s32 b, s32 intensity, POLY_F4 *poly);
void DrawProjectedGradientLine(SVECTOR *start, SVECTOR *end, u32 colour);

#endif

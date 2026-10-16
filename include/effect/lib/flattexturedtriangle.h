#ifndef EFFECT_LIB_FLAT_TEXTURED_TRIANGLE_H
#define EFFECT_LIB_FLAT_TEXTURED_TRIANGLE_H

#include "common.h"
#include "psxsdk/libgte.h"

/* Word access preserves the 32-bit texture stores before the UV halves are set. */
typedef union {
    /* 0x00 */ u32 word;
    /* 0x00 */ struct {
        /* 0x00 */ u16 uv;
        /* 0x02 */ u16 id;
    } fields;
} FlatTextureWord;

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 colour;
    /* 0x08 */ DVECTOR xy0;
    /* 0x0C */ FlatTextureWord texture0;
    /* 0x10 */ DVECTOR xy1;
    /* 0x14 */ FlatTextureWord texture1;
    /* 0x18 */ DVECTOR xy2;
    /* 0x1C */ FlatTextureWord texture2;
} FlatTextureTriangle;

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u16 uv;
    /* 0x08 */ u32 unk008[2];
} TriangleProjectionVertex;

typedef struct {
    /* 0x00 */ u32 unk000[12];
    /* 0x30 */ u32 colour;
    /* 0x34 */ u32 texture0;
    /* 0x38 */ u32 texture1;
    /* 0x3C */ u32 *ot;
    /* 0x40 */ s32 otShift;
    /* 0x44 */ FlatTextureTriangle *cursor;
    /* 0x48 */ u32 unk048;
    /* 0x4C */ u32 unk04C;
    /* 0x50 */ s32 depth;
    /* 0x54 */ u32 unk054;
    /* 0x58 */ TriangleProjectionVertex vertices[3];
} TriangleProjectionContext;

void EmitFlatTexturedTriangle(TriangleProjectionContext *context);

#endif

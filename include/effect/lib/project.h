#ifndef EFFECT_LIB_PROJECT_H
#define EFFECT_LIB_PROJECT_H

#include <common.h>
#include "effect_params.h"

#define EFFECT_PROJECT_SEMITRANS 0x02000000
#define EFFECT_PROJECT_TEXTURE_MASK 0x01FFFFFF

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u16 uv;
} EffectTextureVertex;

typedef struct {
    /* 0x00 */ EffectTextureVertex position;
    /* 0x08 */ u32 unk008[2];
} EffectProjectionVertex;

#if EFFECT_PROJECTION_PREFIX_WORDS == 8
typedef struct {
    /* 0x00 */ u32 unk000[8];
    /* 0x20 */ u32 colour;
    /* 0x24 */ u32 texture0;
    /* 0x28 */ u32 texture1;
    /* 0x2C */ u32 *ot;
    /* 0x30 */ s32 otShift;
    /* 0x34 */ void *cursor;
    /* 0x38 */ u32 unk038;
    /* 0x3C */ u32 unk03C;
    /* 0x40 */ s32 depth;
    /* 0x44 */ u32 unk044;
    /* 0x48 */ EffectProjectionVertex vertices[3];
} EffectProjectionContext;
#else
typedef struct {
    /* 0x00 */ u32 unk000[6];
    /* 0x18 */ u32 colour;
    /* 0x1C */ u32 texture0;
    /* 0x20 */ u32 texture1;
    /* 0x24 */ u32 *ot;
    /* 0x28 */ s32 otShift;
    /* 0x2C */ void *cursor;
    /* 0x30 */ u32 unk030;
    /* 0x34 */ u32 unk034;
    /* 0x38 */ s32 depth;
    /* 0x3C */ u32 unk03C;
    /* 0x40 */ EffectProjectionVertex vertices[3];
} EffectProjectionContext;
#endif

void ProjectTextureTriangle(EffectProjectionContext *context, EffectTextureVertex *a,
                            EffectTextureVertex *b, EffectTextureVertex *c);

void EmitProjectedTextureTriangle(EffectProjectionContext *context);

#endif

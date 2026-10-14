#ifndef EFFECT_LIB_PROJECT_PACKET_H
#define EFFECT_LIB_PROJECT_PACKET_H

#include "psxsdk/libgte.h"

typedef union {
    /* 0x00 */ u32 word;
    /* 0x00 */ struct {
        /* 0x00 */ u16 uv;
        /* 0x02 */ u16 id;
    } fields;
} EffectTextureWord;

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 colour;
    /* 0x08 */ DVECTOR xy0;
    /* 0x0C */ EffectTextureWord texture0;
    /* 0x10 */ DVECTOR xy1;
    /* 0x14 */ EffectTextureWord texture1;
    /* 0x18 */ DVECTOR xy2;
    /* 0x1C */ EffectTextureWord texture2;
} EffectTextureTriangle;

#endif

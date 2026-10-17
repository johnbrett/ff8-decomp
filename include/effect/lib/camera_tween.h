#ifndef EFFECT_LIB_CAMERA_TWEEN_H
#define EFFECT_LIB_CAMERA_TWEEN_H

#include "common.h"

typedef struct {
    /* 0x00 */ u8 pad000[80];
    /* 0x50 */ s16 *weights;
    /* 0x54 */ s16 unk054;
    /* 0x56 */ s16 unk056;
    /* 0x58 */ s16 unk058;
    /* 0x5A */ s16 unk05A;
    /* 0x5C */ s16 unk05C;
    /* 0x5E */ s16 unk05E;
    /* 0x60 */ s16 unk060;
    /* 0x62 */ s16 unk062;
    /* 0x64 */ s16 unk064;
    /* 0x66 */ s16 unk066;
    /* 0x68 */ s16 unk068;
    /* 0x6A */ s16 unk06A;
    /* 0x6C */ s16 unk06C;
    /* 0x6E */ s16 unk06E;
    /* 0x70 */ s16 unk070;
    /* 0x72 */ s16 unk072;
    /* 0x74 */ s16 unk074;
    /* 0x76 */ s16 unk076;
    /* 0x78 */ s16 unk078;
    /* 0x7A */ s16 unk07A;
    /* 0x7C */ s16 unk07C;
    /* 0x7E */ s16 unk07E;
    /* 0x80 */ s16 unk080;
    /* 0x82 */ u8 pad082[50];
    /* 0xB4 */ s16 unk0B4;
    /* 0xB6 */ s16 unk0B6;
    /* 0xB8 */ s16 unk0B8;
    /* 0xBA */ s16 unk0BA;
    /* 0xBC */ s16 unk0BC;
    /* 0xBE */ s16 unk0BE;
    /* 0xC0 */ s16 unk0C0;
    /* 0xC2 */ s16 unk0C2;
    /* 0xC4 */ s16 unk0C4;
    /* 0xC6 */ s16 unk0C6;
    /* 0xC8 */ s16 unk0C8;
    /* 0xCA */ s16 unk0CA;
    /* 0xCC */ s16 unk0CC;
    /* 0xCE */ s16 unk0CE;
    /* 0xD0 */ s16 weight;
    /* 0xD2 */ s16 velocity;
    /* 0xD4 */ s16 acceleration;
    /* 0xD6 */ s16 limit;
    /* 0xD8 */ s16 angle0;
    /* 0xDA */ s16 angle1;
    /* 0xDC */ s16 angle2;
    /* 0xDE */ s16 distance;
    /* 0xE0 */ s16 unk0E0;
    /* 0xE2 */ s16 frame;
} EffectCameraTween;

extern EffectCameraTween *g_effectCameraTween;

void EffectCameraHelper(void);
s32 UpdateEffectCameraTween(void);

#endif

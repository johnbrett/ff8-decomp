#ifndef EFFECT_LIB_ARCTRAIL_H
#define EFFECT_LIB_ARCTRAIL_H

#include "psxsdk/libgte.h"

typedef struct {
    /* 0x000 */ u8 unk000[28];
    /* 0x01C */ SVECTOR position;
    /* 0x024 */ u8 unk024[60];
    /* 0x060 */ MATRIX rotation;
    /* 0x080 */ SVECTOR end;
    /* 0x088 */ SVECTOR start;
    /* 0x090 */ SVECTOR history[11];
    /* 0x0E8 */ u8 unk0E8[60];
    /* 0x124 */ s16 frame;
} EffectArcTrail;

void StepEffectArcTrail(EffectArcTrail *trail);

#endif

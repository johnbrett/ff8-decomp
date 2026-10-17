#ifndef EFFECT_LIB_CAMERA_MOTION_H
#define EFFECT_LIB_CAMERA_MOTION_H

#include "psxsdk/libgte.h"

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} EffectCameraPoint;

typedef struct {
    /* 0x00 */ EffectCameraPoint target;
    /* 0x06 */ EffectCameraPoint position;
} EffectCameraKeyframe;

extern SVECTOR D_800E3D70;
extern SVECTOR D_800E3D78;

void OrbitEffectCamera(s32 angle, s32 scale);
void BlendEffectCameraKeyframes(EffectCameraKeyframe *from, EffectCameraKeyframe *to,
                               s32 weight);

#endif

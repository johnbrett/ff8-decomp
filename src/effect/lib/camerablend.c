#include "effect/lib/camera_motion.h"
#include "battle.h"
#include "psxsdk/inline_c.h"

void BlendEffectCameraKeyframes(EffectCameraKeyframe *from, EffectCameraKeyframe *to, s32 weight) {
    s32 inverse = ONE - weight;

    gte_lddp(inverse);
    gte_ldsv(&from->target);
    gte_gpf1();
    gte_lddp(weight);
    gte_ldsv(&to->target);
    gte_gpl1();
    gte_stsv(&D_800E3D78);
    gte_lddp(inverse);
    gte_ldsv(&from->position);
    gte_gpf1();
    gte_lddp(weight);
    gte_ldsv(&to->position);
    gte_gpl1();
    gte_stsv(&D_800E3D70);
}

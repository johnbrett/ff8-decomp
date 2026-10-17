#include "effect/lib/camera_motion.h"
#include "battle.h"
#include "psxsdk/inline_c.h"

void OrbitEffectCamera(s32 angle, s32 scale) {
    s32 x, y, z;
    s32 sine, cosine;
    y = ((D_800E3D70.vy - D_800E3D78.vy) * scale) >> 12;
    x = ((D_800E3D70.vx - D_800E3D78.vx) * scale) >> 12;
    z = ((D_800E3D70.vz - D_800E3D78.vz) * scale) >> 12;
    D_800E3D70.vy = D_800E3D78.vy + y;
    sine = rsin(angle);
    cosine = rcos(angle);
    D_800E3D70.vx = D_800E3D78.vx + ((x * cosine - z * sine) >> 12);
    D_800E3D70.vz = D_800E3D78.vz + ((x * sine + z * cosine) >> 12);
}

#include "effect/lib/camera_tween.h"

enum {
    CAMERA_TURN_FORWARD,
    CAMERA_TURN_REVERSE,
    CAMERA_TURN_HOLD
};

s32 UpdateEffectCameraTween(void) {
    s32 done = 0;
    s16 value;
    s16 reverse;
    s16 *weights = g_effectCameraTween->weights;

    g_effectCameraTween->frame++;
    if (weights == NULL) {
        g_effectCameraTween->velocity += g_effectCameraTween->acceleration;
        if (g_effectCameraTween->acceleration > 0) {
            if (g_effectCameraTween->velocity > g_effectCameraTween->limit) {
                g_effectCameraTween->velocity = g_effectCameraTween->limit;
            }
        } else if (g_effectCameraTween->acceleration < 0) {
            if (g_effectCameraTween->velocity < g_effectCameraTween->limit) {
                g_effectCameraTween->velocity = g_effectCameraTween->limit;
            }
        }
        g_effectCameraTween->weight += g_effectCameraTween->velocity;
    } else {
        g_effectCameraTween->weight = *weights;
        if (g_effectCameraTween->weight != 4096) {
            g_effectCameraTween->weights++;
        }
    }
    if (g_effectCameraTween->weight >= 4096) {
        g_effectCameraTween->weight = 4096;
        done = 1;
    }
    if (g_effectCameraTween->unk0B4 == CAMERA_TURN_FORWARD) {
        value = g_effectCameraTween->unk0C4;
        if (g_effectCameraTween->unk0C2 > g_effectCameraTween->unk0C4) {
            value += 4096;
        }
        g_effectCameraTween->angle0 =
            (g_effectCameraTween->unk0C2 +
            (value - g_effectCameraTween->unk0C2) *
            g_effectCameraTween->weight / 4096) & 0xFFF;
    } else {
        reverse = g_effectCameraTween->unk0C2;
        if (reverse < g_effectCameraTween->unk0C4) {
            reverse += 4096;
        }
        g_effectCameraTween->angle0 =
            (reverse +
            (g_effectCameraTween->unk0C4 - reverse) *
            g_effectCameraTween->weight / 4096) & 0xFFF;
    }
    switch (g_effectCameraTween->unk0B6) {
    case CAMERA_TURN_HOLD:
        break;
    case CAMERA_TURN_FORWARD:
        value = g_effectCameraTween->unk0C8;
        if (g_effectCameraTween->unk0C6 > g_effectCameraTween->unk0C8) {
            value += 4096;
        }
        g_effectCameraTween->angle1 =
            (g_effectCameraTween->unk0C6 +
            (value - g_effectCameraTween->unk0C6) *
            g_effectCameraTween->weight / 4096) & 0xFFF;
        break;
    case CAMERA_TURN_REVERSE:
        reverse = g_effectCameraTween->unk0C6;
        if (reverse < g_effectCameraTween->unk0C8) {
            reverse += 4096;
        }
        g_effectCameraTween->angle1 =
            (reverse +
            (g_effectCameraTween->unk0C8 - reverse) *
            g_effectCameraTween->weight / 4096) & 0xFFF;
        break;
    }
    if (g_effectCameraTween->unk0B8 == CAMERA_TURN_FORWARD) {
        value = g_effectCameraTween->unk0CC;
        if (g_effectCameraTween->unk0CA > g_effectCameraTween->unk0CC) {
            value += 4096;
        }
        g_effectCameraTween->angle2 =
            (g_effectCameraTween->unk0CA +
            (value - g_effectCameraTween->unk0CA) *
            g_effectCameraTween->weight / 4096) & 0xFFF;
    } else {
        reverse = g_effectCameraTween->unk0CA;
        if (reverse < g_effectCameraTween->unk0CC) {
            reverse += 4096;
        }
        g_effectCameraTween->angle2 =
            (reverse +
            (g_effectCameraTween->unk0CC - reverse) *
            g_effectCameraTween->weight / 4096) & 0xFFF;
    }
    g_effectCameraTween->unk0E0 =
        g_effectCameraTween->unk0BA +
        (g_effectCameraTween->unk0BC - g_effectCameraTween->unk0BA) *
        g_effectCameraTween->weight / 4096;
    g_effectCameraTween->distance =
        g_effectCameraTween->unk0BE +
        (g_effectCameraTween->unk0C0 - g_effectCameraTween->unk0BE) *
        g_effectCameraTween->weight / 4096;
    switch (g_effectCameraTween->unk0CE) {
    case 0:
        g_effectCameraTween->unk05C =
            g_effectCameraTween->unk064 +
            (g_effectCameraTween->unk06C - g_effectCameraTween->unk064) *
            g_effectCameraTween->weight / 4096;
        g_effectCameraTween->unk05E =
            g_effectCameraTween->unk066 +
            (g_effectCameraTween->unk06E - g_effectCameraTween->unk066) *
            g_effectCameraTween->weight / 4096;
        g_effectCameraTween->unk060 =
            g_effectCameraTween->unk068 +
            (g_effectCameraTween->unk070 - g_effectCameraTween->unk068) *
            g_effectCameraTween->weight / 4096;
        break;
    case 1:
        g_effectCameraTween->unk054 =
            g_effectCameraTween->unk074 +
            (g_effectCameraTween->unk07C - g_effectCameraTween->unk074) *
            g_effectCameraTween->weight / 4096;
        g_effectCameraTween->unk056 =
            g_effectCameraTween->unk076 +
            (g_effectCameraTween->unk07E - g_effectCameraTween->unk076) *
            g_effectCameraTween->weight / 4096;
        g_effectCameraTween->unk058 =
            g_effectCameraTween->unk078 +
            (g_effectCameraTween->unk080 - g_effectCameraTween->unk078) *
            g_effectCameraTween->weight / 4096;
        break;
    }
    EffectCameraHelper();
    return done;
}

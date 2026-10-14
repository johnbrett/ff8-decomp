#include "effect/lib/arctrail.h"

void StepEffectArcTrail(EffectArcTrail *trail) {
    SVECTOR offset;
    SVECTOR rotated;
    s32 frame = trail->frame;
    s32 x;
    s32 y;
    s32 z;
    s16 angle;

    trail->position = trail->start;
    x = (trail->end.vx - trail->start.vx) * trail->frame / 10;
    y = (trail->end.vy - trail->start.vy) * trail->frame / 10;
    z = (trail->end.vz - trail->start.vz) * trail->frame / 10;
    trail->position.vx += x;
    trail->position.vy += y;
    trail->position.vz += z;
    angle = frame * 204;
    offset.vx = 0;
    offset.vy = rsin(angle) / 3;
    offset.vz = 0;
    ApplyMatrixSV(&trail->rotation, &offset, &rotated);
    trail->position.vx += rotated.vx;
    trail->position.vy += rotated.vy;
    trail->position.vz += rotated.vz;
    trail->history[trail->frame] = trail->position;
}


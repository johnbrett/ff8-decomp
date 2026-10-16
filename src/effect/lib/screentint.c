#include "effect/lib/screen_primitives.h"
#include "battle.h"

POLY_F4 *DrawScreenTint(s32 r, s32 g, s32 b, s32 intensity, POLY_F4 *poly) {
    r *= intensity;
    g *= intensity;
    b *= intensity;
    poly->x1 = poly->x3 = 320;
    poly->y2 = poly->y3 = 216;
    setPolyF4(poly);
    setSemiTrans(poly, 1);
    poly->y0 = poly->y1 = poly->x2 = poly->x0 = 0;
    setRGB0(poly, r >> 12, g >> 12, b >> 12);
    addPrim(&D_800FA5E8->frontOT[3], poly);
    return poly + 1;
}

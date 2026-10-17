#include "common.h"
#include "psxsdk/inline_c.h"
#include "world/we_object1.h"
#include "world/we_object3.h"
#include "world/we_object4.h"
#include "world/we_object5.h"
#include "world/we_object8.h"
#include "world/we_object9.h"
#include "world/we_object10.h"
#include "psxsdk/libgte.h"
#include "world/we_object2.h"

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object8", func_800B8C70);

// Returns the index of the direction with rank which: 0 turns least away from angle, 2 the most.
s32 func_800B97A0(s32 which, s16 angle, SVECTOR *v) {
    SVECTOR rot;
    SVECTOR *r;
    s16 delta[3];
    SVECTOR range;
    s32 rank[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        rot.vx = ratan2(-v[i].vy, SquareRoot0(v[i].vz * v[i].vz + v[i].vx * v[i].vx));
        r = &rot; // writing vy/vz through a pointer is needed for the match
        r->vy = ratan2(v[i].vx, v[i].vz);
        r->vz = 0;
        delta[i] = (getAngleDelta(angle, rot.vy) > 0) ? getAngleDelta(angle, rot.vy)
                                                       : -getAngleDelta(angle, rot.vy);
    }
    range.vx = (delta[0] < delta[1]) ? ((delta[0] < delta[2]) ? delta[0] : delta[2])
                                     : ((delta[1] < delta[2]) ? delta[1] : delta[2]);
    range.vz = (delta[0] > delta[1]) ? ((delta[0] > delta[2]) ? delta[0] : delta[2])
                                     : ((delta[1] > delta[2]) ? delta[1] : delta[2]);
    for (i = 0; i < 3; i++) {
        if (range.vx == delta[i]) {
            rank[0] = i;
        } else if (range.vz == delta[i]) {
            rank[2] = i;
        } else {
            rank[1] = i;
        }
    }
    return rank[which];
}

s32 func_800B99A4(u16 *battleId) {
    GlyphQuery query;
    SVECTOR delta;
    VECTOR squared;
    AngleSlot height;
    SlotEntry *slot;
    CmdDesc *descriptor;

    if (D_800C5C34 < 0) {
        return 0;
    }
    slot = &D_800DBFB8[D_800C5C34];
    if (((u32) D_800C4D38 < 10 || D_800C4D38 == 128) && slot->pad13 == 1 &&
        D_800C4D98 != 0 && D_800C4D98 != 4) {
        delta.vx = D_800C9770[0].vx - slot->unk1C;
        delta.vy = D_800C9770[0].vy - slot->unk1E;
        delta.vz = D_800C9770[0].vz - slot->unk20;
        gte_ldsv(&delta);
        gte_SQR(0);
        gte_stlvnl(&squared);
        if ((u32) (squared.vx + squared.vz) < 40000U) {
            *battleId = 712;
            return 1;
        }
    }
    if (D_800C4D98 == 0) {
        D_800C4D70 = 0;
        D_800DBF48.vx = D_800C5C08.vx + func_8009CC3C() * 16;
        D_800DBF48.vy = D_800C5C08.vy;
        D_800DBF48.vz = D_800C5C08.vz - func_8009CC3C() * 16;
        query.pos = D_800DBF48;
        query.buf.angle = worldPosToCell(&query.pos, &query.buf.proj);
        gte_ldtr(0, 0, 0);
        descriptor = glyphAt(&query, &height);
        if (descriptor != NULL && D_800C4D64 != descriptor && descriptor->type == 8) {
            slot->position = D_800DBF48;
            slot->vec.vx = 0;
            slot->vec.vy = 0;
            slot->vec.vz = 0;
            D_800C5D68 = 0;
            D_800C4D70 = descriptor;
            slot->position.vy = height.word;
            D_800C4D98++;
        }
    }
    if (D_800C4D98 == 1) {
        if (++D_800C5D68 >= 30) {
            D_800C4D98 = 2;
            D_800C5D68 = 0;
        }
        func_800AB2D4(&slot->position);
    }
    if (D_800C4D98 == 2) {
        if (++D_800C5D68 >= 30) {
            D_800C4D98 = 3;
            D_800C5D68 = 0;
        }
    }
    if (D_800C4D98 == 3) {
        if (++D_800C5D68 >= 30) {
            D_800C4D98 = 4;
            D_800C5D68 = 0;
        }
        func_800AB2D4(&slot->position);
    }
    if (D_800C4D98 == 4) {
        D_800C4D70 = 0;
        if (++D_800C5D68 >= 60) {
            D_800C4D98 = 0;
            D_800C5D68 = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object8", func_800B9D38);

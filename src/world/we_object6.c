#include "common.h"
#include "world.h"
#include "world/we_object6.h"
#include "world/we_object1.h"
#include "world/we_object2.h"
#include "world/we_object5.h"
#include "world/we_object7.h"
#include "world/we_object9.h"
#include "world/we_object10.h"
#include "psxsdk/libc.h"
#include "psxsdk/libetc.h"
#include "psxsdk/libgte.h"

typedef struct {
    /* 0x00 */ s8 busy; // Non-zero: no new kind this frame
    /* 0x01 */ u8 code; // Raw placement code; 0x20..0x28 and 0x84 are accepted
} PlacementReq;

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u16 flags; // PROJ_VERT_*
} ProjVert;

#define PROJ_VERT_IN_X 0x001 // Screen x in 0..319
#define PROJ_VERT_IN_Y 0x100 // Screen y in 0..239

typedef struct {
    /* 0x00 */ u8 data[12];
} WorldModelTri;

typedef struct {
    /* 0x00 */ u8 data[16];
} WorldModelQuad;

// Followed by nQuads WorldModelQuad records and then nVerts SVECTORs.
typedef struct {
    /* 0x00 */ s16 nTris;
    /* 0x02 */ s16 nQuads;
    /* 0x04 */ s16 pad04;
    /* 0x06 */ u16 nVerts;
    /* 0x08 */ WorldModelTri tris[1];
} WorldModel;

typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} WorldModelCtx;

// Private prototypes
static void func_800AE0C8(WorldObjList *actor, SlotEntry *slot, Slot *ctx, PlacementReq *req);
s32 func_800B1174(WorldModel *model, ProjVert *verts, s32 a, s32 b);
s32 func_800B13B8(WorldModel *model, ProjVert *verts, s32 a, s32 b);
static void DrawBankModel(s8 kind, MATRIX *m, SVECTOR *pos, SVECTOR *rot, WorldModelCtx *ctx);
static void PlacePlayerAtSpawn(u8 *flags, s32 spawn);
static void func_800B20E4(u8 *flags, s32 actorIdx, s8 flag, s32 mode);
s32 func_800B28C8(s32 kind, SVECTOR *pts, s16 a, s16 b, SlotEntry *slot, s32 mode, s32 e, s32 f);
static s32 SlotOutlineOverlaps(SVECTOR *quad, SlotEntry *slot, SVECTOR *pts);

void func_800ACC68(MATRIX *outMat, SVECTOR *angles, SVECTOR *rotBuf, SVECTOR *offset) {
    MATRIX m;
    VECTOR t;
    s32 flag;

    RotMatrixYXZ(angles, &m);
    SetRotMatrix(&m);
    t.vx = rotBuf->vx;
    t.vy = rotBuf->vy;
    t.vz = rotBuf->vz;
    func_80040534(&m, &t);
    SetTransMatrix(&m);
    RotTrans(offset, (VECTOR *)m.t, &flag);
    TransposeMatrix(&m, outMat);
    ApplyMatrixLV(outMat, (VECTOR *)m.t, (VECTOR *)outMat->t);
    outMat->t[0] = -outMat->t[0];
    outMat->t[1] = -outMat->t[1];
    outMat->t[2] = -outMat->t[2];
}

/**
 * @brief Snapshot @c D_800D2390.tail with an angle-adjusted @c angle
 *        halfword, then forward to @c func_800ACC68.
 *
 * Steps:
 *  1. Compute @c delta = @c getAngleDelta(@c D_800C977A,
 *     @c D_800D2390.tail.vy) @c >> @c 1 — half the signed result.
 *  2. Snapshot @c D_800D2390.tail into a local SVECTOR via
 *     @c memcpy. The source is cast to @c (u8 @c *) so the compiler
 *     emits @c lwl / @c lwr (matching the target's byte-granular 8-byte
 *     copy).
 *  3. Add @c delta to the @c angle of the local copy.
 *  4. Forward @c (arg, @c &buf, @c D_800C97F8, @c &D_800D2390) to
 *     @c func_800ACC68.
 *
 * @note Purpose uncertain — appears to apply an angle correction to a
 *       cached transform/rotation payload before dispatching world-render
 *       work.
 *
 * @param outMat Destination matrix, forwarded to @c func_800ACC68.
 */
void func_800ACD38(MATRIX *outMat) {
    SVECTOR buf;
    s32 delta;

    delta = getAngleDelta(D_800C977A, D_800D2390.tail.vy) >> 1;

    memcpy(&buf, (u8 *)&D_800D2390.tail, sizeof(buf));

    buf.vy += delta;

    func_800ACC68(outMat, &buf, D_800C97F8, &D_800D2390.head);
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800ACDC4);

void func_800AD688(void) {
}

void func_800AD690(void) {
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800AD698);

/**
 * @brief Walk the placement script and emit slot entries for FF13/FF14 ops.
 *
 * Reads the script returned by @c func_800AF004 (base @c D_800D2288) and
 * dispatches each FF13/FF14 placement opcode to @c RegisterSceneObject, building
 * the rotation/translation pair from one of:
 *   - @c ctx track A (low byte 0x01)
 *   - @c ctx track B (low byte 0x40 / 0x41)
 *   - @c D_800D2128 entry indexed by the high byte (when high byte >= 0)
 *   - all-zero defaults (when high byte < 0)
 *
 * @param actor Opaque marker buffer with a 0x40-byte slot table at offset 6.
 * @param slot  First @c SlotEntry; advances by one entry per emitted slot.
 * @param ctx   Slot context holding two transform tracks at +0x18 and +0x24.
 * @return 1 if at least one slot was emitted, 0 otherwise.
 */
s32 func_800ADE24(WorldObjList *actor, SlotEntry *slot, Slot *ctx) {
    SVECTOR rot;
    s32 didWork;
    VECTOR trans;
    ScriptOp *p;

    didWork = 0;
    p = func_800AF004(D_800D2288, 0);
    if (p == 0) return didWork;

    while (1) {
        u16 op = p->op;
        if (op == 0xFF05) break;

        if (op == 0xFF0E) {
            p = (ScriptOp *)(D_800D2288 + p->param);
            continue;
        }

        if (op == 0xFF13 || op == 0xFF14) {
            u16 paramVal = p->param;
            s32 lowByte = *(u8 *)&p->param;
            s32 highByte = paramVal >> 8;

            if (lowByte != 3 || func_800BEFC4() != 0) {
                if (lowByte == 1) {
                    rot.vz = 0;
                    rot.vx = 0;
                    rot.vy = ctx->tracks[2].rot_y;
                    trans.vx = ctx->tracks[2].trans_x;
                    trans.vy = ctx->tracks[2].trans_y;
                    trans.vz = -ctx->tracks[2].trans_z;
                    RegisterSceneObject(actor, slot, 1, 0, &rot, &trans);
                } else if (lowByte == 0x40) {
                    rot.vz = 0;
                    rot.vx = 0;
                    rot.vy = ctx->tracks[3].rot_y;
                    trans.vx = ctx->tracks[3].trans_x;
                    trans.vy = ctx->tracks[3].trans_y;
                    trans.vz = -ctx->tracks[3].trans_z;
                    RegisterSceneObject(actor, slot, 0x40, 0, &rot, &trans);
                } else if (lowByte == 0x41) {
                    rot.vz = 0;
                    rot.vx = 0;
                    rot.vy = ctx->tracks[3].rot_y;
                    trans.vx = ctx->tracks[3].trans_x;
                    trans.vy = ctx->tracks[3].trans_y;
                    trans.vz = -ctx->tracks[3].trans_z;
                    RegisterSceneObject(actor, slot, 0x41, 2, &rot, &trans);
                } else if ((s8)highByte >= 0) {
                    s32 rz;
                    trans = *(VECTOR *)&D_800D2128[(s8)highByte];
                    rot.vy = D_800D2128[(s8)highByte].rot_y;
                    rz = D_800D2128[(s8)highByte].rot_z;
                    rot.vz = rz;
                    rot.vx = 0;
                    RegisterSceneObject(actor, slot, lowByte, (lowByte == 0x50) ? 4 : 0, &rot, &trans);
                } else {
                    rot.vz = 0;
                    rot.vy = 0;
                    rot.vx = 0;
                    RegisterSceneObject(actor, slot, lowByte, 0, &rot, NULL);
                }

                slot++;
                D_800C5B50++;
                didWork = 1;
            }
        }

        p++;
    }

    return didWork;
}

static void func_800AE0C8(WorldObjList *actor, SlotEntry *slot, Slot *ctx, PlacementReq *req) {
    SVECTOR rot;
    VECTOR trans;
    GameState *gs;
    s8 kind;
    u8 t;
    s32 code;

    gs = &g_gameState;
    if (func_800BD754(0x5C) >= 0) {
        if (D_800C971C != 0) {
            ctx->kind[1] = -1;
        } else {
            ctx->kind[0] = -1;
        }
    } else if (req->busy == 0) {
        code = req->code;
        if ((code >= 0x20 && code <= 0x28) || code == 0x84) {
            // The original passes the code sign-extended.
            if (D_800C971C != 0) {
                ctx->kind[1] = func_800B0010((s8)code);
            } else {
                ctx->kind[0] = func_800B0010((s8)code);
            }
        }
    }
    if (D_800C971C != 0) {
        kind = ctx->kind[1];
    } else {
        kind = ctx->kind[0];
    }
    if ((func_800B00D8(kind) >= 0x20 && func_800B00D8(kind) < 0x29) || func_800B00D8(kind) == 0x84) {
        t = (D_800C971C != 0) ? 5 : 4;
        rot.vz = 0;
        rot.vx = 0;
        rot.vy = ctx->tracks[t].rot_y;
        trans.vx = ctx->tracks[t].trans_x;
        trans.vy = ctx->tracks[t].trans_y;
        trans.vz = -ctx->tracks[t].trans_z;
        RegisterSceneObject(actor, slot, kind, 0, &rot, &trans);
        D_800C5C28 = D_800C5B50;
        D_800C5B50++;
    }
    if (!(gs->gfs[13].exists & 1)) {
        RegisterSceneObject(actor, &D_800DBFB8[D_800C5B50], 0x5E, 0, NULL, &D_800C5C08);
        D_800C5C34 = D_800C5B50;
        D_800C5B50++;
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", InitActors);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800AE518);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800AEB58);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800AEEB0);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800AF004);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800AF28C);

/**
 * @brief Inverse of @c func_800B00D8 — map a marker code back to raw kind.
 *
 * Accepts @p kind in @c [0, 0x84); returns the compact marker byte used
 * by surrounding slot code. Out-of-range or unmapped kinds return @c -1.
 */
s32 func_800B0010(u32 kind) {
    s32 out = -1;
    if (kind < 0x84) {
        switch (kind) {
            case 0x01: out = 4;    break;
            case 0x02: out = 5;    break;
            case 0x06: out = 6;    break;
            case 0x00:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x07:
            case 0x08:
            case 0x09: out = 0;    break;
            case 0x83: out = 0x46; break;
            case 0x22: out = 0x51; break;
            case 0x23: out = 0x52; break;
            case 0x24: out = 0x53; break;
            case 0x25: out = 0x54; break;
            case 0x26: out = 0x55; break;
            case 0x27: out = 0x56; break;
            case 0x28: out = 0x57; break;
            case 0x20: out = 0x4A; break;
            case 0x30: out = 0x40; break;
            case 0x31: out = 2;    break;
            case 0x32: out = 1;    break;
            case 0x41: out = 0x4D; break;
            case 0x42: out = 0x4E; break;
            case 0x21: out = 0x49; break;
        }
    }
    return out;
}

/**
 * @brief Remap a raw slot-kind byte into a compact marker code.
 *
 * Lookup helper used by world-engine slot classifiers. Accepts an 8-bit
 * @p kind; returns @c -1 for values >= @c 0x58 or for cases left blank in
 * the table. Covered cases (partial): menu items @c 0x00-0x06, level
 * markers @c 0x40/0x41, string groups @c 0x49-0x4E, and the @c 0x51-0x57
 * command row.
 */
s32 func_800B00D8(u32 kind) {
    s32 out = -1;
    if (kind < 0x58) {
        switch (kind) {
            case 0x00: out = 0;    break;
            case 0x04: out = 1;    break;
            case 0x05: out = 2;    break;
            case 0x06: out = 6;    break;
            case 0x46: out = 0x83; break;
            case 0x51: out = 0x22; break;
            case 0x52: out = 0x23; break;
            case 0x53: out = 0x24; break;
            case 0x54: out = 0x25; break;
            case 0x55: out = 0x26; break;
            case 0x56: out = 0x27; break;
            case 0x57: out = 0x28; break;
            case 0x4A:
            case 0x4B: out = 0x20; break;
            case 0x40:
            case 0x41: out = 0x30; break;
            case 0x02:
            case 0x03: out = 0x31; break;
            case 0x01: out = 0x32; break;
            case 0x4D: out = 0x41; break;
            case 0x4E: out = 0x42; break;
            case 0x49: out = 0x21; break;
        }
    }
    return out;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800B01A0);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800B04CC);

static void DrawBankModel(s8 kind, MATRIX *m, SVECTOR *pos, SVECTOR *rot, WorldModelCtx *ctx) {
    MATRIX mat;
    SVECTOR ofs;
    ProjVert buf[256];
    WorldModel *model;
    SVECTOR *v;
    ProjVert *out;
    ProjVert *p;
    s32 i;
    s32 f;

    model = (WorldModel *)((u8 *)D_800C973C + D_800C973C[kind]);
    v = (SVECTOR *)((WorldModelQuad *)&model->tris[model->nTris] + model->nQuads);
    ApplyMatrixSV(m, pos, &ofs);
    if (kind == 0x10) {
        RotMatrixYXZ(rot, &mat);
    } else {
        RotMatrix(rot, &mat);
    }
    MulMatrix2(m, &mat);
    mat.t[0] = m->t[0] + ofs.vx;
    mat.t[1] = m->t[1] + ofs.vy;
    mat.t[2] = m->t[2] + ofs.vz;
    SetRotMatrix(&mat);
    SetTransMatrix(&mat);
    if (model->nVerts > 128) {
        p = out = buf;
    } else {
        p = out = (ProjVert *)getScratchAddr(0);
    }
    // The (u16) compares also reject negative screen coordinates. The x
    // compare yields PROJ_VERT_IN_X (1) directly.
    for (i = 0; i < model->nVerts; i += 3, v += 3, p += 3) {
        gte_ldv3c(v);
        gte_rtpt();
        if (i != 0) {
            f = (u16)p[-3].x < 320;
            if ((u16)p[-3].y < 240) f |= PROJ_VERT_IN_Y;
            p[-3].flags = f;
            f = (u16)p[-2].x < 320;
            if ((u16)p[-2].y < 240) f |= PROJ_VERT_IN_Y;
            p[-2].flags = f;
            f = (u16)p[-1].x < 320;
            if ((u16)p[-1].y < 240) f |= PROJ_VERT_IN_Y;
            p[-1].flags = f;
        }
        gte_stsxy3(&p[0].x, &p[1].x, &p[2].x);
        gte_stsz3(&p[0].z, &p[1].z, &p[2].z);
    }
    f = (u16)p[-3].x < 320;
    if ((u16)p[-3].y < 240) f |= PROJ_VERT_IN_Y;
    p[-3].flags = f;
    f = (u16)p[-2].x < 320;
    if ((u16)p[-2].y < 240) f |= PROJ_VERT_IN_Y;
    p[-2].flags = f;
    f = (u16)p[-1].x < 320;
    if ((u16)p[-1].y < 240) f |= PROJ_VERT_IN_Y;
    p[-1].flags = f;
    ctx->unk10 = func_800B1174(model, out, ctx->unk10, ctx->unk14);
    ctx->unk1C = func_800B13B8(model, out, ctx->unk1C, ctx->unk20);
    SetRotMatrix(m);
    SetTransMatrix(m);
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800B1174);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800B13B8);

void InitPlayerPosition(SceneState *st, Slot *slot, u8 *flags, VECTOR *pos) {
    SlotEntry *se;

    D_800C4D38 = st->cmd;
    if (D_80082C8C.mode == 2 || D_80082C8C.mode == 4 || D_80082C8C.mode == 6 ||
        (D_80082C8C.mode == 0 && D_80082C8C.unk02 == 0x3E)) {
        RestoreScenePlacement(D_800D226C, st->mode);
    } else if (flags[0] == 1) {
        func_800BC51C(&D_800DD6A8[0].parts[1].pos, pos);
    } else if (flags[0] == 2 || flags[0] == 3) {
        func_800BC51C(&D_800DD6A8[0].parts[2].pos, pos);
    } else if (D_800D23D8[0] == 4) {
        func_800BC51C(&D_800DD6A8[1].parts[2].pos, pos);
    } else if (st->mode == 0) {
        pos->vx = D_800D2120[D_80082C8C.unk02].x;
        pos->vy = D_800D2120[D_80082C8C.unk02].y;
        pos->vz = D_800D2120[D_80082C8C.unk02].z;
        D_800D2390.tail.vy = D_800D2120[D_80082C8C.unk02].rotX * 16;
        D_800C9770[1].vz = 0;
        D_800C9770[1].vx = 0;
        D_800C9770[1].vy = D_800D2120[D_80082C8C.unk02].rotY * 16;
    } else if (D_800C5C18 >= 0) {
        se = &D_800DBFB8[D_800C5C18];
        pos->vx = se->position.vx;
        pos->vy = -se->position.vz;
        pos->vz = se->position.vy;
    }
    SyncSlotsToCamera(flags, pos, D_800C9770);
    D_800C4D44 = func_800BD998(D_800C4D38);
    D_800C4D28 = slot->unk6C.bytes[2];
}

void SyncSlotsToCamera(u8 *flags, VECTOR *pos, SVECTOR *ang) {
    SlotEntry *slot;

    if (D_800C5C18 >= 0) {
        slot = &D_800DBFB8[D_800C5C18];
        func_800BC544(pos, &slot->position);
        slot->vec = ang[1];
    }
    if (D_800C5C1C >= 0) {
        if ((D_800C4D38 == 0x31) && (D_800C5BFC == 0)) {
            slot = &D_800DBFB8[D_800C5C1C];
            func_800BC544(pos, &slot->position);
            slot->vec = ang[1];
        }
    }
    if (D_800C5C20 >= 0) {
        if (D_800C5BFC == 0) {
            slot = &D_800DBFB8[D_800C5C20];
            func_800BC544(pos, &slot->position);
            slot->vec = ang[1];
        }
    }
    if (D_800C5C28 >= 0) {
        if ((D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) || D_800C4D38 == 0x84) {
            slot = &D_800DBFB8[D_800C5C28];
            func_800BC544(pos, &slot->position);
            slot->vec = ang[1];
        }
    }
    if (D_800C5C24 >= 0) {
        if (D_800C4D38 == 0x32) {
            slot = &D_800DBFB8[D_800C5C24];
            func_800BC544(pos, &slot->position);
            slot->vec = ang[1];
        }
    }
    if (D_800C5C2C >= 0) {
        if (D_800C4D38 == 0x30) {
            slot = &D_800DBFB8[D_800C5C2C];
            func_800BC544(pos, &slot->position);
            slot->vec = ang[1];
        }
    }
    if ((D_800C5C30 >= 0) && (D_800C4D38 == 0x30)) {
        slot = &D_800DBFB8[D_800C5C30];
        func_800BC544(pos, &slot->position);
        slot->vec = ang[1];
    }
}

s32 func_800B1BCC(u8 *p) {
    s32 ret;
    s32 side;
    s32 r;
    s32 sel;
    s32 kind;
    s32 msg;
    s32 res;

    ret = -1;
    if (D_800C4D38 >= 0x10 && D_800C4D38 <= 0x16) {
        if (p[0] == 3) {
            side = 0;
        } else if (p[0] == 4) {
            side = 1;
        } else {
            return -1;
        }
        r = func_800BD640((p + side)[2], &D_800DD6A8[side]);
        if (r >= 0) {
            if ((D_800D243F & 0x40) && r == 1) {
                PlacePlayerAtSpawn(p, r);
            } else {
                if (D_800DD6A8[side].unk1C > 0 && (D_800DD6A8[side].unk03 == 1 || D_800DD6A8[side].unk03 == 2)) {
                    func_8009B550(0, r == 0 ? 4 : r == 1 ? 5 : 6, 0, 1, 2, 1, 2);
                    D_800DD6A8[side].unk1C = -1;
                }
                ret = r;
                r = func_8009D864(0);
                if (r >= 0) {
                    func_8009D8A8(0);
                    if (r == 0) {
                        PlacePlayerAtSpawn(p, ret);
                    }
                    D_800DD6A8[side].unk1C = 0;
                }
            }
        }
    }
    if (((D_800C4D38 >= 0 && D_800C4D38 < 10) || D_800C4D38 == 0x80) && (p[0] == 0 || p[0] == 0xE)) {
        sel = func_800BE958();
        if (sel >= 0) {
            ret = sel;
            if (ret == func_800BD640(p[2], &D_800DD6A8[0])) {
                side = 0;
                kind = 3;
            } else if (ret == func_800BD640(p[3], &D_800DD6A8[1])) {
                side = 1;
                kind = 4;
            } else {
                return ret;
            }
            if (D_800DD6A8[side].unk1C > 0) {
                if (sel == 1) {
                    msg = 7;
                } else if (sel == 0) {
                    msg = 8;
                    if (D_800DD6A8[side].flag1E == -1) {
                        msg = 7;
                    }
                } else if (sel == 2) {
                    msg = 9;
                    if (D_800DD6A8[side].flag1E == -1) {
                        msg = 7;
                    }
                }
                func_8009B550(0, msg, 0, 1, 2, 1, 2);
                D_800DD6A8[side].unk1C = -1;
                D_800D23D8[0] = 0xE;
            } else {
                r = func_8009D864(0);
                if (r < 0) {
                    return ret;
                }
                func_8009D8A8(0);
                if (r == 0) {
                    if (func_800BD040(3000)) {
                        func_800BD058(3000);
                        func_800B20E4(p, side, kind, sel);
                    } else {
                        func_8009B358(9, 10, 0);
                        D_800D23D8[0] = 0;
                    }
                } else if (r == 1) {
                    D_800D23D8[0] = 0;
                }
                D_800DD6A8[side].unk1C = 0;
            }
        }
    } else if (D_800C4D38 == 0x32 && (p[0] == 0 || p[0] == 0xE)) {
        res = func_800BE958();
        if (res >= 0) {
            if (res == 3) {
                ret = 3;
            }
        }
    }
    return ret;
}

static void PlacePlayerAtSpawn(u8 *flags, s32 spawn) {
    u32 kind;
    s32 i;
    SVECTOR *rot;
    VECTOR unused; // never referenced; reserves the 16-byte stack area

    for (i = 0; i < D_800C5B50; i++) {
        kind = func_800B00D8(D_800DBFB8[i].marker);
        if (kind < 10 || kind == 0x80) {
            D_800C5C18 = i;
            break;
        }
    }
    flags[0] = 0;
    D_800C4D38 = kind;
    D_800C4D2C = 0x80000000;
    D_800C9868.vx = D_800CA034[spawn].x;
    D_800C9868.vy = D_800CA034[spawn].y;
    D_800C9868.vz = D_800CA034[spawn].z;
    rot = &D_800C9770[1];
    rot->vx = 0;
    rot->vy = 0;
    rot->vz = 0;
    SyncSlotsToCamera(flags, &D_800C9868, D_800C9770);
    D_800C9878 = 0;
}

static void func_800B20E4(u8 *flags, s32 actorIdx, s8 flag, s32 mode) {
    ActorRecord *actors;
    ActorRecord *rec;
    s32 code;
    s32 script;

    code = 0x10;
    *flags = flag;
    if (mode == 2) {
        code = 0x15;
    }
    D_800C4D38 = code;
    D_800C4D2C = 1;
    actors = D_800DD6A8;
    rec = &actors[actorIdx];
    func_800BC51C(&rec->parts[2].pos, &D_800C9868);
    if (mode == 1) {
        func_800B7240(0x41);
        D_800C987C = 0;
    } else if (mode == 0) {
        script = 0x41;
        if (rec->flag1E != -1) {
            script = 0x40;
        }
        func_800B7240(script);
        D_800C987C = func_800BE5F8(D_800C9878);
    } else if (mode == 2) {
        script = 0x42;
        if (rec->flag1E == -1) {
            script = 0x43;
        }
        func_800B7240(script);
        D_800C987C = func_800BE5F8(D_800C9878);
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800B21EC);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object6", func_800B28C8);

s32 func_800B2B6C(SlotEntry *slot, SlotEntry *target, s32 mode) {
    SVECTOR pts[WORLD_FAN_SPRITES];
    WorldSpriteRec rec;
    SVECTOR off;
    s16 a;
    s16 b;
    s16 size;
    s32 i;
    s32 angle;
    s32 kind;
    WorldSprite *s;

    if (D_800C4D38 != 0x32) {
        if (D_800C4D38 == 0x30 || (D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) || D_800C4D38 == 0x84) {
            size = 64;
        } else {
            size = 32;
        }
    } else {
        size = 256;
    }

    for (i = 0, s = rec.sprite; i < WORLD_FAN_SPRITES; i++, s++) {
        s->pos = slot->position;
        if (i == 0) {
        } else if (i == 1) {
            s->pos.vx -= size;
        } else if (i == 2) {
            s->pos.vz += size;
        } else if (i == 3) {
            s->pos.vx += size;
        } else {
            s->pos.vz -= size;
        }
        s->cellId = worldPosToCell(&s->pos, &s->cell);
    }

    angle = func_800A5DC8(D_800C9868.vx, D_800C9868.vy);
    for (i = 0, s = rec.sprite; i < WORLD_FAN_SPRITES; i++, s++) {
        func_800AC9F4(&off, angle, s->cellId);
        // i[pts] rather than pts[i]: only the index-first form gives the original addu operand order
        i[pts].vx = s->cell.vx + off.vx;
        i[pts].vy = s->cell.vy + off.vy;
        i[pts].vz = s->cell.vz + off.vz;
    }

    kind = func_800B5974(slot->marker, &a, &b, mode);
    if (target->unk13 == 1 && func_800B28C8(kind, pts, a, b, target, mode, 0, 0) != 0) {
        return 0;
    }
    return -1;
}

static s32 SlotOutlineOverlaps(SVECTOR *quad, SlotEntry *slot, SVECTOR *pts) {
    MATRIX m;
    SVECTOR out[5];
    SVECTOR rot;
    SVECTOR tmp;
    s32 i;

    memset(&tmp, 0, sizeof(tmp));
    tmp.vy = slot->vec.vy;
    rot = tmp;
    rot.vy += func_800BC5E0(slot->marker);
    RotMatrix(&rot, &m);
    gte_SetRotMatrix(&m);
    // gte_ldtr needs the (s32) widening to load the halfwords as the original does.
    gte_ldtr((s32)slot->hitPos.vx, 0, (s32)slot->hitPos.vz);
    out[0].vx = 0;
    out[0].vy = 0;
    out[0].vz = 0;
    gte_ldv0(&out[0]);
    gte_mvmva(1, 0, 0, 0, 0);
    gte_stsv(&out[0]);
    for (i = 0; i < 4; i++) {
        gte_ldv0(&pts[i]);
        gte_mvmva(1, 0, 0, 0, 0);
        gte_stsv(&out[i + 1]);
    }
    for (i = 0; i < 5; i++) {
        if (func_800B3ED0(&out[1], &quad[i]) != 0) {
            return 1;
        }
    }
    for (i = 0; i < 5; i++) {
        if (func_800B3ED0(&quad[1], &out[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 OutlineOverlaps(SVECTOR *quad, WorldHitXform *xf, SVECTOR *pts) {
    MATRIX m;
    SVECTOR out[5];
    SVECTOR rot;
    SVECTOR tmp;
    s32 i;

    memset(&tmp, 0, sizeof(tmp));
    tmp.vy = xf->rot.vy;
    rot = tmp;
    RotMatrix(&rot, &m);
    gte_SetRotMatrix(&m);
    // Same (s32) widening as in SlotOutlineOverlaps.
    gte_ldtr((s32)xf->trans.vx, 0, (s32)xf->trans.vz);
    out[0].vx = 0;
    out[0].vy = 0;
    out[0].vz = 0;
    gte_ldv0(&out[0]);
    gte_mvmva(1, 0, 0, 0, 0);
    gte_stsv(&out[0]);
    for (i = 0; i < 4; i++) {
        gte_ldv0(&pts[i]);
        gte_mvmva(1, 0, 0, 0, 0);
        gte_stsv(&out[i + 1]);
    }
    for (i = 0; i < 5; i++) {
        if (func_800B3ED0(&out[1], &quad[i]) != 0) {
            return 1;
        }
    }
    for (i = 0; i < 5; i++) {
        if (func_800B3ED0(&quad[1], &out[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

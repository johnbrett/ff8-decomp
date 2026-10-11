#include "common.h"
#include "psxsdk/libgte.h"
#include "world.h"
#include "world/we_object6.h"
#include "world/we_object7.h"
#include "world/we_object10.h"
#include "world/we_object3.h"
#include "world/we_object1.h"
#include "world/we_object4.h"
#include "world/we_object2.h"
#include "world/we_object5.h"
#include "world/we_object9.h"
#include "snd_init.h"

// Private prototypes
static KeyframeNode *FindKeyframeNode(KeyframeNode *list, s16 cached, s16 *out, ActorRecord *actor);
void func_800B6034(VECTOR *out, KeyframeNode *node, ActorRecord *recs);
void func_800B63C0(VECTOR *out, KeyframeNode *node, ActorRecord *recs);
void func_800B76F8(void);
s32 func_800B7C70(void);
static s32 func_800B816C(void);
static s32 func_800B8230(void);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B310C);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B33D8);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B368C);

/**
 * @brief Update screen-space projection and chained-target pitch/yaw for
 * each entry in @p obj.
 *
 * Two-pass: the first loop marks all entries as uninitialized (status and
 * @c unk30 set to -1). The second loop, for each entry, lazily resolves its
 * screen-space position via @c func_800B01A0; then if the entry chains to
 * a relative neighbour (@c targetIdx != 0) and is currently visible, it
 * also resolves the target's projection, computes the screen-space delta,
 * and stores pitch (atan2 of -dy / horizDist) and yaw (atan2 of -dz / dx
 * plus a 0x800 bias) back into the entry. View-space angles are computed
 * once at function entry from the global camera position vectors.
 *
 * @param obj Tracking object array header.
 */
void func_800B3868(TrackObj *obj) {
    TrackEntry *current;
    TrackEntry *target;
    s32 viewX;
    s32 viewY;
    SVECTOR diff;
    s32 horizDist;
    s32 i;

    viewX = func_800A5DC8(D_800D23C0.x, D_800D23C0.y);
    viewY = func_800A5DC8(D_800C9868.vx, D_800C9868.vy);

    SetRotMatrix(&D_800C9838);
    SetTransMatrix(&D_800C9838);

    for (i = 0, current = obj->entries; i < obj->count; i++, current++) {
        current->status = -1;
        current->unk30 = -1;
    }

    for (i = 0, current = obj->entries; i < obj->count; i++, current++) {
        if (current->status == -1) {
            current->status = func_800B01A0(viewY, viewX, &current->pos, &current->screen, &current->unk30, &current->unk2C);
        }
        if (current->targetIdx != 0 && current->status == 1) {
            target = current + current->targetIdx;
            if (target->status == -1) {
                target->status = func_800B01A0(viewY, viewX, &target->pos, &target->screen, &target->unk30, &target->unk2C);
            }
            diff.vx = target->screen.vx - current->screen.vx;
            diff.vy = target->screen.vy - current->screen.vy;
            diff.vz = target->screen.vz - current->screen.vz;
            current->unk18 = 0;
            horizDist = SquareRoot0(diff.vz * diff.vz + diff.vx * diff.vx);
            current->pitch = ratan2(-diff.vy, horizDist);
            current->yaw = ratan2(-diff.vz, diff.vx) + 0x800;
        }
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B3AB8);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B3ED0);


void SaveScenePlacement(Slot *slot, u8 mode) {
    VECTOR pos;
    VECTOR *p;
    SlotEntry *e;
    s32 i;
    u32 kind;
    s32 idx;
    u32 cmd;
    s32 range;
    u8 c;

    for (i = 0; i < D_800C5B50; i++) {
        e = &D_800DBFB8[i];
        kind = func_800B00D8(e->marker);
        idx = -1;
        if (kind < 10 || kind == 0x80) {
            idx = D_800C971C != 0;
        } else if (kind == 0x32) {
            idx = 2;
        } else if (kind == 0x31) {
            idx = D_800C971C != 0;
        } else if (kind == 0x30) {
            idx = 3;
        } else if (i == D_800C5C28) {
            idx = D_800C971C ? 5 : 4;
        }
        if (idx >= 0) {
            p = &pos;
            p->vx = e->position.vx;
            p->vy = -e->position.vz;
            p->vz = e->position.vy;
            slot->tracks[idx].trans_x = pos.vx;
            slot->tracks[idx].trans_z = pos.vy;
            slot->tracks[idx].trans_y = pos.vz;
            slot->tracks[idx].rot_y = e->vec.vy;
        }
    }
    cmd = D_800C4D38;
    idx = -1;
    if (cmd < 10 || cmd == 0x80) {
        idx = D_800C971C != 0;
    } else if (cmd == 0x32) {
        idx = 2;
    } else if (cmd == 0x31) {
        idx = D_800C971C != 0;
    } else if (cmd == 0x30) {
        idx = 3;
    } else if ((cmd >= 0x20 && cmd <= 0x28) || cmd == 0x84) {
        idx = D_800C971C ? 5 : 4;
    }
    if (idx >= 0) {
        slot->tracks[idx].trans_x = D_800C9868.vx;
        slot->tracks[idx].trans_z = D_800C9868.vy;
        slot->tracks[idx].trans_y = D_800C9868.vz;
        slot->tracks[idx].rot_y = D_800C9770[1].vy;
    }
    slot->unk60 = D_800D2390.tail.vy;
    if ((D_800C4D38 >= 0 && D_800C4D38 < 10) || D_800C4D38 == 0x80 || (D_800C4D38 >= 0x10 && D_800C4D38 <= 0x16) || (D_800C4D38 >= 0x40 && D_800C4D38 <= 0x42) || D_800C4D38 == 0x31
        || (D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) || D_800C4D38 == 0x84 || D_800C4D38 == 0x32 || D_800C4D38 == 0x30) {
        slot->unk6C.bytes[0] = D_800C4D3C;
    }
    slot->unk6C.bytes[2] = D_800C4D28 == MAP_DISPLAY_FULL ? MAP_DISPLAY_OFF : D_800C4D28;
    c = D_800C4D38;
    *(u8 *)&slot->scene.unk02 = 0xFF; // stored as u8: an s8 store lets gcc reuse the -1 below
    *(u8 *)&slot->scene.unk03 = 0xFF;
    slot->scene.cmd = c;
    if (mode == 1) {
        range = D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28;
        if (range || D_800C4D38 == 0x84) {
            if (D_800C971C != 0) {
                if (range || D_800C4D38 == 0x84) {
                    slot->kind[1] = -1;
                }
            } else {
                if (range || D_800C4D38 == 0x84) {
                    slot->kind[0] = -1;
                }
            }
        }
    }
    g_gameState.unk004 = D_800D228C[func_800A5E40(D_800C9868.vx, D_800C9868.vy)];
}

void RestoreScenePlacement(Slot *spawn, u8 mode) {
    s32 idx;
    Track *track;
    s32 y;

    idx = -1;
    if (D_800C971C != 0) {
        if ((D_800C4D38 >= 0 && D_800C4D38 < 10) || D_800C4D38 == 0x80) {
            idx = 1;
        } else if (D_800C4D38 == 0x32) {
            idx = 2;
        } else if (D_800C4D38 == 0x30) {
            idx = 3;
        } else if ((D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) || D_800C4D38 == 0x84) {
            idx = 5;
        } else if (D_800C4D38 == 0x31) {
            idx = 1;
        }
    } else {
        if ((D_800C4D38 >= 0 && D_800C4D38 < 10) || D_800C4D38 == 0x80) {
            idx = 0;
        } else if (D_800C4D38 == 0x32) {
            idx = 2;
        } else if (D_800C4D38 == 0x30) {
            idx = 3;
        } else if ((D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) || D_800C4D38 == 0x84) {
            idx = 4;
        } else if (D_800C4D38 == 0x31) {
            idx = 0;
        }
    }

    if (idx >= 0) {
        track = &spawn->tracks[idx];
        D_800C9868.vx = track->trans_x;
        D_800C9868.vy = track->trans_z;
        y = track->trans_y;
        D_800C9770[1].vz = 0;
        D_800C9770[1].vx = 0;
        D_800C9868.vz = y;
        D_800C9770[1].vy = track->rot_y;
        D_800D2390.tail.vy = spawn->unk60;
    }

    if ((D_800C4D38 >= 0 && D_800C4D38 < 10) || D_800C4D38 == 0x80 ||
        (D_800C4D38 >= 0x10 && D_800C4D38 <= 0x16) || (D_800C4D38 >= 0x40 && D_800C4D38 <= 0x42) ||
        D_800C4D38 == 0x31 || (D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) ||
        D_800C4D38 == 0x84 || D_800C4D38 == 0x32 || D_800C4D38 == 0x30) {
        D_800C4D3C = spawn->unk6C.bytes[0];
    } else {
        D_800C4D3C = 0;
    }
    D_800C4D28 = spawn->unk6C.bytes[2];
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B454C);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B4AA0);


void func_800B56A0(void) {
    func_800BD180();
    if (D_800D23D8[0] == 5) {
        if (func_800B7C70() == 0) {
            return;
        }
        D_800C4D38 = D_800DCAF8;
        func_800A40C0();
        D_800C4D3C = D_800D226C->unk6C.bytes[0];
        D_800C9868.vx = D_800DCAE8.vx;
        D_800C9868.vy = -D_800DCAE8.vz;
        D_800C9868.vz = D_800DCAE8.vy;
        worldPosToCell(&D_800DCAE8, D_800C9770);
        SyncSlotsToCamera(D_800D23D8, &D_800C9868, D_800C9770);
    } else if (D_800D23D8[0] == 6) {
        func_800B76F8();
        return;
    } else if (D_800D23D8[0] == 7) {
        if (func_800B816C() == 0) {
            return;
        }
        D_800C4D38 = D_800DCAF8;
        func_800A40C0();
        D_800C9868.vx = D_800DCAE8.vx;
        D_800C9868.vy = -D_800DCAE8.vz;
        D_800C9868.vz = D_800DCAE8.vy;
        worldPosToCell(&D_800DCAE8, D_800C9770);
        SyncSlotsToCamera(D_800D23D8, &D_800C9868, D_800C9770);
    } else if (D_800D23D8[0] == 8) {
        if (func_800B8230() == 0) {
            return;
        }
        D_800C4D38 = D_800DCAF8;
        if (D_800C4D38 == 0x32) {
            D_800C4D2C = 0x80000000;
            D_800C9770[1] = D_800DBFB8[D_800C5C24].vec;
            D_800D23D8[0] = 6;
            D_800C4D88 = pickAudioTransition(0x32, D_800D23D8[0x6A]);
            if (D_800C4D88 >= 0) {
                sndCmdC1(0, 0x1E, 0);
            }
        } else if ((D_800C4D38 >= 0x20 && D_800C4D38 <= 0x28) || D_800C4D38 == 0x84) {
            D_800C4D44 = 0x20;
            D_800C9770[1] = D_800DBFB8[D_800C5C28].vec;
        }
        D_800C4D3C = 0;
        func_800A40C0();
        D_800C9868.vx = D_800DCAE8.vx;
        D_800C9868.vy = -D_800DCAE8.vz;
        D_800C9868.vz = D_800DCAE8.vy;
        worldPosToCell(&D_800DCAE8, D_800C9770);
        SyncSlotsToCamera(D_800D23D8, &D_800C9868, D_800C9770);
    } else {
        func_8009F6EC();
        return;
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B5974);

// Returns the layout kind (1-4), or 0 for an unknown kind. Every known kind writes
// all four corners of out.
s32 GetFootprintCorners(s32 id, SVECTOR *out, u16 *param, s32 margin) {
    u16 *e;
    s32 layout;
    s32 kind;
    s16 x;
    s16 y;
    s16 x2;

    // Entry (id - 0x40); written this way because (id - 0x40) * 4 does not match.
    if (id >= 0x40) {
        e = &D_800C5C44[id * 4 - 0x100];
    } else if (id == 1) {
        e = &D_800C5C44[0x80]; // entry 0x20, the first fixed entry
    } else {
        e = &D_800C5C44[0x84]; // entry 0x21
    }

    // The table is u16, but the kind and the halved sizes are read signed.
    kind = (s16)e[3];
    if (kind == 1) {
        layout = 1;
        x = ((s16)e[0] >> 1) + margin;
        y = ((s16)e[1] >> 1) + margin;
        out[0].vx = out[3].vx = -x;
        out[1].vx = out[2].vx = x;
        out[0].vz = out[1].vz = y;
        out[2].vz = out[3].vz = -y;
    } else if (kind == 2) {
        layout = 2;
        x = e[0] + margin;
        y = ((s16)e[1] >> 1) + margin;
        out[0].vx = out[3].vx = -x;
        out[1].vx = out[2].vx = -margin;
        out[0].vz = out[1].vz = y;
        out[2].vz = out[3].vz = -y;
    } else if (kind == 3) {
        layout = 3;
        x = (s16)e[0] >> 1;
        x2 = margin + (x >> 1);
        x += margin;
        y = ((s16)e[1] >> 1) + margin;
        out[0].vx = -x2;
        out[3].vx = x2;
        out[1].vx = -x;
        out[2].vx = x;
        out[0].vz = out[3].vz = -y;
        out[1].vz = out[2].vz = y;
    } else if (kind == 4) {
        layout = 4;
        x = ((s16)e[0] >> 1) + margin;
        y = ((s16)e[1] >> 1) + margin;
        out[0].vx = out[3].vx = -x;
        out[1].vx = out[2].vx = x;
        out[0].vz = out[1].vz = y;
        out[2].vz = out[3].vz = -y;
    } else {
        return 0;
    }
    out[0].vy = out[1].vy = out[2].vy = out[3].vy = 0;
    if (param != NULL) {
        *param = e[2];
    }
    return layout;
}


void UpdateKeyframeCamera(KeyframeNode *list, s16 count, MATRIX *outMat, SVECTOR *outAngles,
                   SVECTOR *rotBuf, SVECTOR *offsetOut, ActorRecord *recs) {
    VECTOR cur;
    MATRIX m;
    SVECTOR angles;
    SVECTOR offset;
    SVECTOR rot;
    VECTOR next;
    s16 frac;
    KeyframeNode *node;
    s32 yaw;

    node = FindKeyframeNode(list, count, &frac, recs);
    if (count == 0 || D_800C5D58 != node) {
        func_800ACA70(&D_800DCB28, outMat);
        func_800ACBD0(&D_800DCB38, rotBuf);
        if (count == 0) {
            D_800DCB08 = D_800DCB28;
            D_800DCB18 = D_800DCB38;
        }
    }
    yaw = func_800A5DC8(D_800C9868.vx, D_800C9868.vy);

    func_800B6034(&cur, node, recs);
    if (node->blend == 1) {
        func_800B6034(&next, node + 1, recs);
        func_800BE4D8(&next, &cur, frac, &D_800DD670);
    } else if (node->blend == 2) {
        D_800DD670 = cur;
    } else if (node->blend == 3) {
        func_800BE4D8(&cur, &D_800DCB28, frac, &D_800DD670);
    }

    func_800B63C0(&cur, node, recs);
    if (node->blend == 1) {
        func_800B63C0(&next, node + 1, recs);
        func_800BE4D8(&next, &cur, frac, &D_800DD658);
    } else if (node->blend == 2) {
        D_800DD658 = cur;
    } else if (node->blend == 3) {
        func_800BE4D8(&cur, &D_800DCB38, frac, &D_800DD658);
    }

    func_800AC778(&D_800DD670, &D_800DD658, yaw, &m, &angles, &offset, &rot);
    if (outMat != NULL) {
        *outMat = m;
    }
    if (outAngles != NULL) {
        *outAngles = angles;
    }
    if (offsetOut != NULL) {
        *offsetOut = offset;
    }
    if (rotBuf != NULL) {
        *rotBuf = rot;
    }
    D_800C5D58 = node;
    D_800DCB08 = D_800DD670;
    D_800DCB18 = D_800DD658;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B6034);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B63C0);

// The early return for mode 0xFF is what produces the original copy of dir.
static inline s32 GetKeyframeDirection(ActorRecord *actor) {
    u8 mode;
    s32 dir;

    mode = D_800D23D8[(actor - D_800DD6A8) + 2];
    dir = -1;
    if (mode == 0xFF) {
        return dir;
    }
    if (mode == 0) {
        if (actor->unk03 == 1 || actor->unk03 == 2) {
            if (actor->unk1F == 1) {
                dir = 0;
            } else if (actor->flag1E == dir) {
                if (actor->unk1F == 0) {
                    dir = 1;
                }
            }
        }
    } else if (mode == 1) {
        if (actor->unk03 == 1 || actor->unk03 == 2) {
            if (actor->unk1F == 1) {
                dir = 2;
            }
        }
    }
    return dir;
}

static KeyframeNode *FindKeyframeNode(KeyframeNode *list, s16 cached, s16 *out, ActorRecord *actor) {
    s32 dir;
    s16 prev;

    dir = GetKeyframeDirection(actor);
    if (dir >= 0 && dir != 1) {
        while (list->time != -1 && list->time != -2) {
            list++;
        }
        if (out != NULL) {
            *out = 0x1000;
        }
        if (list->time == -2) {
            D_800C987C = list[1].time - 1;
        }
    } else {
        prev = 0;
        while (list->time != -1) {
            if (list->time != -2 && cached - list->time <= 0) {
                break;
            }
            prev = list->time;
            list++;
        }
        if (out != NULL) {
            if (list->time == -1) {
                *out = 0x1000;
            } else {
                *out = ((cached - prev) << 12) / (list->time - prev);
                *out = (*out < 0) ? 0 : (*out > 0x1000) ? 0x1000 : *out;
            }
        }
    }
    return list;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B6968);

/**
 * @brief Compute a layout offset for an actor based on a 1..4 step counter.
 *
 * Looks up the actor's pair-of-mode-keys from @c D_800C5984 (indexed by
 * @c D_800D23D8[idx+2] * 2). Each key indexes into @c D_800C5C44 (stride
 * 4 u16s = 8 bytes) to retrieve a halfword that is biased by 0x80. The
 * resulting two values @p a and @p b are accumulated into a step-dependent
 * sum: +a@@1, +b@@2, +0x10+b@@3, +0x10+a@@4.
 *
 * @param idx Actor index into @c D_800DD6A8.
 * @param count Step counter (1..4); negative/zero returns 0.
 * @return Accumulated layout offset in pixels.
 */
s32 func_800B7080(s32 idx, s32 count) {
    s32 i = idx;
    ActorRecord *e;
    u16 *cmds;
    u8 *pairs;
    u8 *modes;
    u8 *pair;
    s32 a, b;
    s32 result;
    s32 one = 1;
    s32 four = 4;

    e = &D_800DD6A8[i];
    if (e->flag1E != -1) {
        count = e->partCount - (count + one);
    }

    cmds  = D_800C5C44;
    pairs = D_800C5984;
    modes = D_800D23D8;

    pair = &pairs[modes[i + 2] * 2];
    a = (s32)cmds[(pair[0] - 0x40) * four] - 0x80;
    b = (s32)cmds[(pair[1] - 0x40) * four] - 0x80;

    result = 0;
    if (count > 0) {
        result = (s16)a + 0x10;
    }
    if (count >= 2) {
        result += (s16)b;
    }
    if (count >= 3) {
        result += 0x10 + (s16)b;
    }
    if (count >= 4) {
        result += 0x10 + (s16)a;
    }
    return result;
}

/** @brief Reset 23 global state variables for the field engine. */
void func_800B7178(void) {
    D_800C5B50 = 0;
    D_800C5B54 = 0;
    D_800C5B58 = 4;
    D_800C5C18 = -1;
    D_800C5C1C = -1;
    D_800C5C20 = -1;
    D_800C5C24 = -1;
    D_800C5C28 = -1;
    D_800C5C2C = -1;
    D_800C5C30 = -1;
    D_800C5C38 = 0;
    D_800C5C3C = 0;
    D_800C5C40 = 0;
    D_800C5D54 = 0;
    D_800C5924 = 0;
    D_800C5BFC = 0;
    D_800C4D98 = 0;
    D_800C4D70 = 0;
    D_800C4D9C = 0;
    D_800C97A4 = -1;
    D_800C4DC0 = 0;
    D_800C4DC4 = 1;
    D_800C4DC8 = 0;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B7240);

// The points table is indexed by part position; one is a variable for the same reason as in func_800BE720.
void func_800B73A4(ActorRecord *group) {
    SVECTOR d;
    VECTOR sq;
    VECTOR *pts;
    ActorPart *entry;
    s8 dir;
    s32 i;
    s32 a;
    s32 b;
    s32 len;

    pts = group->points;
    dir = group->flag1E;
    entry = group->parts;
    for (i = 0; i < group->partCount; i++, entry++) {
        if (dir == 1) {
            b = entry->prevHalf;
        } else {
            s32 one = 1;
            b = group->span - (entry->prevHalf + one);
        }
        a = b + dir;
        d.vx = pts[a].vx - pts[b].vx;
        d.vy = pts[a].vy - pts[b].vy;
        d.vz = pts[a].vz - pts[b].vz;
        gte_ldsv(&d);
        gte_SQR(0);
        gte_stlvnl(&sq);
        len = SquareRoot0(sq.vx + sq.vy + sq.vz);
        entry->prevWord = entry->currWord = len - entry->prevWord;
        entry->prevHalf = entry->currHalf = group->span - entry->prevHalf - 2;
        group->unk1F = group->slotCount - group->unk1F;
    }
    group->flag1E = -group->flag1E;
}

void func_800B7530(ActorRecord *group) {
    ActorPart *entry;
    ActorPart *best;
    s32 maxWord;
    s32 maxHalf;
    s32 i;
    s32 half;

    maxWord = 0;
    maxHalf = 0;
    best = group->parts;
    i = 0;
    entry = best;
    for (; i < group->partCount; i++, entry++) {
        if (maxHalf < entry->prevHalf) {
            maxHalf = entry->prevHalf;
            maxWord = entry->prevWord;
            best = entry;
        } else if (maxHalf == entry->prevHalf) {
            if (maxWord < entry->prevWord) {
                maxWord = entry->prevWord;
                best = entry;
            }
        }
    }

    {
        s32 word = 0;
        half = best->prevHalf;
        entry = group->parts;
        for (i = 0; i < group->partCount; i++, entry++) {
            entry->prevHalf = half;
            entry->prevWord = word;
        }
    }

    entry = group->parts;
    for (i = 0; i < group->partCount; i++, entry++) {
        entry->prevWord += func_800B7080(group - D_800DD6A8, i);
        func_800AEB58(entry, group);
    }

    entry = group->parts;
    for (i = 0; i < group->partCount; i++, entry++) {
        entry->currHalf = entry->prevHalf;
        entry->currWord = entry->prevWord;
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B76F8);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B7C70);

static s32 func_800B816C(void) {
    s32 done;
    s32 val;
    s32 clamped;
    s32 *scroll;

    done = 0;
    if (D_800C4D2C < 0) {
        D_800C4D2C = 4;
        D_800DCB48 = 0;
        D_800C4D40 = 0;
        D_800C4D44 = 0x10;
        D_800C5C04 = 4;
        D_800C4D2C = 0;
        D_800C4D58 = 0;
    }

    scroll = &D_800C4D58;
    val = *scroll + 12;
    *scroll = val;
    if (val >= 0) {
        clamped = 799;
        if (val < 800) {
            clamped = val;
        }
    } else {
        clamped = 0;
    }
    *scroll = clamped;

    D_800DCB48++;
    if (D_800DCB48 >= 64) {
        done = 1;
        D_800C4D2C = 0;
        D_800D23D8[0] = 0;
        D_800C5C04 = 0;
        D_800C4D58 = 0;
    }
    return done;
}

static s32 func_800B8230(void) {
    s32 done;
    SlotEntry *slots;
    SlotEntry *slot;
    s32 timer;
    s32 step;

    done = 0;
    if (D_800C4D2C < 0) {
        D_800C4D2C = 4;
        D_800DCB48 = 0;
        D_800C4D40 = 0;
        D_800C4D44 = 0x10;
        D_800C4D2C = 0;
        D_800DCB4C = (D_800C97F4 - D_800C9868.vz) / 30;
    }

    slots = D_800DBFB8;
    slot = slots + D_800C5C2C;
    step = D_800DCB4C;
    timer = D_800DCB48 + 1;
    D_800DCB48 = timer;
    slot->position.vy += step;
    if (timer >= 31) {
        done = 1;
        D_800D23D8[0] = 0;
        D_800C5C04 = 0;
        D_800C4D2C = 0;
        D_800C4D58 = 0;
    }

    D_800C9868.vx = slot->position.vx;
    D_800C9868.vy = -slot->position.vz;
    D_800C9868.vz = slot->position.vy;
    worldPosToCell(&slot->position, D_800C9770);
    D_800C9770[1] = (slots + D_800C5C2C)->vec;
    return done;
}


static inline s32 FindSlotByMarker(s32 marker) {
    s32 i;

    for (i = 0; i < D_800C5B50; i++) {
        if (marker == D_800DBFB8[i].marker) {
            return i;
        }
    }
    return -1;
}

void PlaceRequestedObjects(u8 *flags) {
    WorldPlacement *tbl;
    SlotEntry *slot;
    s32 i;
    s32 id;
    s32 idx;

    tbl = D_800C96FC;
    for (i = 0; i < 2; i++) {
        id = flags[i + 0x6B];
        if (id == 0) {
            continue;
        }
        func_8009D840(i);
        if (tbl[id].kind == 0x30) {
            idx = FindSlotByMarker(0x40);
            slot = &D_800DBFB8[idx];
            slot->position.vx = tbl[id].x;
            slot->position.vy = tbl[id].y;
            slot->position.vz = tbl[id].z;
            slot->vec.vy = tbl[id].rotY;
            idx = FindSlotByMarker(0x41);
            slot = &D_800DBFB8[idx];
            slot->position.vx = tbl[id].x;
            slot->position.vy = tbl[id].y;
            slot->position.vz = tbl[id].z;
            slot->vec.vy = tbl[id].rotY;
        } else {
            idx = FindSlotByMarker(func_800B0010(tbl[id].kind));
            slot = &D_800DBFB8[idx];
            slot->position.vx = tbl[id].x;
            slot->position.vy = tbl[id].y;
            slot->position.vz = tbl[id].z;
            slot->vec.vy = tbl[id].rotY;
        }
    }
}

/**
 * @brief Walk the cmd-stream at @c D_800C96C8 (variant for object slot 1).
 *
 * Mirrors @c func_800BC46C but with a richer opcode set: in addition to
 * end / link / store, dispatches a number of side-effect opcodes (call
 * wrappers, bit ops on the @c D_800D226C slot, scene/inventory pokes).
 *
 * @param out  Output halfword captured by 0xFF08 (returns 1) or 0xFF2B (returns 3).
 * @return     1 if 0xFF08 fired, 3 if 0xFF2B fired, 0 otherwise.
 */
s32 func_800B85DC(s16 *out) {
    ScriptOp *op;
    s32 result;

    result = 0;
    op = func_800AF004(D_800C96C8, 1);

    if (op != 0) {
        while (1) {
            if (op->op == 0xFF05) break;

            if (op->op == 0xFF0E) {
                op = (ScriptOp *)&D_800C96C8[op->param];
                continue;
            } else if (op->op == 0xFF08) {
                *out = op->param;
                result = 1;
                break;
            } else if (op->op == 0xFF2B) {
                *out = op->param;
                result = 3;
                break;
            } else if (op->op == 0xFF1F) {
                s8 lo = op->param;
                u8 hi = op->param >> 8;
                func_8009B358(lo, hi, 0);
            } else if (op->op == 0xFF26) {
                D_800D23D8[0] = (u8)op->param;
            } else if (op->op == 0xFF28) {
                u8 enable = op->param >> 8;
                s8 bitPos = op->param;
                if (enable) {
                    SET_FLAG(D_800D226C->flags, bitPos);
                } else {
                    CLEAR_FLAG(D_800D226C->flags, bitPos);
                }
            } else if (op->op == 0xFF23) {
                s8 lo = op->param;
                s8 hi = op->param >> 8;
                func_8009B550(lo, hi, 0, 1, 2, 1, 2);
            } else if (op->op == 0xFF2E) {
                u8 byteIdx = op->param;
                u8 byteVal = op->param >> 8;
                if (byteIdx < 2) {
                    D_800D226C->bytes[(s8)byteIdx] = byteVal;
                }
            } else if (op->op == 0xFF24) {
                func_8009D8A8(op->param);
            } else if (op->op == 0xFF36) {
                D_800C4DBC = 1;
            } else if (op->op == 0xFF37) {
                s8 lo = op->param;
                u8 hi = op->param >> 8;
                addItemToInventory(lo, hi);
            }
            op++;
        }
    }
    return result;
}

void ResetPositionHistory(void) {
    WorldTrailPoint point;
    WorldTrailPoint *p; // the position fields are written through a pointer; direct stores do not match
    GlyphQuery q;
    VECTOR unused; // never used, but the compiled code only matches the original with it
    s32 i;
    s32 type;

    p = &point;
    D_800DCAB8 = 3;
    D_800DCAB9 = 0;
    p->x = D_800C9868.vx;
    p->y = D_800C9868.vz;
    p->z = -D_800C9868.vy;
    D_800DCAD8 = 0;
    point.angle = D_800C9770[1].vy;
    D_800DCABA = -1;
    q.pos.vx = point.x;
    q.pos.vy = point.y;
    q.pos.vz = point.z;
    q.buf.angle = worldPosToCell(&q.pos, &q.buf.proj);
    type = glyphAt(&q, NULL)->type;
    point.onLand = type < 6;
    for (i = 0; i < 16; i++) {
        D_800DC9B8[i] = point;
    }
    D_800DCAC8 = point;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object7", func_800B893C);



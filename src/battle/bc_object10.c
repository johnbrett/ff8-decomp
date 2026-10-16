#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object10.h"
#include "battle/bc_object13.h"
#include "battle/bc_object14.h"

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 active;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ void (*finish)(s32 index);
    /* 0x08 */ s16 slotIndex;
} BattleActionState;

typedef struct BattleActionTask {
    /* 0x00 */ u8 unk00[12];
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 state;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ BattleActionState *action;
} BattleActionTask;

typedef struct {
    /* 0x00 */ u8 unk00[12];
    /* 0x0C */ s16 frame;
    /* 0x0E */ s16 duration;
} BattleTintFadeTask;

typedef struct {
    /* 0x00 */ SVECTOR rotation;
    /* 0x08 */ SVECTOR eye;
    /* 0x10 */ SVECTOR target;
    /* 0x18 */ MATRIX matrix;
} BattleCameraWorkspace;

typedef struct {
    /* 0x00 */ s8 active;
    /* 0x01 */ u8 unk01[11];
    /* 0x0C */ s16 frame;
    /* 0x0E */ s16 duration;
    /* 0x10 */ s16 *data;
    /* 0x14 */ u8 unk14[1296];
} BattleCameraTaskData;

#define BATTLE_SLOT_COUNT 11
typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 active;
    /* 0x02 */ u8 unk2[50];
} BattleSlot;

typedef struct BattleListNode {
    /* 0x00 */ struct BattleListNode *next;
    /* 0x04 */ s32 value;
} BattleListNode;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 active;
    /* 0x02 */ u8 unk2[10];
} BattleListEntry;

typedef struct {
    /* 0x00 */ BattleListNode *pool;
    /* 0x04 */ BattleListNode *head;
    /* 0x08 */ BattleListEntry *entries;
    /* 0x0C */ s16 count;
    /* 0x0E */ s16 unkE;
} BattleList;

extern u8 D_800F0278[];
extern u8 D_800EF7F8[];
extern BattleCameraTaskData D_800EF828[2];
extern BattleCameraTaskData *D_800F0288;
extern s16 D_800F1A1C;
extern u8 D_800F1A24;
extern u8 D_800F1A2C;
extern u8 D_800F02EC;

extern SVECTOR D_800F02C0;
extern s32 D_800F02F0;
extern SVECTOR D_800E3D70;
extern SVECTOR D_800E3D78;

extern u8 D_800E3D2C[16];
extern u8 D_800E3D3C[32];
extern s16 D_800F0290[8];
extern u16 D_800F02F4;
extern u16 D_800F02E8;

extern u8 D_800EF72C[];
extern u8 D_800F05C8[];

extern u8 D_800F02F8[];
extern u8 D_800F0308[];
extern u8 D_800F0408[];
extern u8 D_800F0578[];
extern u8 D_800F082C[];
extern u8 D_800F085C[];
extern u8 D_800F0830[];
extern u8 D_800F1668[];
extern u8 D_800E3DA8[];
extern BattleSlot D_800F05F0[BATTLE_SLOT_COUNT];
extern u8 D_800F0854[];
extern u8 D_80170000[];

static s32 CompleteBattleAction(BattleActionTask *task);
static s32 FadeBattleTintOut(BattleTintFadeTask *task);
s32 func_800B53F8(SVECTOR *eye, SVECTOR *target, MATRIX *matrix);
static u32 RemapBattleStatusFlags(u16 persistent, u32 transient);
static void BuildBattleCurveTangents(s16 *knots, s16 *values, float *tangents, s32 count);
static s32 InterpolateBattleCurve(s16 value, s16 *knots, s16 *values, float *tangents, s32 count);
BattleListEntry *func_800B8944(BattleListNode *pool, BattleListNode **head, BattleListEntry *entry);
static BattleSlot *FindFreeBattleSlot(void);
static BattleListEntry *FindFreeBattleListEntry(BattleList *list);
static void RotateLinkedList(BattleListNode *pool, BattleListNode **head);


void func_800B5B48(void);
void func_800B8314(void);
s32 func_8013E000(s32);
void func_800C2B88(u8 *);

static s32 CompleteBattleAction(BattleActionTask *task) {
    BattleActionState *action = task->action;
    BattleEffectSlot *slot = &D_800EF2D0[action->slotIndex];

    if (slot->flags & BATTLE_SLOT_FLAG_UNK02) {
        if (func_800C5A34(slot, 26, 0x40) != 0) {
            return 0;
        }
    }
    if (action->finish != NULL) {
        action->finish(action->slotIndex);
    }
    action->active = 255;
    return 2;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B4A74);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B4BAC);

/**
 * @brief Set or clear a bit in an entity's flags word and update state.
 *
 * Takes the entity at D_800EF2D0[a0]. Creates a bitmask
 * from 1 << a1. Loads the word at entity+8, clears the bit. If a2 is
 * nonzero, sets the bit instead. Calls func_800B5C10 to update the
 * entity, then func_800B56B8 to finalize.
 *
 * @param a0 Entity index into D_800EF2D0.
 * @param a1 Bit position to modify.
 * @param a2 If nonzero, set the bit; if zero, clear it.
 */
void func_800B4DE8(s32 a0, s32 a1, s32 a2) {
    u8 *entity = (u8 *)&D_800EF2D0[a0];
    s32 mask = 1 << a1;
    s32 flags = *(s32 *)(entity + 8) & ~mask;
    if (a2 != 0) {
        flags |= mask;
    }
    func_800B5C10(entity, flags);
    func_800B56B8(entity);
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B4E54);

s32 BuildBattleDirectionBasis(VECTOR *input, MATRIX *matrix) {
    VECTOR horizontal;
    VECTOR vertical;
    VECTOR direction;
    s32 scale = 1;

    direction.vx = input->vx;
    direction.vy = input->vy;
    direction.vz = input->vz;
    while ((direction.vx < 0 ? -direction.vx : direction.vx) > 10000 ||
           (direction.vy < 0 ? -direction.vy : direction.vy) > 10000 ||
           (direction.vz < 0 ? -direction.vz : direction.vz) > 10000) {
        scale *= 2;
        direction.vx = (direction.vx & 1) + direction.vx / 2;
        direction.vy = (direction.vy & 1) + direction.vy / 2;
        direction.vz = (direction.vz & 1) + direction.vz / 2;
    }
    scale *= SquareRoot0(VectorNormal(&direction, &direction));
    horizontal.vx = direction.vz;
    horizontal.vy = 0;
    horizontal.vz = -direction.vx;
    VectorNormal(&horizontal, &horizontal);
    OuterProduct12(&direction, &horizontal, &vertical);
    VectorNormal(&vertical, &vertical);
    matrix->m[0][0] = horizontal.vx;
    matrix->m[0][1] = horizontal.vy;
    matrix->m[0][2] = horizontal.vz;
    matrix->m[1][0] = vertical.vx;
    matrix->m[1][1] = vertical.vy;
    matrix->m[1][2] = vertical.vz;
    matrix->m[2][0] = direction.vx;
    matrix->m[2][1] = direction.vy;
    matrix->m[2][2] = direction.vz;
    return scale;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B53F8);

/**
 * @brief Compute 3D vector differences and initialize transformation data.
 *
 * Computes differences of 3 words at offsets 0x14, 0x18, 0x1C between
 * a1 and a0, stores them in a2 at the same offsets. Then calls three
 * transformation functions to finalize the setup.
 *
 * @param a0 Source position data.
 * @param a1 Target position data.
 * @param a2 Output delta structure.
 */
void func_800B54A0(s32 a0, s32 a1, s32 a2) {
    s32 dst = a2;
    *(s32 *)(dst + 0x14) = *(s32 *)(a1 + 0x14) - *(s32 *)(a0 + 0x14);
    *(s32 *)(dst + 0x18) = *(s32 *)(a1 + 0x18) - *(s32 *)(a0 + 0x18);
    *(s32 *)(dst + 0x1C) = *(s32 *)(a1 + 0x1C) - *(s32 *)(a0 + 0x1C);
    TransposeMatrix((MATRIX *)a0, (MATRIX *)dst);
    ApplyMatrixLV((MATRIX *)dst, (VECTOR *)(dst + 0x14), (VECTOR *)(dst + 0x14));
    MulMatrix((MATRIX *)dst, (MATRIX *)a1);
}

/**
 * @brief Compute coordinate differences and call ratan2.
 *
 * @param a0 Pointer to first coordinate pair (s16 x at +0, s16 y at +4).
 * @param a1 Pointer to second coordinate pair (s16 x at +0, s16 y at +4).
 * @return Result of ratan2(dx, dy).
 */
s32 func_800B5528(s32 a0, s32 a1) {
    s32 dx = *(s16 *)a0 - *(s16 *)a1;
    s32 dy = *(s16 *)(a0 + 4) - *(s16 *)(a1 + 4);
    return ratan2(dx, dy);
}

static u32 RemapBattleStatusFlags(u16 persistent, u32 transient) {
    u32 result = 0;
    s32 i;

    for (i = 0; i < 16; i++) {
        if ((persistent >> i) & 1) {
            if (D_800E3D2C[i] != 255) {
                result |= 1U << D_800E3D2C[i];
            }
        }
    }
    for (i = 0; i < 32; i++) {
        if (transient & (1U << i)) {
            if (D_800E3D3C[i] != 255) {
                result |= 1U << D_800E3D3C[i];
            }
        }
    }
    return result;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B5604);

/**
 * @brief Update entity render state based on computed attribute.
 *
 * If entity byte at offset 4 is >= 16, returns immediately. Otherwise
 * calls func_800B5604 to compute the current attribute. Loads the
 * entity's render pointer at offset 0x74 and compares byte[3] and
 * byte[0] against the computed attribute:
 * - If byte[3] is non-zero and byte[0] matches, clears byte[3].
 * - If byte[3] is non-zero and byte[0] differs, sets byte[3] to attribute.
 * - If byte[3] is zero and byte[0] differs, calls func_800C2B88.
 *
 * @param a0 Pointer to entity structure.
 */
void func_800B56B8(u8 *a0) {
    u8 *ptr;
    s32 attr;

    if (a0[4] >= 0x10) {
        return;
    }
    attr = func_800B5604(a0);
    ptr = *(u8 **)(a0 + 0x74);
    if (ptr[3] != 0) {
        if (ptr[0] == attr) {
            ptr[3] = 0;
        } else {
            ptr[3] = attr;
        }
    } else {
        if (ptr[0] != attr) {
            func_800C2B88(a0);
        }
    }
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B5748);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B59CC);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B5B48);

/**
 * @brief Register entity callback or call initialization routine.
 *
 * If the entity's word at offset 0x8C is zero, calls func_800B59CC.
 * Otherwise registers func_800B5B48 as a callback via func_800B2C58,
 * storing the entity pointer and a1 into the result structure.
 *
 * @param a0 Entity pointer.
 * @param a1 Value to store at result offset 0x10.
 */
void func_800B5C10(u8 *a0, s32 a1) {
    if (*(s32 *)(a0 + 0x8C) == 0) {
        func_800B59CC();
    } else {
        u8 *result = func_800B2C58(func_800B5B48);
        *(s32 *)(result + 0xC) = (s32)a0;
        *(s32 *)(result + 0x10) = a1;
    }
}

/**
 * @brief Compute sprite attributes and apply to entity.
 *
 * Calls RemapBattleStatusFlags with a 16-bit truncated a1 and a2, then
 * combines the result with bits 24-25 from the entity's word at +8,
 * and passes it to func_800B5C10.
 *
 * @param a0 Entity pointer.
 * @param a1 Sprite parameter (truncated to 16-bit).
 * @param a2 Second sprite parameter.
 */
void func_800B5C70(s32 a0, s32 a1, s32 a2) {
    s32 result = RemapBattleStatusFlags((u16)a1, a2);
    s32 val = *(s32 *)(a0 + 8) & 0x01800000;
    func_800B5C10(a0, val | result);
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B5CB8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B5EC8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B5FD0);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6100);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6270);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6334);

/**
 * @brief Call func_800B2B68 if D_800EF72C pointer is non-null.
 *
 * Reads the pointer stored in D_800EF72C and calls func_800B2B68
 * with it if non-zero.
 */
void func_800B64E0(void) {
    void *pool = *(void **)D_800EF72C;
    if (pool != NULL) {
        func_800B2B68(pool);
    }
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B650C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6584);

/**
 * @brief State machine for resource allocation and initialization.
 *
 * State 0: Allocates a resource via func_8013E000(2), stores result in
 * D_800EF72C, increments state, falls through.
 * State 1: Stores 0xFF at ptr[1], calls func_800B8F4C(0xF), returns 2.
 * Default: Returns 0.
 *
 * @param a0 State control structure (state at +0xD, pointer at +0x10).
 * @return 2 when initialization complete, 0 otherwise.
 */
INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B66E0);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6764);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B67D4);

void MoveBattleCameraOutward(s32 distance) {
    VECTOR *direction = func_800B3698(sizeof(VECTOR));

    direction->vx = D_800E3D70.vx - D_800E3D78.vx;
    direction->vy = D_800E3D70.vy - D_800E3D78.vy;
    direction->vz = D_800E3D70.vz - D_800E3D78.vz;
    VectorNormal(direction, direction);
    D_800E3D70.vx += (direction->vx * distance) >> 12;
    D_800E3D70.vy += (direction->vy * distance) >> 12;
    D_800E3D70.vz += (direction->vz * distance) >> 12;
    func_800B36B8(sizeof(VECTOR));
}

void UpdateBattleCameraMatrix(void) {
    BattleCameraWorkspace *work;
    s32 x;
    s32 y;
    s32 z;

    if (D_800F02A0 != 0) {
        work = func_800B3698(sizeof(BattleCameraWorkspace));
        work->rotation.vy = 0;
        work->rotation.vx = 0;
        work->rotation.vz = D_800F02A0;
        RotMatrixYXZ(&work->rotation, &work->matrix);
        ApplyMatrixSV(&work->matrix, &D_800E3D70, &work->eye);
        ApplyMatrixSV(&work->matrix, &D_800E3D78, &work->target);
        D_800F02F0 = func_800B53F8(&work->eye, &work->target, &D_800F02C8);
        MulMatrix0(&D_800F02C8, &work->matrix, &D_800F02C8);
        func_800B36B8(sizeof(BattleCameraWorkspace));
    } else {
        D_800F02F0 = func_800B53F8(&D_800E3D70, &D_800E3D78, &D_800F02C8);
    }
    x = D_800F02C8.t[0] + D_800F02C0.vx;
    y = D_800F02C0.vy;
    z = D_800F02C0.vz;
    D_800F02C0.vz = 0;
    D_800F02C0.vy = 0;
    D_800F02C0.vx = 0;
    D_800F02C8.t[0] = x;
    D_800F02C8.t[1] += y;
    D_800F02C8.t[2] += z;
}

/**
 * @brief Call func_800B3650 with D_800F02C8 as the argument.
 */
void func_800B6A9C(void) {
    func_800B3650(&D_800F02C8);
}

/**
 * @brief Compose @c D_800F02C8 with @p a0 via stack buffer and submit.
 *
 * @param a0 Right-hand matrix passed to @c CompMatrix.
 */
static void func_800B6AC0(MATRIX *a0) {
    MATRIX m;
    CompMatrix(&D_800F02C8, a0, &m);
    func_800B3650(&m);
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6AF4);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6C98);

/**
 * @brief Decode a compressed index value.
 *
 * If bit 12 of a0 is set, uses the lower 12 bits as an index into the
 * D_800F0290 halfword table. Otherwise sign-extends a0 to 16 bits.
 *
 * @param a0 Compressed value with bit 12 as format flag.
 * @return Decoded signed 16-bit value.
 */
s16 func_800B6D88(s32 a0) {
    if (a0 & 0x1000) {
        return D_800F0290[a0 & 0xFFF];
    }
    return (s16)a0;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B6DBC);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B717C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B724C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B75C8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B789C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B79B8);

void ResetBattleCameraTasks(void) {
    s32 i;
    s32 inactive;

    func_800C3C00();
    func_800B2A00(D_800F0278, D_800EF7F8, 16, 2);
    inactive = -1;
    for (i = 1; i >= 0; i--) {
        D_800EF828[i].active = inactive;
    }
    for (i = 7; i >= 0; i--) {
        D_800F0290[i] = 0;
    }
    D_800F02F4 = 0;
    D_800F0288 = 0;
    D_800F02E8 = ONE;
    D_800F1A1C = 0;
    D_800F1A24 = 0;
    D_800F1A2C = 0;
    D_800F02C0.vz = 0;
    D_800F02C0.vy = 0;
    D_800F02C0.vx = 0;
    D_800F02A0 = 0;
    D_800F02EC = 1;
}

/** @brief Raise @ref BATTLE_STATE_UNK100 when @p on, lower it otherwise. */
void func_800B7D20(s32 on) {
    if (on != 0) {
        D_800EEC5C |= BATTLE_STATE_UNK100;
    } else {
        D_800EEC5C &= ~BATTLE_STATE_UNK100;
    }
}

static void BuildBattleCurveTangents(s16 *knots, s16 *values, float *tangents, s32 count) {
    float intervals[32];
    float slopes[32]; /* Reused for the diagonal during elimination. */
    float factor;
    s32 i;

    tangents[0] = 0.0f;
    tangents[count - 1] = 0.0f;
    for (i = 0; i < count - 1; i++) {
        intervals[i] = knots[i + 1] - knots[i];
        slopes[i + 1] = (values[i + 1] - values[i]) / intervals[i];
    }
    tangents[1] = slopes[2] - slopes[1] - intervals[0] * tangents[0];
    slopes[1] = 2 * (knots[2] - knots[0]);
    for (i = 1; i < count - 2; i++) {
        factor = intervals[i] / slopes[i];
        tangents[i + 1] = slopes[i + 2] - slopes[i + 1] - tangents[i] * factor;
        slopes[i + 1] = 2 * (knots[i + 2] - knots[i]) - intervals[i] * factor;
    }
    tangents[count - 2] -= intervals[count - 2] * tangents[count - 1];
    for (i = count - 2; i > 0; i--) {
        tangents[i] = (tangents[i] - intervals[i] * tangents[i + 1]) / slopes[i];
    }
}

static s32 InterpolateBattleCurve(s16 value, s16 *knots, s16 *values,
                        float *tangents, s32 count) {
    s32 first = 0;
    s32 last = count - 1;
    s32 middle;
    s32 knot;
    s32 startValue;
    s32 nextKnot;
    s32 nextValue;
    float duration;
    float elapsed;
    float firstTangent;
    float lastTangent;
    float curve;
    float slope;

    while (first < last) {
        middle = (first + last) / 2;
        if (knots[middle] < value) {
            first = middle + 1;
        } else {
            last = middle;
        }
    }
    if (first > 0) {
        first--;
    }
    nextKnot = knots[first + 1];
    knot = knots[first];
    duration = nextKnot - knot;
    elapsed = value - knot;
    firstTangent = tangents[first];
    lastTangent = tangents[first + 1];
    curve = (lastTangent - firstTangent) * elapsed / duration;
    curve = (curve + 3.0f * firstTangent) * elapsed;
    nextValue = values[first + 1];
    startValue = values[first];
    slope = (nextValue - startValue) / duration;
    curve += slope - (firstTangent + firstTangent + lastTangent) * duration;
    return curve * elapsed + startValue;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B81B4);

SVECTOR *InterpolateBattleVector(s16 value, s16 *knots,
                                s16 *valuesX, s16 *valuesY, s16 *valuesZ,
                                s32 count, float *tangentsX, float *tangentsY,
                                float *tangentsZ, SVECTOR *result) {
    result->vx = InterpolateBattleCurve(value, knots, valuesX, tangentsX, count);
    result->vy = InterpolateBattleCurve(value, knots, valuesY, tangentsY, count);
    result->vz = InterpolateBattleCurve(value, knots, valuesZ, tangentsZ, count);
    return result;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8314);

/**
 * @brief Initialize sound system buffers and register playback handler.
 *
 * Calls func_800B86C0 to set up the primary audio buffer, func_800B2A00
 * to initialize D_800F05C8 with D_800F0578 entries, and func_800B2A84 to
 * register func_800B8314 as the playback callback.
 *
 * @return Pointer to D_800F05C8 buffer.
 */
u8 *func_800B84C8(void) {
    u8 *buf;
    func_800B86C0(D_800F02F8, D_800F0308, D_800F0408, 0x1E);
    buf = D_800F05C8;
    func_800B2A00(buf, D_800F0578, 0x14, 4);
    func_800B2A84(buf, func_800B8314);
    return buf;
}

/**
 * @brief Allocate from D_800F05C8 and clear byte at offset 0xD.
 *
 * @param task Per-frame step installed on the new task.
 */
void *func_800B853C(void *task) {
    u8 *result = func_800B2A84(D_800F05C8, task);
    result[0xD] = 0;
    return result;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8564);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8644);

/**
 * @brief Initialize a linked list structure and clear data entries.
 *
 * Sets up the header fields (head pointer, zero field, data pointer,
 * count), calls func_800B8870 to initialize the list, then clears
 * byte at offset 1 for each entry (stride 0xC).
 *
 * @param a0 Pointer to the list header structure.
 * @param a1 Head pointer to store and pass to func_800B8870.
 * @param a2 Data array pointer.
 * @param a3 Number of entries.
 */
void func_800B86C0(u8 *a0, u8 *a1, u8 *a2, s32 a3) {
    *(s32 *)a0 = (s32)a1;
    *(s32 *)(a0 + 4) = 0;
    *(s32 *)(a0 + 8) = (s32)a2;
    *(u16 *)(a0 + 0xC) = a3;
    func_800B8870(a1, a3);
    if (a3 > 0) {
        s32 i = 0;
        u8 *ptr = a2;
        do {
            ptr[1] = 0;
            i++;
            ptr += 0xC;
        } while (i < a3);
    }
}

void func_800B8BEC(void);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B872C);

static BattleListEntry *FindFreeBattleListEntry(BattleList *list) {
    s32 i;

    for (i = 0; i < list->count; i++) {
        if (list->entries[i].active == 0) {
            return &list->entries[i];
        }
    }
    return NULL;
}

void func_800B8798(BattleList *list, s32 tag) {
    BattleListEntry *entry = FindFreeBattleListEntry(list);

    if (entry != NULL) {
        BattleListEntry *result = func_800B8944(list->pool, &list->head, entry);
        result->active = tag;
    }
}

/**
 * @brief Unpack a pointer pair and call func_800B8B28 with mode 1.
 *
 * @param a0 Pointer to a structure with a word at +0 and data at +4.
 */
void func_800B87E4(s32 *a0) {
    func_800B8B28(*a0, (s32)a0 + 4, 1);
}

void func_800B8810(BattleList *list) {
    RotateLinkedList(list->pool, &list->head);
}

/**
 * @brief Unpack a pointer pair, call func_800B8A98, and clear result byte.
 *
 * @param a0 Pointer to a structure with a word at +0 and data at +4.
 */
void func_800B8838(s32 *a0) {
    u8 *result = (u8 *)func_800B8A98(*a0, (s32)a0 + 4, 1);
    if (result != 0) {
        result[1] = 0;
    }
}

/**
 * @brief Initialize a linked list array structure.
 *
 * Clears the head, stores count, then zeroes the data field of each entry (stride 8).
 *
 * @param a0 Pointer to the list structure.
 * @param count Number of entries to initialize.
 */
void func_800B8870(u8 *a0, s32 count) {
    s32 i = 1;
    *(s32 *)a0 = 0;
    *(s32 *)(a0 + 4) = count;
    if (count > 0) {
        a0 += 8;
        do {
            *(s32 *)(a0 + 4) = 0;
            i++;
            a0 += 8;
        } while (i <= count);
    }
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B88A0);

/**
 * @brief Walk a linked list, following count links.
 *
 * @param node Starting node pointer.
 * @param count Number of links to follow.
 * @return The node reached after traversal, or NULL if a null link is hit.
 */
s32 func_800B88E0(s32 node, s32 count) {
    s32 i = 0;
    if (count <= 0) goto end;
loop:
    if (node == 0) goto end;
    node = *(s32 *)node;
    i++;
    if (i < count) goto loop;
end:
    return node;
}

/**
 * @brief Allocate a linked list node and initialize it.
 *
 * Calls func_800B88A0 to allocate. If successful, clears the first word
 * (next pointer) and sets the second word to 1 (active flag).
 *
 * @return Pointer to the allocated node, or NULL if allocation failed.
 */
s32 *func_800B890C(void) {
    s32 *node = func_800B88A0();
    if (node != 0) {
        node[0] = 0;
        node[1] = 1;
    }
    return node;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8944);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B89F4);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8A98);

/**
 * @brief Look up entity via func_800B88E0 and return field at +4.
 *
 * Dereferences a1 as a pointer to get the search key, calls func_800B88E0
 * with that key and a2 as arguments. If a match is found, returns the
 * word at offset 4 of the result; otherwise returns 0.
 *
 * @param a0 Unused (passed from caller context).
 * @param a1 Pointer to search key word.
 * @param a2 Mode parameter for func_800B88E0.
 * @return Word at result+4 if found, or 0.
 */
s32 func_800B8B28(s32 a0, s32 *a1, s32 a2) {
    s32 result = (s32)func_800B88E0(*a1, a2);
    if (result != 0) {
        return *(s32 *)(result + 4);
    }
    return 0;
}

/**
 * @brief Count nodes in a linked list after skipping the first two.
 *
 * Dereferences the pointer at *a1 twice to skip two header nodes,
 * then walks the list counting nodes until NULL.
 *
 * @param a0 Unused first parameter.
 * @param a1 Pointer to the start of the linked list (double indirection).
 * @return Number of nodes after the first two, or 0 if list is too short.
 */
s32 func_800B8B60(s32 a0, s32 *a1) {
    s32 count = 0;
    a1 = *(s32 **)a1;
    if (a1 == 0) {
        return count;
    }
    a1 = *(s32 **)a1;
    if (a1 == 0) {
        return count;
    }
    do {
        a1 = *(s32 **)a1;
        count++;
    } while (a1 != 0);
    return count;
}

static void RotateLinkedList(BattleListNode *pool, BattleListNode **head) {
    BattleListNode *first;
    BattleListNode *node;

    node = *head;
    if (node != NULL) {
        first = node->next;
        if (first != NULL) {
            node->next = first->next;
            first->next = NULL;
            do {
                head = &(*head)->next;
            } while (*head != NULL);
            *head = first;
        }
    }
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8BEC);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8C6C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8CE0);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8DB8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8E2C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8E4C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8EF4);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8F2C);

/**
 * @brief Allocate handler for func_800B8BEC and store initial params.
 *
 * Registers func_800B8BEC as callback via func_800B2C58. If allocation
 * succeeds, clears halfword at +0xC, stores a0 at +0xE, clears +0x10,
 * and sets +0x11 to 0x80.
 *
 * @param a0 Value stored as halfword at handler offset 0xE.
 */
void func_800B8F4C(s32 a0) {
    u8 *result = func_800B2C58(func_800B8BEC);
    if (result != 0) {
        *(u16 *)(result + 0xC) = 0;
        *(u16 *)(result + 0xE) = a0;
        *(u8 *)(result + 0x10) = 0;
        *(u8 *)(result + 0x11) = 0x80;
    }
}

/**
 * @brief Allocate handler for func_800B8BEC with inverted byte layout.
 *
 * Same as func_800B8F4C but with +0x10 set to 0x80 and +0x11 cleared.
 *
 * @param a0 Value stored as halfword at handler offset 0xE.
 */
void func_800B8F98(s32 a0) {
    u8 *result = func_800B2C58(func_800B8BEC);
    if (result != 0) {
        *(u16 *)(result + 0xC) = 0;
        *(u16 *)(result + 0xE) = a0;
        *(u8 *)(result + 0x10) = 0x80;
        *(u8 *)(result + 0x11) = 0;
    }
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B8FE4);

/**
 * @brief Initialize sound entry fields if D_800E3DA8 pointer is non-null.
 *
 * Loads the pointer from D_800E3DA8. If non-null, sets byte at +0x10
 * to 0xFF, clears halfword at +0xC, stores a0 as halfword at +0xE,
 * and clears byte at +0x11 (re-reading the pointer for the last store).
 *
 * @param a0 Value to store at entry offset 0xE.
 */
void func_800B9048(s32 a0) {
    s32 ptr = *(s32 *)D_800E3DA8;
    if (ptr != 0) {
        s32 ptr2;
        *(u8 *)(ptr + 0x10) = 0xFF;
        ptr2 = *(s32 *)D_800E3DA8;
        *(u16 *)(ptr + 0xC) = 0;
        *(u16 *)(ptr + 0xE) = a0;
        *(u8 *)(ptr2 + 0x11) = 0;
    }
}

static s32 FadeBattleTintOut(BattleTintFadeTask *task) {
    s32 level;
    s32 i;
    s32 complete;

    level = (task->frame << 12) / task->duration;
    level = rsin((4096 - level) / 4);
    for (i = 3; i >= 0; i--) {
        D_800EF738[i].level = level;
    }
    complete = (task->frame++ >= task->duration) * 2;
    return complete;
}

/**
 * @brief Black out the screen tint and start the task that animates it.
 *
 * @param a0 Stored at offset 0xE of the task's storage.
 *
 * @note The colour stores are volatile: without it the three bytes are merged
 *       into one halfword and a byte.
 */
void func_800B9114(s32 a0) {
    BattleTint *tint;
    s32 i = 0;
    tint = D_800EF738;
    for (; i < 4; i++) {
        *(volatile u8 *)&tint->r = 0;
        *(volatile u8 *)&tint->g = 0;
        *(volatile u8 *)&tint->b = 0;
        tint++;
    }
    {
        BattleTintFadeTask *task = func_800B2C58(FadeBattleTintOut);
        task->frame = 0;
        task->duration = a0;
    }
}

/**
 * @brief Update max frame count and recompute buffer address.
 *
 * Reads the word at a0-4. If it exceeds D_800F0854, updates D_800F0854
 * and recomputes D_800F085C as D_80170000 minus the new value times 8.
 *
 * @param a0 Pointer (the word at a0-4 is the frame count).
 */
void func_800B9174(u8 *a0) {
    s32 val = *(s32 *)(a0 - 4);
    if (*(u16 *)D_800F0854 < val) {
        *(u16 *)D_800F0854 = val;
        *(s32 *)D_800F085C = (s32)D_80170000 - *(u16 *)D_800F0854 * 8;
    }
}

/**
 * @brief Align a size up to 4 bytes and store to D_800F082C.
 *
 * @param size Byte count to align.
 */
void func_800B91B4(s32 size) {
    *(s32 *)D_800F082C = (size + 3) & ~3;
}

/**
 * @brief Compute the difference between D_800F085C and D_800F082C.
 *
 * @return D_800F085C - D_800F082C.
 */
s32 func_800B91CC(void) {
    return *(s32 *)D_800F085C - *(s32 *)D_800F082C;
}

/**
 * @brief Find the first free slot in D_800F05F0 array.
 *
 * Scans 11 entries at stride 0x34 in D_800F05F0. Returns a pointer to the
 * first entry where byte at offset 1 is zero, or NULL if all occupied.
 *
 * @return Pointer to free slot, or 0 if none found.
 */
static BattleSlot *FindFreeBattleSlot(void) {
    s32 i;

    for (i = 0; i < BATTLE_SLOT_COUNT; i++) {
        if (D_800F05F0[i].active == 0) {
            return &D_800F05F0[i];
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B921C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B9290);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B94E0);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B9518);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B953C);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B96EC);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B97D8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B9BF8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800B9F34);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BA2D0);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BA640);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BA874);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BA9FC);

/**
 * @brief Call func_800B2B68 with D_800F0830.
 */
void func_800BAAA4(void) {
    func_800B2B68(D_800F0830);
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BAAC8);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BABC0);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BAD28);

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BAE08);

/**
 * @brief Clear the active byte of entries matching a given ID.
 *
 * Iterates 11 entries at stride 0x34 from D_800F05F0. If an entry's
 * first byte matches a0 or a0 + 0x1000, clears byte[1] of that entry.
 *
 * @param a0 ID to match against (also checks a0 + 0x1000).
 */
void func_800BAE28(s32 a0) {
    u8 *base = (u8 *)(s32)D_800F05F0;
    s32 i = 0;
    s32 match2 = a0 + 0x1000;
    do {
        if (base[0] == a0 || base[0] == match2) {
            base[1] = 0;
        }
        i++;
        base += 0x34;
    } while (i < 11);
}

INCLUDE_ASM("asm/ovl/battle/nonmatchings/bc_object10", func_800BAE6C);

/**
 * @brief Clear the global D_800F1668 to zero.
 */
void func_800BAEDC(void) {
    *(s32 *)D_800F1668 = 0;
}

#ifndef WORLD_WE_OBJECT7_H
#define WORLD_WE_OBJECT7_H

#include "common.h"
#include "world.h"

/**
 * @brief 0x34-byte tracking entry — one world-space target with screen-space
 * projection state and a relative neighbour link.
 *
 * Populated by @c func_800B01A0 (which fills @c screen plus @c unk30 and
 * @c unk2C from the world transform pipeline) and
 * consumed by @c func_800B3868 to compute pitch/yaw to a chained target.
 */
typedef struct {
    VECTOR pos;          /**< 0x00: world position; func_800B01A0 projects it. */
    SVECTOR screen;      /**< 0x10: projected screen-space position (x, y, z). */
    s16 unk18;           /**< 0x18: roll/twist angle — zeroed when target valid. */
    s16 yaw;             /**< 0x1A: yaw angle to target (atan2 + 0x800 bias). */
    s16 pitch;           /**< 0x1C: pitch angle to target. */
    u8 pad1E[0x0E];
    s16 unk2C;           /**< 0x2C: scratch halfword filled by func_800B01A0. */
    s8 targetIdx;        /**< 0x2E: relative index of the chained target entry (0 = none). */
    s8 status;           /**< 0x2F: -1 = uninitialized, 1 = visible/active. */
    s8 unk30;            /**< 0x30: secondary status byte. */
    u8 pad31[0x03];
} TrackEntry;

/** @brief Header for a TrackEntry array — count plus pointer-to-entries. */
typedef struct {
    u8 pad00[0x02];
    s8 count;            /**< 0x02: number of entries pointed to by @c entries. */
    u8 pad03[0x15];
    TrackEntry *entries; /**< 0x18: pointer to the entry array. */
} TrackObj;

/* File-private world data. */
extern u8 *D_800C96C8;
extern s16 D_800DCB4C;

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ s16 angle;
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 unk0F;
} WorldTrailPoint;

extern WorldTrailPoint D_800DC9B8[16]; // Position history ring, seeded with one point
extern u8 D_800DCAB8;
extern u8 D_800DCAB9;
extern s8 D_800DCABA;
extern WorldTrailPoint D_800DCAC8;
extern s32 D_800DCAD8;

/* addItemToInventory is main-binary. */
extern void addItemToInventory(s32 itemId, s32 count);

extern s32  func_800B4AA0(void);
extern void func_800B56A0(void);
extern void func_800B7240(s8 v);
extern void ResetPositionHistory(void);
extern void func_800B893C(void);

extern void SaveScenePlacement(Slot *slot, u8 mode);
extern void RestoreScenePlacement(Slot *slot, u8 mode);
extern s32 func_800B3ED0(SVECTOR *a, SVECTOR *b);
extern s32 func_800B5974(s8 marker, s16 *outA, s16 *outB, s32 mode);
extern s32 func_800B7080(s32 idx, s32 count);
extern s32 GetFootprintCorners(s32 id, SVECTOR *out, u16 *param, s32 margin);
extern void func_800B5C60(UnkWorldKeyframe *list, s16 count, MATRIX *outMat, SVECTOR *outAngles,
                                 SVECTOR *rotBuf, SVECTOR *offsetOut, ActorRecord *recs);
extern void func_800B73A4(ActorRecord *group);
extern void func_800B7530(ActorRecord *group);
extern void func_800B83B4(u8 *flags);

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ u8 unk0A;
    /* 0x0B */ u8 unk0B;
} UnkWorldPlacement;

extern u8 *D_800D228C;
extern VECTOR D_800DCAE8;
extern s32 D_800DCAF8;
extern UnkWorldKeyframe *D_800C5D58;
extern VECTOR D_800DCB08;
extern VECTOR D_800DCB18;
extern VECTOR D_800DCB28;
extern VECTOR D_800DCB38;
extern VECTOR D_800DD670;
extern UnkWorldPlacement *D_800C96FC;

#endif /* WORLD_WE_OBJECT7_H */

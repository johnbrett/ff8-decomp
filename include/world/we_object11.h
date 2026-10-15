#ifndef WORLD_WE_OBJECT11_H
#define WORLD_WE_OBJECT11_H

#include "common.h"
#include "world.h"
#include "world/we_object3.h"

#define WORLD_UNK_COUNT_20 32

typedef struct {
    /* 0x00 */ u8 unk00[68];
    /* 0x44 */ s32 unk44;
} WorldObjectSlot;

#define WORLD_UNK_OBJECT_COUNT_40 64

extern LookupTarget *D_800DD8F8[WORLD_UNK_COUNT_20]; // Backup of D_800DDB00
extern WorldObjectSlot *D_800E1D58[WORLD_UNK_OBJECT_COUNT_40];
extern MATRIX D_800C5DB8;
extern MATRIX D_800C5DD8;
extern s32 D_800DDB80[];
extern s16 D_800E1E58[];

extern void func_800BF80C(GlyphHeader *p, s32 *ot, WorldPrimBank *pools);
extern void func_800BFBFC(s32 kind);
extern void func_800BFCC0(s32 *ot, s32 arg1);
extern void ResetWorldRenderState(void);
extern void func_800C0084(s32 idx, WorldSlotVec4 *vals, s32 mode);
extern void func_800C0154(s32 idx, WorldSlotVec4 *vals, s32 mode);
extern void func_800C2B04(s32 idx, s32 mode, u32 count);

#endif /* WORLD_WE_OBJECT11_H */

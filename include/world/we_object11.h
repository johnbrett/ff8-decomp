#ifndef WORLD_WE_OBJECT11_H
#define WORLD_WE_OBJECT11_H

#include "common.h"
#include "world.h"
#include "world/we_object3.h"

#define LOOKUP_TARGET_COUNT 32
#define WORLD_OBJECT_SLOT_COUNT 64

/* Object registered in D_800E1D58 by ClaimObjectSlot; only the word at 0x44 (cleared on claim) is known. */
typedef struct {
    /* 0x00 */ u8 pad00[0x44];
    /* 0x44 */ s32 unk44;
} WorldObjectSlot;

extern LookupTarget *D_800DD8F8[LOOKUP_TARGET_COUNT];
extern WorldObjectSlot *D_800E1D58[WORLD_OBJECT_SLOT_COUNT];
extern MATRIX D_800C5DB8;
extern MATRIX D_800C5DD8;

extern void func_800BF80C(GlyphHeader *p, s32 *ot, WorldPrimBank *pools);
extern void func_800BFBFC(s32 kind);

#endif /* WORLD_WE_OBJECT11_H */

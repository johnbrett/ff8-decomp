#include "common.h"
#include "psxsdk/libgte.h"
#include "world.h"
#include "world/we_object10.h"
#include "world/we_object11.h"

// Private prototypes
void func_800C3278(s32 *ot, s32 arg1);
s32 func_800C02D8(s32 a0, s32 a1, s32 a2, s32 a3);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BF80C);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BFBFC);

void func_800BFCC0(s32 *ot, s32 arg1) {
    s32 i;

    for (i = 0; i < LOOKUP_TARGET_COUNT; i++) {
        D_800DD8F8[i] = D_800DDB00[i];
    }
    func_800C3278(&ot[1], arg1);
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", DrawSkinnedModel);

void ResetWorldRenderState(void) {
    s32 i;

    for (i = WORLD_OBJECT_SLOT_COUNT - 1; i >= 0; i--) {
        D_800E1D58[i] = NULL;
    }
    for (i = LOOKUP_TARGET_COUNT - 1; i >= 0; i--) {
        D_800DDB00[i] = NULL;
    }

    SetFarColor(0, 60, 120);
    SetFogFar(2048, 512);
    SetFogNear(512, 512);
    SetColorMatrix(&D_800C5DB8);
    SetLightMatrix(&D_800C5DD8);
}

void func_800C0084(s32 idx, SVECTOR *vals, s32 mode) {
    LookupTarget *slot;

    switch (mode) {
    case 0:
        D_800DDB00[idx]->unk10 = *vals;
        slot = D_800DDB00[idx];
        break;
    case 1:
        D_800DDB00[idx]->unk10.vx += vals->vx;
        D_800DDB00[idx]->unk10.vy += vals->vy;
        D_800DDB00[idx]->unk10.vz += vals->vz;
        slot = D_800DDB00[idx];
        break;
    default:
        return;
    }
    slot->flags &= ~(LOOKUP_TARGET_FLAG_UNK08 | LOOKUP_TARGET_FLAG_UNK10);
}

void func_800C0154(s32 idx, SVECTOR *vals, s32 mode) {
    LookupTarget *slot;

    switch (mode) {
    case 0:
        D_800DDB00[idx]->unk18 = *vals;
        slot = D_800DDB00[idx];
        break;
    case 1:
        D_800DDB00[idx]->unk18.vx += vals->vx;
        D_800DDB00[idx]->unk18.vy += vals->vy;
        D_800DDB00[idx]->unk18.vz += vals->vz;
        slot = D_800DDB00[idx];
        break;
    default:
        return;
    }
    slot->flags &= ~(LOOKUP_TARGET_FLAG_UNK08 | LOOKUP_TARGET_FLAG_UNK10);
}

static void func_800C0224(s32 idx, VECTOR *vals, s32 mode) {
    LookupTarget *slot;

    switch (mode) {
    case 0:
        slot = D_800DDB00[idx];
        slot->unk20 = *vals;
        break;
    case 1:
        D_800DDB00[idx]->unk20.vx += vals->vx;
        D_800DDB00[idx]->unk20.vy += vals->vy;
        D_800DDB00[idx]->unk20.vz += vals->vz;
        break;
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C02D8);

static s32 ClaimObjectSlot(s32 idx, s32 arg1, WorldObjectSlot *slot) {
    if (D_800E1D58[idx] != NULL) {
        return 0;
    }
    D_800E1D58[idx] = slot;
    slot->unk44 = 0;
    return func_800C02D8(arg1, 0x11, idx, idx);
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C0D00);

static s32 *func_800C1718(s32 idx, s32 firstWord, LookupTarget *slot) {
    if (D_800DDB00[idx] != NULL) {
        return NULL;
    }
    D_800DDB00[idx] = slot;
    slot->unk00 = firstWord;
    D_800DDB00[idx]->flags = 0;
    D_800DDB00[idx]->unk10.vx = 0;
    D_800DDB00[idx]->unk10.vy = 400;
    D_800DDB00[idx]->unk10.vz = 0;
    D_800DDB00[idx]->unk18.vx = 0;
    D_800DDB00[idx]->unk18.vy = 0;
    D_800DDB00[idx]->unk18.vz = 0;
    D_800DDB00[idx]->unk20.vx = ONE;
    D_800DDB00[idx]->unk20.vy = ONE;
    D_800DDB00[idx]->unk20.vz = ONE;
    D_800DDB00[idx]->unk50 = 0;
    D_800DDB00[idx]->field52 = 0;
    D_800DDB00[idx]->flags = 0;
    return &slot->unk98;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C17E4);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C22B0);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C239C);

void func_800C2B04(s32 idx, s32 mode, u32 count) {
    LookupTarget *slot = D_800DDB00[idx];
    s32 sum;
    s32 prodSum;
    s32 j;
    u32 i;

    if (slot->unk00 != -1) {
        j = 2;
        if (mode == 13) {
            prodSum = 0;
            sum = 0;
            for (i = 0; i < count; i++) {
                sum += slot->unk68[j - 2];
                prodSum += slot->unk68[j - 2] * slot->unk68[j - 1];
                j += 2;
            }
            D_800DDB00[idx]->unk0C = D_800DDB00[idx]->unk68[j - 2] * 16;
            D_800DDB00[idx]->unk0E = D_800DDB00[idx]->unk68[j - 1];
            D_800DDB00[idx]->unk08 = D_800DDB00[idx]->unk6C + (prodSum + sum);
            D_800DDB00[idx]->unk50 = 0;
        }
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C2C00);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3278);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3674);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3714);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3918);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3B74);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3CE4);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3DB0);

#include "common.h"
#include "psxsdk/libgte.h"
#include "world.h"
#include "world/we_object10.h"
#include "world/we_object11.h"


// Private prototypes
void func_800C3278(u8 *arg0, s32 arg1);
void func_800C3674(SVECTOR *verts, s32 *sxy, s16 *sz, s32 count);
void func_800C3714(u8 *pkt, u8 *tris, s32 *env, s32 count);
void func_800C3918(u8 *pkt, u8 *quads, s32 *env, s32 count);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BF80C);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BFBFC);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BFCC0);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", DrawSkinnedModel);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", ResetWorldRenderState);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C0084);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C0154);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", SetRenderSlotScale);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C02D8);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", ClaimObjectSlot);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C0D00);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", ClaimRenderSlot);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C17E4);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C22B0);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C239C);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C2B04);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C2C00);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3278);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3674);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3714);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3918);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3B74);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3CE4);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3DB0);

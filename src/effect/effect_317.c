/**
 * @file effect_317.c
 * @brief Acid (Quistis)
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"

typedef struct {
    /* 0x00 */ u8 unk00[12];
    /* 0x0C */ s32 frame;
    /* 0x10 */ SVECTOR pos;
    /* 0x18 */ SVECTOR velocity;
} SpriteParticle317;

extern void *D_801D34C4;
extern BattleSpriteAnim D_801A6518;

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0044);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A00C0);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0140);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A01BC);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A024C);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0370);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0474);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A086C);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A09EC);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0A54);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0ABC);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A0CAC);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1268);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A135C);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1890);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1AE8);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1C68);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1CEC);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1E54);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A1F2C);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A203C);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A20F0);

s32 func_801A21A0(SpriteParticle317 *particle) {
    BattleSpritePrim *prim;
    s32 frame;
    void *head;

    func_800C96E4(&particle->pos, particle->pos.pad, 0);
    prim = func_800B3698(sizeof(BattleSpritePrim));
    prim->anim = &D_801A6518;
    prim->frame = particle->frame;
    prim->flags = 0;
    head = D_801D34C4;
    D_801D34C4 = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->frame + 1;
    particle->pos.vx += particle->velocity.vx;
    particle->pos.vy += particle->velocity.vy;
    particle->pos.vz += particle->velocity.vz;
    particle->velocity.vy += 16;
    particle->frame = frame;
    return (frame >= 9) * 2;
}

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A227C);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A2364);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A23E0);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A25F4);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A27F0);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A2B80);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A2CEC);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A3184);

INCLUDE_ASM("asm/ovl/effect_317/nonmatchings/effect_317", func_801A3450);

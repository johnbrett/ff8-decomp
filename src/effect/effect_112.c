/**
 * @file effect_112.c
 * @brief Meteor Barret (Zell's Finisher)
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"

typedef struct {
    /* 0x00 */ u8 unk00[12];
    /* 0x0C */ s16 frame;
    /* 0x0E */ s16 frames;
    /* 0x10 */ BattleSpriteAnim *anim;
    /* 0x14 */ SVECTOR pos;
    /* 0x1C */ SVECTOR velocity;
} SpriteParticle112;

extern void *D_801ECDA8;

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0044);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A00C0);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0140);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A01BC);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A024C);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A03CC);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0434);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A049C);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A068C);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0C48);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A0D38);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A1130);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A1238);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A12AC);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A1360);

s32 func_801A14C4(SpriteParticle112 *particle) {
    BattleSpritePrim *prim;
    s16 frame;
    void *head;

    prim = func_800B3698(sizeof(BattleSpritePrim));
    func_800C96E4(&particle->pos, particle->pos.pad, -(particle->velocity.pad >> 2));
    prim->anim = particle->anim;
    prim->frame = particle->frame;
    prim->flags = 0;
    head = D_801ECDA8;
    D_801ECDA8 = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->frame + 1;
    particle->pos.vx += particle->velocity.vx;
    particle->pos.vy += particle->velocity.vy;
    particle->pos.vz += particle->velocity.vz;
    particle->frame = frame;
    return (frame >= particle->frames) * 2;
}

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A15AC);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A1698);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A16F4);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A1790);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A2EEC);

INCLUDE_ASM("asm/ovl/effect_112/nonmatchings/effect_112", func_801A3248);

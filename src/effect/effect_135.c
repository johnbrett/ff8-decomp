/**
 * @file effect_135.c
 * @brief Reflect Beam
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"
extern BattleSpriteAnim D_801A44E0;
extern void *D_801DF2B4;

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A0308);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A0648);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A09D4);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A0DB8);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A10DC);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1480);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1840);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1C88);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1EB4);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1ED8);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1F54);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A1FD4);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A2050);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A20E0);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A2170);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A2274);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A2684);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A2804);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A286C);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A28D4);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A2AC4);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A3080);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A3128);

s32 func_801A31D0(BattleSpriteParticle *particle) {
    BattleSpritePrim *prim;
    s16 frame;
    void *head;
    prim = func_800B3698(sizeof(BattleSpritePrim));
    func_800C96E4(&particle->pos.vector, 2048, -512);
    prim->anim = &D_801A44E0;
    prim->frame = particle->pos.fields.frame;
    prim->flags = 0;
    head = D_801DF2B4;
    D_801DF2B4 = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->pos.fields.frame + 1;
    particle->velocityX += particle->accelerationX;
    particle->velocityY += particle->accelerationY;
    particle->velocityZ += particle->accelerationZ;
    particle->pos.fields.frame = frame;
    particle->pos.vector.vx += particle->velocityX;
    particle->pos.vector.vy += particle->velocityY;
    particle->pos.vector.vz += particle->velocityZ;
    return (frame > 7) * 2;
}

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A32D8);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A33A8);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A3624);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A3AB0);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A3F78);

INCLUDE_ASM("asm/ovl/effect_135/nonmatchings/effect_135", func_801A434C);

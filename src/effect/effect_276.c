/**
 * @file effect_276.c
 * @brief X-ATM092 Death
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"
extern BattleSpriteAnim D_801A7490;
extern void *D_801D6B48;

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A0308);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A0648);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A09D4);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A0DB8);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A10DC);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1480);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1840);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1C88);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1EB4);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1ED8);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1F54);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A1FD4);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2050);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A20E0);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2204);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2294);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2398);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2924);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2AA4);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2B0C);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2B74);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A2D64);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3320);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3854);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3A78);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3BC0);

s32 func_801A3D5C(BattleSpriteParticle *particle) {
    BattleSpritePrim *prim;
    s16 frame;
    void *head;
    prim = func_800B3698(sizeof(BattleSpritePrim));
    func_800C96E4(&particle->pos.vector, particle->scale, -(particle->scale >> 2));
    prim->anim = &D_801A7490;
    prim->frame = particle->pos.fields.frame >> 1;
    prim->flags = 0;
    head = D_801D6B48;
    D_801D6B48 = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->pos.fields.frame + 1;
    particle->pos.vector.vx += particle->velocityX;
    particle->pos.vector.vy += particle->velocityY;
    particle->pos.vector.vz += particle->velocityZ;
    particle->velocityY += 16;
    particle->pos.fields.frame = frame;
    return (frame > 15) * 2;
}

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3E54);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3F4C);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A3FE8);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A407C);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A41CC);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A4368);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A4460);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A4674);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A48BC);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A4C64);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A4C90);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A5240);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A5420);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A54F8);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A5924);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A596C);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A59D4);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A5A00);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A6384);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A6590);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A6618);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A6880);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A693C);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A70CC);

INCLUDE_ASM("asm/ovl/effect_276/nonmatchings/effect_276", func_801A73AC);

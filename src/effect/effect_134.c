/**
 * @file effect_134.c
 * @brief Beam Laser
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"
extern BattleSpriteAnim D_801A4044;
extern void *D_801D2538;

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A0308);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A0648);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A09D4);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A0DB8);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A10DC);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1480);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1840);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1C88);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1EB4);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1ED8);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1F54);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A1FD4);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A2050);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A20E0);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A21E4);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A254C);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A26CC);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A2734);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A279C);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A298C);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A2F48);

s32 func_801A2FB0(BattleSpriteParticle *particle) {
    BattleSpritePrim *prim;
    s16 frame;
    void *head;
    prim = func_800B3698(sizeof(BattleSpritePrim));
    func_800C96E4(&particle->pos.vector, 3072, -768);
    prim->anim = &D_801A4044;
    prim->frame = particle->pos.fields.frame;
    prim->flags = 0;
    head = D_801D2538;
    D_801D2538 = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->pos.fields.frame + 1;
    particle->pos.vector.vx += particle->velocityX;
    particle->pos.vector.vy += particle->velocityY;
    particle->pos.vector.vz += particle->velocityZ;
    particle->pos.fields.frame = frame;
    return (frame > 15) * 2;
}

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3088);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3130);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A32AC);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3A6C);

INCLUDE_ASM("asm/ovl/effect_134/nonmatchings/effect_134", func_801A3DB0);

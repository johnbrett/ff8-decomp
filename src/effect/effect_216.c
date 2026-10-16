/**
 * @file effect_216.c
 * @brief Different Beat (Zell's Finisher)
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"

typedef struct {
    /* 0x00 */ u8 unk00[12];
    /* 0x0C */ SVECTOR pos;
    /* 0x14 */ s8 velocityX;
    /* 0x15 */ s8 velocityY;
    /* 0x16 */ s8 velocityZ;
    /* 0x17 */ s8 frame;
} SpriteParticle216;

extern BattleSpriteAnim D_801AAE10;
extern void *D_801C3B8C;

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A05A0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A07B8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A0900);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A0C38);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A0CC4);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A0DA8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A1098);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A13E0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A1968);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A1F90);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A22BC);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A2668);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A2C30);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A32C0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A34EC);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A392C);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A3DD4);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A41D8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A4650);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A4AC0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A4FC0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A53F8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A58CC);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5AF8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5B1C);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5B98);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5C18);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5C94);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5D24);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5E48);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5ED8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A5FDC);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A6580);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A6700);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A6768);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A67D0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A69C0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A6F7C);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A6FB4);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7084);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A70BC);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7168);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A71F0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7284);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7318);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7338);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7424);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7628);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A76E4);

s32 func_801A7798(SpriteParticle216 *particle) {
    BattleSpritePrim *prim;
    s8 frame;
    void *head;

    func_800C96E4(&particle->pos, particle->pos.pad, -(particle->pos.pad >> 2));
    prim = func_800B3698(sizeof(BattleSpritePrim));
    prim->anim = &D_801AAE10;
    prim->frame = particle->frame;
    prim->flags = 0;
    head = D_801C3B8C;
    D_801C3B8C = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->frame + 1;
    particle->pos.vx += particle->velocityX << 2;
    particle->pos.vy += particle->velocityY << 2;
    particle->pos.vz += particle->velocityZ << 2;
    particle->frame = frame;
    return (frame > 11) * 2;
}

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7898);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A79C8);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7B28);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7C64);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7D10);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7ED0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7EF4);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A7F18);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A80F0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A8194);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A8240);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A8364);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A845C);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A8698);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A9D8C);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801A9E84);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801AA2E0);

INCLUDE_ASM("asm/ovl/effect_216/nonmatchings/effect_216", func_801AA9C0);

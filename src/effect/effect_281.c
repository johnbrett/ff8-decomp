/**
 * @file effect_281.c
 * @brief Shotgun
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "battle/bc_object15.h"
typedef struct {
    /* 0x00 */ u8 unk00[12];
    /* 0x0C */ BattleSpriteAnim *anim;
    /* 0x10 */ SVECTOR pos;
    /* 0x18 */ s16 velocityX;
    /* 0x1A */ s16 velocityY;
    /* 0x1C */ s16 velocityZ;
    /* 0x1E */ s16 frames;
    /* 0x20 */ s16 accelerationX;
    /* 0x22 */ s16 accelerationY;
    /* 0x24 */ s16 accelerationZ;
} ShotgunParticle;
extern void *D_801A83D4;

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A0308);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A0648);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A09D4);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A0DB8);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A10DC);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1480);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1840);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1C88);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1EB4);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1ED8);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1F54);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A1FD4);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2050);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A20E0);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A21E4);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2504);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2684);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A26EC);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2754);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2944);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2F00);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A2F90);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A3018);

s32 func_801A3108(ShotgunParticle *particle) {
    BattleSpritePrim *prim;
    s16 frame;
    void *head;
    func_800C96E4(&particle->pos, 800, -200);
    prim = func_800B3698(sizeof(BattleSpritePrim));
    prim->anim = particle->anim;
    prim->frame = particle->pos.pad;
    prim->flags = 0;
    head = D_801A83D4;
    D_801A83D4 = func_800C9E10(prim, D_800FA5E8->ot, 2, head);
    func_800B36B8(sizeof(BattleSpritePrim));
    frame = particle->pos.pad + 1;
    particle->pos.vx += particle->velocityX;
    particle->pos.vy += particle->velocityY;
    particle->pos.vz += particle->velocityZ;
    particle->velocityX += particle->accelerationX;
    particle->velocityY += particle->accelerationY;
    particle->velocityZ += particle->accelerationZ;
    particle->pos.pad = frame;
    return (frame >= particle->frames) * 2;
}

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A3210);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A3298);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A3678);

INCLUDE_ASM("asm/ovl/effect_281/nonmatchings/effect_281", func_801A38D4);

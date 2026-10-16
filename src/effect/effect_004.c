/**
 * @file effect_004.c
 * @brief Double
 */
#include "common.h"
#include "effect.h"

typedef struct DoubleTask {
    /* 0x00 */ u8 taskHeader[12];
    /* 0x0C */ EffectAnimSet *animSet;
    /* 0x10 */ EffectModel *model;
    /* 0x14 */ EffectModel *linkedModel;
    /* 0x18 */ struct DoubleTask *owner;
    /* 0x1C */ SVECTOR pos;
    /* 0x24 */ u8 pad024[12];
    /* 0x30 */ s32 scaleX;
    /* 0x34 */ s32 scaleY;
    /* 0x38 */ s32 scaleZ;
    /* 0x3C */ u8 pad03C[10];
    /* 0x46 */ s16 unk046;
    /* 0x48 */ u8 pad048[4];
    /* 0x4C */ BattleSpriteAnim *anim;
    /* 0x50 */ s16 frame;
    /* 0x52 */ u8 pad052[2];
    /* 0x54 */ SVECTOR origin;
    /* 0x5C */ s16 unk05C;
    /* 0x5E */ s16 unk05E;
    /* 0x60 */ u8 pad060[2];
    /* 0x62 */ s16 unk062;
    /* 0x64 */ s16 unk064;
    /* 0x66 */ u8 pad066[4];
    /* 0x6A */ s16 unk06A;
} DoubleTask;

extern u8 D_801D4A94[];
extern BattleSpriteAnim D_801A5CB0;

void func_801A46AC(DoubleTask *task);
DoubleTask *func_801A09B4(void *pool, void (*step)(DoubleTask *), s32 size,
                        DoubleTask *owner);
void func_801A0C74(DoubleTask *task, SVECTOR *out);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0180);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A02D0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A037C);

void func_801A039C(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A03A4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A04A0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A059C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A05D4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0764);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A08F0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A098C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A09B4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0B40);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0C74);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0CA4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0CD4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0D04);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0E40);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0E70);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0EA0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A0ED0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A111C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A116C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1210);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1240);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1298);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A12BC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1304);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A134C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1404);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1458);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A14C4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A14FC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A17DC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1B14);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A1EA8);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A22A0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A25C8);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A2968);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A2D3C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A319C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A33F0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3760);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A385C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3978);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3A14);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3B20);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3C10);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3C40);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3CD4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3DB0);

static void SpawnDoubleParticle(DoubleTask *owner) {
    DoubleTask *task;

    task = func_801A09B4(D_801D4A94, func_801A46AC, sizeof(DoubleTask), owner);
    task->unk062 = ONE;
    task->unk064 = 0;
    task->unk05E = owner->unk05E;
    task->unk06A = owner->unk06A;
    func_801A0C74(task, &task->pos);
    task->pos.vy -= 640;
    task->origin = task->pos;
    task->unk05C = owner->unk05C;
    task->unk046 = owner->unk05C;
    /* The intervening calls can change the owner. */
    task->unk06A = owner->unk06A;
    task->anim = &D_801A5CB0;
    task->frame = ONE;
    task->scaleX = 16;
    task->scaleY = 16;
    task->scaleZ = 16;
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A3F40);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A418C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A426C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A42B0);

void func_801A42FC(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4304);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A43D4);

void func_801A4424(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A442C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A44EC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A453C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4570);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A45A4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A461C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A464C);

void func_801A46A4(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A46AC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4910);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4948);

void func_801A49C4(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A49CC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4B24);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4B6C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4B9C);

void func_801A4BF8(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4C00);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4DB4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4DD4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4DF4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4E14);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4E28);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4E48);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4E68);

void func_801A4E84(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4E8C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A4FB0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A50C4);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A51F0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5234);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5278);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A52BC);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5300);

void func_801A534C(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5354);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A540C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A545C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A54B0);

void func_801A5514(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A551C);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5654);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5668);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A56C0);

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5710);

void func_801A5740(void) {
}

INCLUDE_ASM("asm/ovl/effect_004/nonmatchings/effect_004", func_801A5748);

#include "common.h"
#include "effect.h"
#include "effect/lib/entity.h"

typedef struct {
    /* 0x00 */ u8 pad000[4];
    /* 0x04 */ void *unk004;
    /* 0x08 */ u8 pad008[12];
    /* 0x14 */ s16 unk014;
    /* 0x16 */ s16 unk016;
    /* 0x18 */ s16 unk018;
    /* 0x1A */ s16 unk01A;
    /* 0x1C */ u8 unk01C;
    /* 0x1D */ u8 unk01D;
    /* 0x1E */ u8 unk01E;
    /* 0x1F */ u8 pad01F;
    /* 0x20 */ s32 unk020;
    /* 0x24 */ s16 unk024;
} DribbleModelState;

typedef struct {
    /* 0x00 */ u8 pad000[96];
    /* 0x60 */ void *unk060;
    /* 0x64 */ DribbleModelState *state;
    /* 0x68 */ BattleEffectSlot *slot;
    /* 0x6C */ s32 *unk06C;
    /* 0x70 */ s32 *unk070;
    /* 0x74 */ u8 pad074[60];
    /* 0xB0 */ s16 unk0B0;
    /* 0xB2 */ u8 pad0B2[6];
} DribbleModel;

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1794);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1818);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A18BC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1934);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1A00);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1A94);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1B0C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1B9C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1C14);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1C44);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1CA0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1D6C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A1F00);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A21CC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A24F0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A2878);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A2C5C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A2F64);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A32EC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A36A8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A3AF0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A3D34);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A3F3C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A3FF4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A47FC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A48F0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5230);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A534C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5384);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5430);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A551C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5534);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5B60);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5DC8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5E88);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A5FA8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A60C8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A6130);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A6BCC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A6CCC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A6D6C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A6FF4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A71FC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A740C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A7E7C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A7EB8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A7EF8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A7F10);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A7F98);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A81CC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8280);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A83BC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8498);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A860C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8718);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8830);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8AF8);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8D9C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8E0C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A8E60);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A9108);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A93E0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A9474);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A94D0);

void func_801A9518(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A9520);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A95C0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A965C);

static void InitDribbleModel(DribbleModel *model, void *arg1, DribbleModelState *state,
                   void *arg3, BattleEffectSlot *slot, s32 slotIndex) {
    effectZeroWords(model, sizeof(DribbleModel));
    model->unk060 = arg1;
    model->state = state;
    model->slot = slot;
    model->unk0B0 = slotIndex;
    model->unk06C = &D_800FA5F0;
    model->unk070 = &D_800FA5F0;
    state->unk018 = 320;
    state->unk01C = 128;
    state->unk01D = 128;
    state->unk01E = 128;
    state->unk004 = arg3;
    state->unk014 = 0;
    state->unk016 = 0;
    state->unk01A = 0;
    state->unk020 = -1;
    state->unk024 = 0;
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A9760);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801A97C0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA2D4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA540);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA564);

void func_801AA6B4(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA6BC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA7BC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA988);

void func_801AA9A4(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AA9AC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AAA4C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AAA9C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AAC24);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AAE50);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AAF70);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AAFE4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB070);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB0D4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB1D0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB37C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB3D4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB4E0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB5DC);

void func_801AB644(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB64C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB7CC);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB82C);

void func_801AB848(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB850);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB8F0);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB964);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801AB998);

void func_801ABA20(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABA28);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABB04);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABB18);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABB2C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABB9C);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABBF4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABC54);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABC68);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABC90);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABCA4);

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABCB8);

void func_801ABCD4(void) {
}

INCLUDE_ASM("asm/ovl/effect_041/nonmatchings/effect_041_tail", func_801ABCDC);

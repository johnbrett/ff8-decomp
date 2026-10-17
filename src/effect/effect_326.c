/**
 * @file effect_326.c
 * @brief Zantetsuken Reverse
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"

typedef struct {
    /* 0x00 */ u8 pad000[12];
    /* 0x0C */ s16 unk00C;
    /* 0x0E */ s16 unk00E;
    /* 0x10 */ s16 unk010;
    /* 0x12 */ s16 unk012;
    /* 0x14 */ s16 unk014;
    /* 0x16 */ s16 unk016;
    /* 0x18 */ s16 unk018;
    /* 0x1A */ s16 unk01A;
    /* 0x1C */ s16 unk01C;
    /* 0x1E */ s16 unk01E;
    /* 0x20 */ s16 unk020;
    /* 0x22 */ s16 unk022;
} ZantetsukenReversePart;
extern u8 D_801A9F3C[];
s32 func_8019CFC4(void *);
s32 func_8019D144(void *);

static void SpawnZantetsukenReverseParts(void);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80190000);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019029C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801907A8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80190DAC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019143C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80191C5C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80191EF4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80191F7C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80191FAC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80192020);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80192110);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80192218);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801925AC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019299C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80192EAC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801934BC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80193640);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80193674);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801936C4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801937BC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019469C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019470C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801947A0);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801948A4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801948F8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80194AA4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80194C00);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80194D30);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80194E3C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195148);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195A9C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195D44);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195E50);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195E7C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195EA0);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195ED0);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80195F04);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80196384);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80196508);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80196694);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80196814);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80196994);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80196A38);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801971CC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197330);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197494);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197600);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197734);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197C7C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197E1C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80197FA0);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80198090);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80198514);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80198A98);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80198B58);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80198C70);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80198EB8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019924C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_801992DC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80199B7C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_80199BCC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019A45C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019A52C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019A8A0);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019AF0C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019AF5C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B00C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B110);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B37C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B5D8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B834);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B8D8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B948);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019B9B8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019BF38);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019BFEC);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019C148);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019C37C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019C5A8);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019C7E4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019CA18);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019CC7C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019CDE4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019CF2C);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019CFC4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019D144);

static void SpawnZantetsukenReverseParts(void) {
    ZantetsukenReversePart *part;
    part = func_800B2A84(D_801A9F3C, func_8019CFC4);
    part->unk00C = 0;
    part->unk00E = 0;
    part->unk010 = 0;
    part->unk012 = -12000;
    part->unk016 = 0;
    part->unk018 = 0;
    part->unk014 = -4500;
    part->unk01C = 12288;
    part->unk022 = 50;
    part->unk01E = -33;
    part->unk020 = -33;
    part = func_800B2A84(D_801A9F3C, func_8019CFC4);
    part->unk00C = 0;
    part->unk00E = 1;
    part->unk010 = 0;
    part->unk012 = -12000;
    part->unk014 = -1100;
    part->unk016 = 0;
    part->unk018 = 0;
    part->unk01C = 12288;
    part->unk022 = -40;
    part->unk01E = 33;
    part->unk020 = 33;
    part = func_800B2A84(D_801A9F3C, func_8019CFC4);
    part->unk00C = 0;
    part->unk00E = 0;
    part->unk010 = 0;
    part->unk012 = -12450;
    part->unk014 = -4500;
    part->unk016 = 2048;
    part->unk018 = 0;
    part->unk01C = 12288;
    part->unk022 = 50;
    part->unk01E = -33;
    part->unk020 = -33;
    part = func_800B2A84(D_801A9F3C, func_8019CFC4);
    part->unk00C = 0;
    part->unk00E = 1;
    part->unk010 = 0;
    part->unk012 = -12450;
    part->unk014 = -1100;
    part->unk016 = 2048;
    part->unk018 = 0;
    part->unk01C = 12288;
    part->unk022 = -40;
    part->unk01E = 33;
    part->unk020 = 33;
    part = func_800B2A84(D_801A9F3C, func_8019D144);
    part->unk012 = -12500;
    part->unk00C = 0;
    part->unk010 = 0;
    part->unk014 = -4500;
    part->unk01E = 288;
    part->unk01C = 288;
    part->unk018 = 0;
    part->unk020 = 18432;
}

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019D470);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019D858);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019DA48);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019DF80);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019E110);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019E2A0);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019E390);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019E3F4);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019ED68);

INCLUDE_ASM("asm/ovl/effect_326/nonmatchings/effect_326", func_8019F4CC);

/**
 * @file effect_191.c
 * @brief Doomtrain Summon (Runaway Train)
 */
#include "common.h"
#include "battle.h"
#include "battle/bc_object9.h"
#include "psxsdk/libc.h"
#include "effect/effect_191.h"

typedef struct {
    /** 0x00 */ u8 pad00[0xC];
    /** 0x0C */ s16 unk0C;
} func_8019B604_arg0;

typedef struct {
    /** 0x00 */ u8 pad00[0xC];
    /** 0x0C */ s16 unk0C;
    /** 0x0E */ s16 unk0E;
    /** 0x10 */ s16 unk10;
    /** 0x12 */ s16 unk12;
    /** 0x14 */ s16 unk14;
    /** 0x16 */ s16 unk16;
    /** 0x18 */ u8 pad18[0x1C - 0x18];
    /** 0x1C */ s16 unk1C;
    /** 0x1E */ s16 unk1E;
    /** 0x20 */ s16 unk20;
    /** 0x22 */ s16 unk22;
} func_8019B2C0_arg0;

s32 func_8019B2C0(func_8019B2C0_arg0 *arg0);
static s32 func_8019B604(func_8019B604_arg0 *arg0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80190000);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80190320);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801906B4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80190AA4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80190FB4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801915C4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80191748);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019177C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801917CC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801918C4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801927A4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80192814);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80192BC8);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80192C3C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80192CB8);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80192D78);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80192DEC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019331C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801933F0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801934E0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193564);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193594);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193608);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801936F0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801937F8);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193824);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193848);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193878);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801938AC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193978);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193A64);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193AA8);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193AEC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193B58);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193BC4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193C7C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193D14);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193DCC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193E90);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80193F24);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80194080);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801941D4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80194324);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80194518);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801946C0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019481C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80194B54);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80194C30);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80194FA0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80195304);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80195808);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80195868);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80195C18);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80195C68);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801962EC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801966C0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019672C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019679C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80196BA4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80196D30);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80196E14);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801970F8);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019714C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801971A0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801971F4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019724C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801972A4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019776C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80197F08);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80197F88);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80198004);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_801986F4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019876C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80198FCC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019903C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80199B44);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80199BC0);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_80199C38);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019A5AC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019A620);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019B254);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019B2C0);

static s32 func_8019B604(func_8019B604_arg0 *arg0) {
    func_8019B2C0_arg0 *puff;
    s32 count;
    s32 i;

    if (D_800EEC5C & (BATTLE_STATE_UNK200 | BATTLE_STATE_UNK001)) {
        return 0;
    }
    // Unsigned compare is required to match the generated sltiu.
    if ((u16)arg0->unk0C < 12 && arg0->unk0C % 3 == 1) {
        count = rand() % 2 + 1;
        for (i = 0; i < count; i++) {
            puff = func_800B2A84(&D_801A8668, func_8019B2C0);
            puff->unk0C = 0;
            puff->unk0E = i + rand() % 4;
            puff->unk10 = rand() % 400 + 1000;
            puff->unk12 = rand() % 2000 - 1300;
            puff->unk14 = -6000 - rand() % 3000;
            puff->unk16 = 12;
            puff->unk1C = rand() % 3072 + 1152;
            puff->unk1E = puff->unk1C / 6;
            puff->unk20 = puff->unk22 = (rand() % 6144 + 1664) / 2;
        }
    }
    return ++arg0->unk0C > 12 ? 2 : 0;
}

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019B8AC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019BE70);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019C514);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019CB5C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019CD28);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019D0B4);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019D48C);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019D4EC);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019DC00);

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019E1E8);

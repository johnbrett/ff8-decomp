/**
 * @file effect_191.c
 * @brief Doomtrain Summon (Runaway Train)
 */
#include "common.h"
#include "effect.h"
#include "battle/bc_object9.h"

typedef struct {
    /* 0x00 */ u8 pad000[12];
    /* 0x0C */ s16 age;
    /* 0x0E */ s16 side;
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x16 */ s16 duration;
    /* 0x18 */ s16 rotation;
    /* 0x1A */ s16 unk01A;
    /* 0x1C */ s16 scale;
    /* 0x1E */ u8 pad01E[2];
    /* 0x20 */ s16 unk020;
} DoomtrainTask;

extern u8 D_801A8668[];

s32 func_8019481C(DoomtrainTask *task);

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

static void StartDoomtrainPair(void) {
    DoomtrainTask *task;

    task = func_800B2A84(D_801A8668, func_8019481C);
    task->age = 0;
    task->side = 0;
    task->x = 3200;
    task->y = 0;
    task->z = -3200;
    task->duration = 103;
    task->rotation = -1024;
    task->unk01A = 1;
    task->scale = ONE;
    task->unk020 = 1;
    task = func_800B2A84(D_801A8668, func_8019481C);
    task->age = 0;
    task->side = 1;
    task->x = -3200;
    task->y = 0;
    task->z = 3200;
    task->duration = 103;
    task->rotation = 1024;
    task->unk01A = 1;
    task->scale = ONE;
    task->unk020 = 0;
}

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

INCLUDE_ASM("asm/ovl/effect_191/nonmatchings/effect_191", func_8019B604);

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

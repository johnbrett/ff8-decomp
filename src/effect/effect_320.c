/**
 * @file effect_320.c
 * @brief Dark Flare
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/libgpu.h"

/* The packed color word is needed to match the original word store. */
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 color;
    /* 0x08 */ DVECTOR xy0;
    /* 0x0C */ DVECTOR xy1;
    /* 0x10 */ DVECTOR xy2;
    /* 0x14 */ DVECTOR xy3;
} ScreenTintQuad;

extern void *D_801B1358;

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A0310);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A0658);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A0BE0);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A1208);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A1534);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A18E0);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A1EA8);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A2538);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A2764);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A2AE8);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A2EC4);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A3488);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A3AF4);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A3EB8);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A42FC);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A4900);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A4FD4);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5200);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5224);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A52A0);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5320);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A539C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A542C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A54BC);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A55C0);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5A0C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5B8C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5BF4);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5C5C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A5E4C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A6408);

static void DrawDarkFlareScreenTint(u32 color) {
    ScreenTintQuad *quad;
    DR_TPAGE *mode;

    mode = D_801B1358;
    D_801B1358 = mode + 1;
    setlen(mode, 1);
    mode->code[0] = 0xE10002A0;
    addPrim(&D_800FA5E8->frontOT[3], mode);
    quad = D_801B1358;
    D_801B1358 = quad + 1;
    setlen(quad, 5);
    quad->color = color;
    setcode(quad, 0x2A);
    quad->xy2.vx = quad->xy0.vx = 0;
    quad->xy1.vx = quad->xy3.vx = 320;
    quad->xy0.vy = quad->xy1.vy = 0;
    quad->xy2.vy = quad->xy3.vy = 216;
    addPrim(&D_800FA5E8->frontOT[3], quad);
    mode = D_801B1358;
    D_801B1358 = mode + 1;
    setlen(mode, 1);
    mode->code[0] = 0xE10002C0;
    addPrim(&D_800FA5E8->frontOT[3], mode);
}

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A65C4);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A6698);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A678C);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A6E24);

INCLUDE_ASM("asm/ovl/effect_320/nonmatchings/effect_320", func_801A70A4);

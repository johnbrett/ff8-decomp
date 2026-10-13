/**
 * @file effect_274.c
 * @brief Duel
 */
#include "common.h"
#include "battle.h"
#include "psxsdk/libgpu.h"
#include "psxsdk/libgte.h"

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 colour0;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u32 colour1;
    /* 0x10 */ s16 x1;
    /* 0x12 */ s16 y1;
    /* 0x14 */ u32 colour2;
    /* 0x18 */ s16 x2;
    /* 0x1A */ s16 y2;
    /* 0x1C */ u32 colour3;
    /* 0x20 */ s16 x3;
    /* 0x22 */ s16 y3;
} DuelBorderQuad;

extern void *D_801D3A58;

static void DrawDuelScreenBorders(s32 frame);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0020);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0058);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0340);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0680);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0A0C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A0DF0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A1114);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A14B8);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A1878);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A1CC0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A1EEC);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A1F10);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A1F8C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A200C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A2088);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A2118);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A223C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A22CC);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A23D0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A28B8);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A2A38);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A2AA0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A2B08);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A2CF8);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A32B4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A32D4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A33C0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A35C4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A3B44);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A3D5C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A3EA4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A41D4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4260);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4338);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4370);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A446C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A44A4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4550);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A45D8);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A466C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4700);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A472C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4758);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4770);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A47F4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A48AC);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4AD0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4C2C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A4D68);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A5048);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A50EC);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A5184);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A5630);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A576C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A5AFC);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A5D9C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A5E98);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A62A0);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A65B8);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A6934);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A69E4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A6EF4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A6F2C);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A7264);

static void DrawDuelScreenBorders(s32 frame) {
    s32 height = rsin(frame << 4);
    DR_TPAGE *mode;
    DuelBorderQuad *quad;
    u32 *ot;
    u32 *colour0;
    u32 *colour1;
    u32 *colour2;
    u32 *colour3;

    mode = D_801D3A58;
    D_801D3A58 = mode + 1;
    ot = &D_800FA5E8->frontOT[3];
    setlen(mode, 1);
    mode->code[0] = 0xE1000220;
    addPrim(ot, mode);
    quad = D_801D3A58;
    D_801D3A58 = quad + 1;
    colour0 = &quad->colour0;
    colour1 = &quad->colour1;
    colour2 = &quad->colour2;
    colour3 = &quad->colour3;
    height = height * 80 >> 12;
    quad->x0 = 0;
    quad->y0 = height - 80;
    quad->x1 = 320;
    quad->y1 = height - 80;
    quad->x2 = 0;
    quad->y2 = height;
    quad->x3 = 320;
    quad->y3 = height;
    setlen(quad, 8);
    *colour0 = *colour1 = 0x404040;
    *colour2 = *colour3 = 0;
    setcode(quad, 0x3A);
    addPrim(ot, quad);
    quad = D_801D3A58;
    D_801D3A58 = quad + 1;
    colour0 = &quad->colour0;
    colour1 = &quad->colour1;
    colour2 = &quad->colour2;
    colour3 = &quad->colour3;
    quad->x0 = 0;
    quad->y0 = 216 - height;
    quad->x1 = 320;
    quad->y1 = 216 - height;
    quad->x2 = 0;
    quad->y2 = 296 - height;
    quad->x3 = 320;
    quad->y3 = 296 - height;
    *colour0 = *colour1 = 0;
    *colour2 = *colour3 = 0x404040;
    setlen(quad, 8);
    setcode(quad, 0x3A);
    addPrim(ot, quad);
    mode = D_801D3A58;
    D_801D3A58 = mode + 1;
    setlen(mode, 1);
    mode->code[0] = 0xE1000240;
    addPrim(ot, mode);
}

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A7CA8);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A7CE4);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A7D20);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A8538);

INCLUDE_ASM("asm/ovl/effect_274/nonmatchings/effect_274", func_801A86F8);

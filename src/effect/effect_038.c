/**
 * @file effect_038.c
 * @brief Quake
 */
#include "common.h"

#include "psxsdk/libgte.h"

typedef struct {
    /* 0x00 */ SVECTOR vertices[3];
    /* 0x18 */ SVECTOR center;
    /* 0x20 */ u8 pad020[8];
    /* 0x28 */ u8 r;
    /* 0x29 */ u8 g;
    /* 0x2A */ u8 b;
    /* 0x2B */ u8 code;
    /* 0x2C */ u8 shadeR;
    /* 0x2D */ u8 shadeG;
    /* 0x2E */ u8 shadeB;
    /* 0x2F */ u8 shadeCode;
    /* 0x30 */ u16 tpage;
    /* 0x32 */ u16 clut;
    /* 0x34 */ u16 indices[3];
    /* 0x3A */ s16 id;
    /* 0x3C */ u8 pad03C[40];
    /* 0x64 */ u8 u[5];
    /* 0x69 */ u8 v[5];
    /* 0x6E */ u8 active;
    /* 0x6F */ u8 pad06F;
} QuakeTriangle;

typedef struct {
    /* 0x00 */ u16 indices[3];
    /* 0x06 */ u8 u2;
    /* 0x07 */ u8 v2;
    /* 0x08 */ u8 u0;
    /* 0x09 */ u8 v0;
    /* 0x0A */ u16 clut;
    /* 0x0C */ u8 u1;
    /* 0x0D */ u8 v1;
    /* 0x0E */ u16 tpage;
    /* 0x10 */ u8 r;
    /* 0x11 */ u8 g;
    /* 0x12 */ u8 b;
    /* 0x13 */ u8 pad013;
} QuakeTriangleSource;

extern QuakeTriangle *D_801B177C;
extern u16 D_801B1824;

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0000);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0188);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A02D8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0384);

void func_801A03A4(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A03AC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A04A8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A05A4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A05DC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A076C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A08F8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0920);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0AAC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0BE0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0C10);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0C40);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0C70);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0DAC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0DDC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0E0C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A0E3C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1088);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A10D8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A117C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A11AC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1204);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1228);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1270);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A12B8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1370);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A13C4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1430);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1468);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1748);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1A80);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A1E14);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A220C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A2534);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A28D4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A2CA8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A3108);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A335C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A34F0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A3674);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A37F8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A3940);

static void InitQuakeTriangle(s16 index, SVECTOR *vertices, QuakeTriangleSource *source) {
    QuakeTriangle *triangle = &D_801B177C[index];
    s32 a;
    s32 b;
    s32 c;

    triangle->active = 1;
    a = source->indices[0] & 0xFFF;
    b = source->indices[1] & 0xFFF;
    c = source->indices[2] & 0xFFF;
    triangle->id = index + 400;
    triangle->indices[0] = D_801B1824 + a;
    triangle->indices[1] = D_801B1824 + b;
    triangle->indices[2] = D_801B1824 + c;
    triangle->vertices[0].vx = vertices[a].vx;
    triangle->vertices[0].vy = vertices[a].vy;
    triangle->vertices[0].vz = vertices[a].vz;
    triangle->vertices[1].vx = vertices[b].vx;
    triangle->vertices[1].vy = vertices[b].vy;
    triangle->vertices[1].vz = vertices[b].vz;
    triangle->vertices[2].vx = vertices[c].vx;
    triangle->vertices[2].vy = vertices[c].vy;
    triangle->vertices[2].vz = vertices[c].vz;
    triangle->center.vx = (triangle->vertices[0].vx + triangle->vertices[1].vx + triangle->vertices[2].vx) / 3;
    triangle->center.vy = (triangle->vertices[0].vy + triangle->vertices[1].vy + triangle->vertices[2].vy) / 3;
    triangle->center.vz = (triangle->vertices[0].vz + triangle->vertices[1].vz + triangle->vertices[2].vz) / 3;
    triangle->u[0] = source->u0;
    triangle->v[0] = source->v0;
    triangle->u[1] = source->u1;
    triangle->v[1] = source->v1;
    triangle->u[2] = source->u2;
    triangle->v[2] = source->v2;
    triangle->u[3] = (triangle->u[0] + triangle->u[1] + triangle->u[2]) / 3;
    triangle->v[3] = (triangle->v[0] + triangle->v[1] + triangle->v[2]) / 3;
    triangle->clut = source->clut;
    triangle->tpage = source->tpage;
    triangle->r = source->r;
    triangle->g = source->g;
    triangle->b = source->b;
    triangle->code = 0x24;
    triangle->shadeR = source->r * 3 / 5;
    triangle->shadeG = source->g * 3 / 5;
    triangle->shadeB = source->b * 3 / 5;
    triangle->shadeCode = 0x2C;
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A3ECC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A41BC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A43F4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A44E0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A46FC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A4BD0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A4F8C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A52F0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A5A10);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A5AE4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A5B34);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A5C40);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A5CA8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6538);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A66DC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6778);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A67C0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6A5C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6CFC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6EAC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6F10);

void func_801A6F90(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A6F98);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7040);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A729C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A758C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A75E4);

void func_801A763C(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7644);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7794);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A781C);

void func_801A7874(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A787C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A79D0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7C1C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7D94);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7EFC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A7F74);

void func_801A8030(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8038);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A80E0);

void func_801A81F4(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A81FC);

void func_801A82EC(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A82F4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8378);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8624);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8698);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A86D0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8714);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8770);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A88E8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8C38);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8DC0);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8E28);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A8F44);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9154);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9450);

void func_801A95D4(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A95DC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9698);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A96C4);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9710);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A973C);

void func_801A9794(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A979C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A984C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9894);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A98EC);

void func_801A9944(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A994C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A99F8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9AB8);

void func_801A9BA4(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9BAC);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9C5C);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9C70);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9CC8);

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9D18);

void func_801A9D48(void) {
}

INCLUDE_ASM("asm/ovl/effect_038/nonmatchings/effect_038", func_801A9D50);

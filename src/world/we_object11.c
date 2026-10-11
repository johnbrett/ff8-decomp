#include "common.h"
#include "psxsdk/libgte.h"
#include "world.h"
#include "world/we_object10.h"
#include "world/we_object11.h"


typedef struct {
    /* 0x00 */ s16 vert;
    /* 0x02 */ s16 count;
    /* 0x04 */ s16 bone;
    /* 0x06 */ s16 pad06;
} WmPart; /* 0x08 */

typedef struct {
    /* 0x00 */ s16 firstPart;
    /* 0x02 */ s16 partCount;
    /* 0x04 */ u8 pad04[0x0E];
    /* 0x12 */ s16 triCount;
    /* 0x14 */ u8 pad14[0x2];
    /* 0x16 */ s16 quadCount;
    /* 0x18 */ u8 pad18[0x8];
} WmGroup; /* 0x20 */

typedef struct {
    /* 0x00 */ s16 verts[3];
    /* 0x06 */ u8 pad06[0x12];
} WmTri; /* 0x18 */

typedef struct {
    /* 0x00 */ s16 verts[4];
    /* 0x08 */ u8 pad08[0x14];
} WmQuad; /* 0x1C */

typedef struct {
    /* 0x00 */ u8 pad00[0x0C];
    /* 0x0C */ WmTri *tris;
    /* 0x10 */ WmQuad *quads;
    /* 0x14 */ u8 pad14[0x4];
    /* 0x18 */ SVECTOR *verts;
    /* 0x1C */ WmGroup *groups;
    /* 0x20 */ WmPart *parts;
    /* 0x24 */ s32 groupCount;
    /* 0x28 */ u8 pad28[0x8];
    /* 0x30 */ s32 g3Count;  // Packet section sizes, see WmModel.packets
    /* 0x34 */ s32 g4Count;
    /* 0x38 */ s32 ft3Count;
} WmModelData;

typedef struct {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ MATRIX mat;
    /* 0x34 */ u8 pad34[0xC];
} WmBone; /* 0x40 */

typedef struct {
    /* 0x00 */ WmModelData *data;
    /* 0x04 */ WmBone *bones;
    /* 0x08 */ u8 pad08[0x4C];
    /* 0x54 */ POLY_G3 *packets; // POLY_G3, POLY_G4, POLY_FT3 then POLY_FT4 sections back to back
} WmModel;

// Start of the POLY_FT3 and POLY_FT4 packet sections of a model.
#define WM_FT3_PACKETS(m) ((POLY_FT3 *)((POLY_G4 *)((m)->packets + (m)->data->g3Count) + (m)->data->g4Count))
#define WM_FT4_PACKETS(m) ((POLY_FT4 *)(WM_FT3_PACKETS(m) + (m)->data->ft3Count))

// Private prototypes
static void DrawSkinnedModel(s32 *ot, s32 arg1, WmModel **model);
static void SetRenderSlotScale(s32 idx, WorldRenderScale *vals, s32 mode);
static s32 ClaimObjectSlot(s32 idx, s32 arg1, WorldObjectSlot *slot);
static s32 *ClaimRenderSlot(s32 idx, s32 firstWord, LookupTarget *slot);
static u8 *func_800C22B0(s32 idx, u32 mode);
void func_800C3278(s32 *ot, s32 arg1);
void func_800C3674(SVECTOR *verts, s32 *sxy, s16 *sz, s32 count);
void func_800C3714(POLY_FT3 *pkt, WmTri *tris, s32 *ot, s32 count);
void func_800C3918(POLY_FT4 *pkt, WmQuad *quads, s32 *ot, s32 count);

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BF80C);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800BFBFC);

// The only caller passes D_800D244C->primList. Each level hands the next
// element on, so the packet builders link into primList[2] onward.
void func_800BFCC0(s32 *ot, s32 arg1) {
    s32 i;

    for (i = 0; i < WORLD_RENDER_SLOT_COUNT; i++) {
        D_800DD8F8[i] = D_800DDB00[i];
    }
    func_800C3278(&ot[1], arg1);
}

static void DrawSkinnedModel(s32 *ot, s32 arg1, WmModel **model) {
    s32 i;
    s32 k;
    s32 g;
    u16 tri;
    u16 quad;

    tri = 0;
    quad = 0;
    for (g = 0; g < (*model)->data->groupCount; g++) {
        k = 0;
        for (i = (*model)->data->groups[g].firstPart;
             i < (*model)->data->groups[g].firstPart + (*model)->data->groups[g].partCount; i++) {
            SetRotMatrix(&(*model)->bones[(*model)->data->parts[i].bone].mat);
            SetTransMatrix(&(*model)->bones[(*model)->data->parts[i].bone].mat);
            func_800C3674(&(*model)->data->verts[(*model)->data->parts[i].vert], &D_800DDB80[k], &D_800E1E58[k],
                          (*model)->data->parts[i].count);
            k += (*model)->data->parts[i].count;
        }
        func_800C3714(WM_FT3_PACKETS(*model) + tri,
                      &(*model)->data->tris[tri], &ot[1], (*model)->data->groups[g].triCount);
        tri += (*model)->data->groups[g].triCount;
        func_800C3918(WM_FT4_PACKETS(*model) + quad,
                      &(*model)->data->quads[quad], &ot[1], (*model)->data->groups[g].quadCount);
        quad += (*model)->data->groups[g].quadCount;
    }
}

void ResetWorldRenderState(void) {
    s32 i;

    for (i = WORLD_OBJECT_SLOT_COUNT - 1; i >= 0; i--) {
        D_800E1D58[i] = NULL;
    }
    for (i = WORLD_RENDER_SLOT_COUNT - 1; i >= 0; i--) {
        D_800DDB00[i] = NULL;
    }

    SetFarColor(0, 60, 120);
    SetFogFar(2048, 512);
    SetFogNear(512, 512);
    SetColorMatrix(&D_800C5DB8);
    SetLightMatrix(&D_800C5DD8);
}

void func_800C0084(s32 idx, WorldSlotVec4 *vals, s32 mode) {
    LookupTarget *slot;

    switch (mode) {
    case 0:
        D_800DDB00[idx]->vec10 = *vals;
        slot = D_800DDB00[idx];
        break;
    case 1:
        D_800DDB00[idx]->vec10.vx += vals->vx;
        D_800DDB00[idx]->vec10.vy += vals->vy;
        D_800DDB00[idx]->vec10.vz += vals->vz;
        slot = D_800DDB00[idx];
        break;
    default:
        return;
    }
    slot->flags &= ~(WORLD_SLOT_FLAG_UNK08 | WORLD_SLOT_FLAG_UNK10);
}

void func_800C0154(s32 idx, WorldSlotVec4 *vals, s32 mode) {
    LookupTarget *slot;

    switch (mode) {
    case 0:
        D_800DDB00[idx]->vec18 = *vals;
        slot = D_800DDB00[idx];
        break;
    case 1:
        D_800DDB00[idx]->vec18.vx += vals->vx;
        D_800DDB00[idx]->vec18.vy += vals->vy;
        D_800DDB00[idx]->vec18.vz += vals->vz;
        slot = D_800DDB00[idx];
        break;
    default:
        return;
    }
    slot->flags &= ~(WORLD_SLOT_FLAG_UNK08 | WORLD_SLOT_FLAG_UNK10);
}

// mode 0 sets the scale, mode 1 adds to x/y/z.
static void SetRenderSlotScale(s32 idx, WorldRenderScale *vals, s32 mode) {
    LookupTarget *slot;

    switch (mode) {
    case 0:
        slot = D_800DDB00[idx];
        slot->scale = *vals;
        break;
    case 1:
        D_800DDB00[idx]->scale.x += vals->x;
        D_800DDB00[idx]->scale.y += vals->y;
        D_800DDB00[idx]->scale.z += vals->z;
        break;
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C02D8);

static s32 ClaimObjectSlot(s32 idx, s32 arg1, WorldObjectSlot *slot) {
    if (D_800E1D58[idx] != NULL) {
        return 0;
    }
    D_800E1D58[idx] = slot;
    slot->unk44 = 0;
    return func_800C02D8(arg1, 0x11, idx, idx);
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C0D00);

static s32 *ClaimRenderSlot(s32 idx, s32 firstWord, LookupTarget *slot) {
    if (D_800DDB00[idx] != NULL) {
        return NULL;
    }
    D_800DDB00[idx] = slot;
    slot->firstWord = firstWord;
    D_800DDB00[idx]->flags = 0;
    D_800DDB00[idx]->vec10.vx = 0;
    D_800DDB00[idx]->vec10.vy = 400;
    D_800DDB00[idx]->vec10.vz = 0;
    D_800DDB00[idx]->vec18.vx = 0;
    D_800DDB00[idx]->vec18.vy = 0;
    D_800DDB00[idx]->vec18.vz = 0;
    D_800DDB00[idx]->scale.x = 0x1000;
    D_800DDB00[idx]->scale.y = 0x1000;
    D_800DDB00[idx]->scale.z = 0x1000;
    D_800DDB00[idx]->unk50 = 0;
    D_800DDB00[idx]->field52 = 0;
    D_800DDB00[idx]->flags = 0;
    return &slot->subBuffer;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C17E4);

// Any other mode returns an unset pointer, as the original does.
static u8 *func_800C22B0(s32 idx, u32 mode) {
    u8 *result;

    switch (mode) {
    case 0x1C:
        result = D_800DDB00[idx]->data->parts[D_800DDB00[idx]->unk70].unk0C;
        break;
    case 0x1D:
        result = D_800DDB00[idx]->data->parts[D_800DDB00[idx]->unk71].unk0C;
        break;
    case 0x1E:
        result = D_800DDB00[idx]->data->parts[D_800DDB00[idx]->unk71].unk28;
        break;
    case 0x1F:
        result = D_800DDB00[idx]->unk30;
        break;
    }
    return result;
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C239C);

void func_800C2B04(s32 idx, s32 mode, u32 count) {
    LookupTarget *slot = D_800DDB00[idx];
    s32 sum;
    s32 prodSum;
    s32 j;
    u32 i;

    if (slot->firstWord != -1) {
        j = 2;
        if (mode == 0xD) {
            prodSum = 0;
            sum = 0;
            for (i = 0; i < count; i++) {
                sum += slot->unk68[j - 2];
                prodSum += slot->unk68[j - 2] * slot->unk68[j - 1];
                j += 2;
            }
            D_800DDB00[idx]->unk0C = D_800DDB00[idx]->unk68[j - 2] * 16;
            D_800DDB00[idx]->unk0E = D_800DDB00[idx]->unk68[j - 1];
            D_800DDB00[idx]->unk08 = D_800DDB00[idx]->unk6C + (prodSum + sum);
            D_800DDB00[idx]->unk50 = 0;
        }
    }
}

INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C2C00);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3278);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3674);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3714);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3918);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3B74);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3CE4);
INCLUDE_ASM("asm/ovl/world/nonmatchings/we_object11", func_800C3DB0);

#ifndef WORLD_WE_OBJECT6_H
#define WORLD_WE_OBJECT6_H

#include "world.h"
#include "world/we_object3.h"
#include "world/we_object2.h"

extern void func_800ACC68(MATRIX *outMat, SVECTOR *angles, SVECTOR *rotBuf,
                          SVECTOR *offset);

extern void func_800AD698(SceneState *st, u8 *flags);
extern void InitActors(u8 *flags);
extern s32  func_800AE518(u8 *flags);
extern void func_800AEB58(ActorSegment *part, ActorRecord *actor);
extern void func_800AEEB0(u8 *flags, void *a, void *b, void *c);
extern void func_800B04CC(SVECTOR *ang, MATRIX *m, u8 *flags, s32 *modelBank);
extern void InitPlayerPosition(SceneState *st, Slot *slot, u8 *flags, VECTOR *pos);
extern void SyncSlotsToPlayer(u8 *flags, VECTOR *pos, SVECTOR *ang);
extern s32  func_800B1BCC(u8 *p);

extern s32 func_800B0010(u32 kind);
extern s32 func_800B00D8(u32 kind);

extern void func_800ACD38(MATRIX *outMat);

/* Projects @p pos to screen space in @p screenOut and returns a status of
   -1, 0 or 1. @p byteOut and @p halfOut are optional outputs; both are
   NULL-checked. */
extern s32 func_800B01A0(s16 viewY, s16 viewX, VECTOR *pos, SVECTOR *screenOut,
                         s8 *byteOut, s16 *halfOut);

extern void func_800ACDC4(GlyphHeader *p, BattleSceneCtx *ctx, WorldPrimBank *pools);

extern ScriptOp *func_800AF004(u8 *base, s32 flag);

extern s32 func_800B21EC(WorldSpriteRec *rec, s32 mode, s32 c, s32 d);

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
} SpawnPoint;

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s16 z;
    /* 0x0A */ u8 cameraYaw;
    /* 0x0B */ u8 playerHeading;
} WorldSpawn;

typedef struct {
    /* 0x00 */ u8 unk00[16];
    /* 0x10 */ SVECTOR unk10;
    /* 0x18 */ SVECTOR unk18;
} WorldHitTransform;

extern s32 func_800B2B6C(SlotEntry *slot, SlotEntry *target, s32 mode);
extern s32 func_800B2F5C(SVECTOR *quad, WorldHitTransform *xf, SVECTOR *pts);

extern SpawnPoint *D_800CA034;
extern WorldSpawn *D_800D2120;
extern VECTOR D_800C5C08; // Fixed translation of the 0x5E marker
extern s32 D_800C5C34; // Slot index of the 0x5E marker placement
extern u8 D_800D243F;
extern ActorSegment D_800DD6F0[]; // Part pool shared by both actor records

#endif /* WORLD_WE_OBJECT6_H */

#ifndef WORLD_WE_OBJECT10_H
#define WORLD_WE_OBJECT10_H

#include "common.h"
#include "world.h"
#include "world/we_object3.h"
#include "psxsdk/libgte.h"


extern u8             D_800DCE78[];
extern s32            D_800C5DAC;
extern LookupTarget  *D_800DDB00[];
extern u8            *D_800C9E34;

extern void func_800BAC84(u8 *p);
extern s32  func_800BA870(u8 *p);
extern s32 func_800BEF6C(void);
extern void func_8009C5FC(s32 *data);

extern void UpdateActorCameraDistance(u8 *flags);
extern s32 func_800BD754(s32 marker);
extern s32 RegisterSceneObject(WorldObjList *actor, SlotEntry *slot, s32 marker, s32 flag, SVECTOR *rot, VECTOR *trans);
extern s32 func_800BDEF4(SlotEntry *input, s32 kind, s32 high);
extern void func_800BE040(void);
extern s32 func_800BE720(ActorRecord *group);
extern s32 func_800BD998(u32 mapId);
extern s32 func_800BE958(void);
extern s32 func_800BE5F8(KeyframeNode *list);
extern void func_800BE4D8(VECTOR *a, VECTOR *b, s32 t, VECTOR *out);

extern void func_800BF20C(CmdDesc *p, s32 kind, s32 arg);
extern void func_800BF2E8(GlyphHeader *p, s32 *ot, WorldPrimBank *pools);

#endif /* WORLD_WE_OBJECT10_H */

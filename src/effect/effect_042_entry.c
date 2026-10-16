/**
 * @file effect_042_entry.c
 * @brief Shoot: the overlay entry point.
 */
#include "common.h"
#include "effect/effect_042_entry.h"
#include "effect/lib/entity.h"
#include "effect/lib/tables.h"
#include "battle/bc_object9.h"
#include "battle/bc_object11.h"

#define EFFECT_BANK_SIZE 24576

extern s32 D_801DC5A0;
extern s32 D_801DC5A4;
extern s32 D_801DCEC0;
extern u8 D_801DCDF0[];
extern u8 D_801B2EC4[];
extern u8 D_801B30F8[];
extern u8 *D_801DC5B0;
extern u8 *D_801DCDD8;
extern u8 *D_801DCDDC;
extern u8 *D_801DCDE0;
extern u8 *D_801DCDE4;
extern s32 D_801DD030;
extern u8 D_801DCED0[];
extern u8 D_801DC5D0[];
extern s32 D_801E9B90;
extern u8 D_801E90A0[];
extern s32 D_801E2300;
extern u8 D_801DD3A0[];
s32 func_801AE290(EffectEntity *entity);

void *func_801A0000(EffectAnimSet *animSet) {
    u8 *bank0;
    EffectEntity *entity;
    u8 *bank1;
    u8 *frames;

    D_801DC5A0 = 0;
    D_801DC5A4 = 0;
    func_800B2A00(&D_801DCEC0, D_801DCDF0, 100, 2);
    entity = effectSpawnTask(&D_801DCEC0, func_801AE290, 100, NULL);
    entity->animSet = animSet;
    entity->unk02C = animSet->anims[entity->unk02A].unk000;
    entity->unk02D =
        entity->animSet->anims[entity->unk02A].parts[entity->unk02B].unk000;
    entity->pc = 0;
    entity->unk05A = animSet->anims->unk010;
    entity->unk058 = animSet->anims->unk011;
    entity->unk02F = entity->unk05A - 1;
    if (entity->unk02F < entity->unk058) {
        entity->unk02F = entity->unk058;
    }
    if (!(animSet->flags & EFFECT_ANIMSET_FLAG_LOADED)) {
        func_800C3BE0(D_801B2EC4);
        func_800BB084(D_801B30F8);
    }
    D_801DC5B0 = D_801B30F8;
    bank0 = D_801B30F8;
    D_801DCDD8 = bank0;
    bank1 = bank0 + EFFECT_BANK_SIZE;
    D_801DCDE0 = bank0 + EFFECT_BANK_SIZE;
    D_801DC5B0 = bank0 + EFFECT_BANK_SIZE;
    frames = bank1;
    D_801DCDDC = frames;
    frames += EFFECT_BANK_SIZE;
    D_801DC5B0 = frames;
    D_801DCDE4 = frames;
    func_800B2A00(&D_801DD030, D_801DCED0, 88, 4);
    func_800B2A00(&g_effectChildPool, D_801DC5D0, 676, 3);
    func_800B2A00(&D_801E9B90, D_801E90A0, 280, 10);
    func_800B2A00(&D_801E2300, D_801DD3A0, 508, 40);
    return &D_801DCEC0;
}

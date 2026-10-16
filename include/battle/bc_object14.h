#ifndef BATTLE_BC_OBJECT14_H
#define BATTLE_BC_OBJECT14_H

#include "common.h"

/**
 * @file
 * @brief Battle sound-effect callbacks.
 */

/** @brief Clear @c D_800F1B90 and register the callback with mode 1. */
void func_800C5304(s32 a0, s32 a1);

/** @brief Look up a word from the @c D_800E662C array. */
s32 func_800C6B1C(s32 idx);

struct BattleEffectSlot;
s32 func_800C5A34(struct BattleEffectSlot *slot, s32 command, s32 flags);

#endif /* BATTLE_BC_OBJECT14_H */

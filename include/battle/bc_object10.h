#ifndef BATTLE_BC_OBJECT10_H
#define BATTLE_BC_OBJECT10_H


/**
* @file
* @brief Battle audio list structures.
*/
SoundCmd* func_800B8564(s16, u8);

/** @brief Initialize a linked-list array of @p count entries at @p a0. */
void func_800B8870(u8 *a0, s32 count);

/** @brief Allocate a handler for @c func_800B8BEC and store its parameters. */
void func_800B8F4C(s32 a0);

s32 BuildBattleDirectionBasis(VECTOR *input, MATRIX *matrix);
void MoveBattleCameraOutward(s32 distance);
void UpdateBattleCameraMatrix(void);
void ResetBattleCameraTasks(void);
SVECTOR *InterpolateBattleVector(s16 value, s16 *knots, s16 *valuesX, s16 *valuesY,
                                s16 *valuesZ, s32 count, float *tangentsX,
                                float *tangentsY, float *tangentsZ, SVECTOR *result);

#endif /* BATTLE_BC_OBJECT10_H */

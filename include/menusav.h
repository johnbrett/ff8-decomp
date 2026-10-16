#ifndef MENUSAV_H
#define MENUSAV_H

#include "common.h"

extern void func_801E7190(void); /**< Save-point save menu. */
extern void func_801E7268(void); /**< Title menu: NEW GAME / Continue (screen 0x10). */
typedef struct {
    /* 0x00 */ u8 pad00[88];
    /* 0x58 */ u8 unk58;
} SaveMenuParams;

void func_801EAD28(SaveMenuParams *);

#endif /* MENUSAV_H */

#include "common.h"
#include "sound.h"
#include "snd_bank.h"
#include "snd_note.h"

extern s16 D_8007507A;
/**
 * @brief Sets the CD audio input volume on the SPU to the current global value.
 *
 * Reads the volume level from D_8007507A and writes it to both the left
 * (0x1F801DB0) and right (0x1F801DB2) CD audio volume registers, producing
 * equal stereo volume.
 */
void sndSetCdVolume(void) {
    s32 val = D_8007507A;
    *(s16 *)0x1F801DB0 = val;
    *(s16 *)0x1F801DB2 = val;
}

void CopySoundWords(s32 *src, s32 *dst, u32 bytes) {
    bytes >>= 2;

    while (bytes >> 2) {
        s32 word0 = src[0];
        s32 word1 = src[1];
        s32 word2 = src[2];
        s32 word3 = src[3];

        dst[0] = word0;
        dst[1] = word1;
        dst[2] = word2;
        dst[3] = word3;
        src += 4;
        dst += 4;
        bytes -= 4;
    }
    while (bytes != 0) {
        *dst++ = *src++;
        bytes--;
    }
}

void SwapSoundWords(s32 *first, s32 *second, u32 bytes) {
    s32 first0;
    s32 second0;
    s32 first1;
    s32 second1;

    bytes >>= 2;

    while (bytes >> 1) {
        first0 = first[0];
        second0 = second[0];
        first1 = first[1];
        second1 = second[1];

        second[0] = first0;
        second[1] = first1;
        first[0] = second0;
        first[1] = second1;
        first += 2;
        second += 2;
        bytes -= 2;
    }
    if (bytes != 0) {
        first0 = first[0];
        second0 = second[0];

        second[0] = first0;
        first[0] = second0;
    }
}

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001A674);

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001AA28);

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
} UnkStruct80074F10;

extern UnkStruct80074F10 D_80074F10;

void func_8001ACCC(SoundSeqTrack *track, SoundSeqTrack *tracks) {
    s32 savedUnk04;
    s32 newVal;

    if (D_80074F10.unk08 != 0) {
        if (--D_80074F10.unk08 == 0) {
            savedUnk04 = track->work.params.instParams;
            track->field5E = 0;
            track->work.params.instParams = 0;
            track->work.params.voiceIdx = 0;
            track->field14 = 0;
            track->field18 = savedUnk04;
        } else {
            newVal = D_80074F10.unk00 + D_80074F10.unk04;

            if ((newVal & 0xFFFF0000) != (D_80074F10.unk00 & 0xFFFF0000)) {
                func_80017D14(track, tracks);
            }

            D_80074F10.unk00 = newVal;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001AD60);

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001B1F4);

/**
 * @brief Adjusts a note/instrument value based on a flag and range check.
 *
 * If bit 10 of @p a0 is set and @p a1 is in range [0x40, 0x80), adds 0x20
 * to @p a1 (shifting the value into a higher register/octave).
 *
 * @param a0 Flags value; bit 10 enables the adjustment.
 * @param a1 Note or instrument index to potentially adjust.
 * @return Adjusted value, or @p a1 unchanged if conditions are not met.
 */
s32 sndAdjustNoteOctave(s32 a0, s32 a1) {
    if ((a0 & 0x400) && (u32)a1 >= 0x40 && (u32)a1 < 0x80) {
        return a1 + 0x20;
    }
    return a1;
}

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001B42C);

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001B690);

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001B820);

INCLUDE_ASM("asm/nonmatchings/snd_note", func_8001BAA8);

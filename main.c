#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "song.h"

#include "lib/tsf.h"

static int WHITE_NOTES[52] = {
    A0, B0, C1, D1, E1, F1, G1,
    A1, B1, C2, D2, E2, F2, G2,
    A2, B2, C3, D3, E3, F3, G3,
    A3, B3, C4, D4, E4, F4, G4,
    A4, B4, C5, D5, E5, F5, G5,
    A5, B5, C6, D6, E6, F6, G6,
    A6, B6, C7, D7, E7, F7, G7,
    A7, B7, C8,
};
static int BLACK_NOTES[36] = {
    AS0, CS1, DS1, FS1, GS1,
    AS1, CS2, DS2, FS2, GS2,
    AS2, CS3, DS3, FS3, GS3,
    AS3, CS4, DS4, FS4, GS4,
    AS4, CS5, DS5, FS5, GS5,
    AS5, CS6, DS6, FS6, GS6,
    AS6, CS7, DS7, FS7, GS7,
    AS7,
};

void write_invention_4(tsf *soundfont) {
    Song song;
    //        SONG   SOUNDFONT  BEATS/MEASURE  BPM     MEASURES
    song_init(&song, soundfont, 3,             100.0f, 26);

    int piano = 0;

    // Measures 1-5
    // ====================================================

    float u = 1.0; // upper
    float o = 1.0; // lower
    song_note(&song, piano, D4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, A4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, BF4, 0.5, u, 1.0); u += 1.0/4;
    o += 1.5;

    song_note(&song, piano, CS4, 0.5, u, 1.0); u += 1.0/4;
    song_note(&song, piano, BF4, 0.5, u, 1.0); u += 1.0/4;
    song_note(&song, piano, A4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E4, 0.5,  u, 1.0); u += 1.0/4;
    o += 1.5;

    song_note(&song, piano, F4, 0.5, u, 1.0); u += 1.0/2;
    song_note(&song, piano, A4, 0.5, u, 1.0); u += 1.0/2;
    song_note(&song, piano, D5, 0.5, u, 1.0); u += 1.0/2;
    song_note(&song, piano, D3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, E3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, F3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, BF3, 0.5, o, 1.0); o += 1.0/4;

    song_note(&song, piano, G4, 0.5, u, 1.0); u += 1.0/2;
    song_note(&song, piano, CS5, 0.5, u, 1.0); u += 1.0/2;
    song_note(&song, piano, E5, 0.5, u, 1.0); u += 1.0/2;
    song_note(&song, piano, CS3, 0.5, o, 1.0); o += 1.0/4;
    song_note(&song, piano, BF3, 0.5, o, 1.0); o += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, F3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, E3, 0.5,  o, 1.0); o += 1.0/4;

    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, A5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, BF5, 0.5, u, 1.0); u += 1.0/4;
    song_note(&song, piano, F3, 0.5, o, 1.0); o += 1.0/2;
    song_note(&song, piano, A3, 0.5, o, 1.0); o += 1.0/2;
    song_note(&song, piano, D4, 0.5, o, 1.0); o += 1.0/2;

    // Measures 6-10
    // ====================================================

    song_note(&song, piano, CS5, 0.5, u, 1.0); u += 1.0/4;
    song_note(&song, piano, BF5, 0.5, u, 1.0); u += 1.0/4;
    song_note(&song, piano, A5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E3, 0.5, o, 1.0); o += 1.0/2;
    song_note(&song, piano, G3, 0.5, o, 1.0); o += 1.0/2;
    song_note(&song, piano, CS4, 0.5, o, 1.0); o += 1.0/2;

    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, A5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D3, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, D4, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, F3, 0.5,  o, 1.0); o += 1.0/2;

    song_note(&song, piano, BF4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, A5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, BF3, 0.5,  o, 1.0); o += 1.0/2;

    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, C5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, C3, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, C4, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, E3, 0.5,  o, 1.0); o += 1.0/2;

    song_note(&song, piano, A4, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, G5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, C5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F3, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/2;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/2;

    // Measures 11-15
    // ====================================================

    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, F5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, BF3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, BF3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, C4, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, D4, 0.5,  o, 1.0); o += 1.0/4;

    song_note(&song, piano, G4, 0.5,  u, 1.0); u += 1.0/2;
    u += 1.0/2;
    u += 1.0/2;
    song_note(&song, piano, E3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, D4, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, C4, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, BF3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/4;

    song_note(&song, piano, C5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, C5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, D5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, E5, 0.5,  u, 1.0); u += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, F3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, BF3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, C4, 0.5,  o, 1.0); o += 1.0/4;

    song_note(&song, piano, F4, 0.5,  u, 1.0); u += 1.0/2;
    u += 1.0/2;
    song_note(&song, piano, BF4, 0.5,  u, 1.0); u += 1.0/1;
    song_note(&song, piano, D3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, C4, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, BF3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, A3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, G3, 0.5,  o, 1.0); o += 1.0/4;
    song_note(&song, piano, F3, 0.5,  o, 1.0); o += 1.0/4;

    song_write(&song, "test.wav");
}

#define NOTES 7

int main(int argc, char **argv) {
    srand(time(NULL));
    tsf *soundfont = tsf_load_filename("/home/paul/Downloads/soundfonts/sal/SalC5Light2.sf2");
    /* write_invention_4(soundfont); */
    // ============================================================

    Song song;
    song_init(&song, soundfont, 3, 100.0f, 8);
    int piano = 0;

    int notes[NOTES] = {C4, D4, E4, F4, G4, A4, B4};
    /* int notes[NOTES]; */
    /* for (int i = 0; i < NOTES; i++) { */
    /*     notes[i] = (i * ) % NOTES + 33; */
    /* } */

    float o = 1.0;
    int offsets[3] = {2, 4, 8};
    for (int i = 0; i < 32; i++) {

        int offset = offsets[rand() % 2];
        song_note(&song, piano, notes[rand()%NOTES], 0.5, o, 1.0); o += 1.0/offset;
    }

    song_write(&song, "test.wav");

    // ============================================================
    return 0;
}

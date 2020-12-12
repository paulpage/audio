#include <stdbool.h>
#include <stdint.h>

#include "song.h"

#define TSF_IMPLEMENTATION
#include "lib/tsf.h"

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

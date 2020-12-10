#include <stdbool.h>
#include <stdint.h>

#define TSF_IMPLEMENTATION
#include "lib/tsf.h"

#define NUM_CHANNELS 2
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

#define A0  21
#define AS0 22
#define BF0 22
#define B0  23
#define C1  24
#define CS1 25
#define DF1 25
#define D1  26
#define DS1 27
#define EF1 27
#define E1  28
#define F1  29
#define FS1 30
#define GF1 30
#define G1  31
#define GS1 32
#define AF1 32

#define A1  33
#define AS1 34
#define BF1 34
#define B1  35
#define C2  36
#define CS2 37
#define DF2 37
#define D2  38
#define DS2 39
#define EF2 39
#define E2  40
#define F2  41
#define FS2 42
#define GF2 42
#define G2  43
#define GS2 44
#define AF2 44

#define A2  45
#define AS2 46
#define BF2 46
#define B2  47
#define C3  48
#define CS3 49
#define DF3 49
#define D3  50
#define DS3 51
#define EF3 51
#define E3  52
#define F3  53
#define FS3 54
#define GF3 54
#define G3  55
#define GS3 56
#define AF3 56

#define A3  57
#define AS3 58
#define BF3 58
#define B3  59
#define C4  60
#define CS4 61
#define DF4 61
#define D4  62
#define DS4 63
#define EF4 63
#define E4  64
#define F4  65
#define FS4 66
#define GF4 66
#define G4  67
#define GS4 68
#define AF4 68

#define A4  69
#define AS4 70
#define BF4 70
#define B4  71
#define C5  72
#define CS5 73
#define DF5 73
#define D5  74
#define DS5 75
#define EF5 75
#define E5  76
#define F5  77
#define FS5 78
#define GF5 78
#define G5  79
#define GS5 80
#define AF5 80

#define A5  81
#define AS5 82
#define BF5 82
#define B5  83
#define C6  84
#define CS6 85
#define DF6 85
#define D6  86
#define DS6 87
#define EF6 87
#define E6  88
#define F6  89
#define FS6 90
#define GF6 90
#define G6  91
#define GS6 92
#define AF6 92

#define A6  93
#define AS6 94
#define BF6 94
#define B6  95
#define C7  96
#define CS7 97
#define DF7 97
#define D7  98
#define DS7 99
#define EF7 99
#define E7  100
#define F7  101
#define FS7 102
#define GF7 102
#define G7  103
#define GS7 104
#define AF7 104

#define A7  105
#define AS7 106
#define BF7 106
#define B7  107
#define C8  108

typedef struct {
    // Header
    char group_id[4];
    uint32_t file_length;
    char riff_type[4];

    // Format Chunk
    char fmt_group_id[4];
    uint32_t fmt_chunk_size;
    uint16_t format_tag;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;

    // Data Chunk
    char data_group_id[4];
    uint32_t data_chunk_size;
} WavHeader;

WavHeader get_wav_header(
        uint32_t size,
        uint32_t sample_rate,
        uint16_t num_channels,
        uint16_t bits_per_sample)
{
    uint16_t block_align = num_channels * bits_per_sample / 8;
    uint32_t byte_rate = sample_rate * block_align;

    WavHeader wav = {
        // Header
        .group_id = {'R','I','F','F'},
        .file_length = 36 + size * block_align,
        .riff_type = {'W','A','V','E'},
        
        // Format Chunk
        .fmt_group_id = {'f','m','t',' '},
        .fmt_chunk_size = 2 * sizeof(uint32_t) + 4 * sizeof(uint16_t),
        .format_tag = 1,
        .num_channels = num_channels,
        .sample_rate = sample_rate,
        .byte_rate = byte_rate,
        .block_align = block_align,
        .bits_per_sample = bits_per_sample,

        // Data Chunk
        .data_group_id = {'d','a','t','a'},
        .data_chunk_size = size * block_align,
    };

    return wav;
}

typedef struct {
    float top;
    float bottom;
} Fraction;

Fraction frac(float top, float bottom) {
    Fraction f = {top, bottom};
    return f;
}

typedef struct {
    tsf *soundfont;
    uint16_t num_channels;
    uint32_t num_samples;
    uint32_t sample_rate;
    uint32_t bits_per_sample;
    int16_t *samples;
    int beats_per_measure;
    float bpm;
    int measures;
} Song;

void song_init(Song *song, tsf *soundfont, int beats_per_measure, float bpm, int measures) {
    int mode = (NUM_CHANNELS == 1
            ? TSF_MONO
            : TSF_STEREO_INTERLEAVED);


    song->soundfont = soundfont;
    tsf_set_output(song->soundfont, mode, SAMPLE_RATE, 0);

    song->num_channels = NUM_CHANNELS;
    song->sample_rate = SAMPLE_RATE;
    song->num_samples = measures * beats_per_measure
        * song->num_channels * song->sample_rate
        * 60.0f / bpm;
    song->bits_per_sample = BITS_PER_SAMPLE;
    song->samples = malloc(sizeof(int16_t) * song->num_samples);
    song->beats_per_measure = beats_per_measure;
    song->bpm = bpm;
    song->measures = measures;
}

void song_write(Song *song, char *filename) {
    WavHeader header = get_wav_header(
            song->num_samples,
            song->sample_rate,
            song->num_channels,
            song->bits_per_sample);
    FILE *f = fopen(filename, "wb");
    fwrite(&header, sizeof(WavHeader), 1, f);
    fwrite(song->samples, sizeof(int16_t), song->num_samples, f);
    fclose(f);
}

void song_note(
        Song *song,
        int preset,
        int key,
        float vel,
        float beat,
        float duration)
{

    float samples_per_beat = song->sample_rate / (song->bpm / 60.0);
    uint32_t offset = (beat - 1.0) * samples_per_beat;
    uint32_t duration_samples = duration * samples_per_beat;
    tsf_note_on(song->soundfont, preset, key, vel);
    tsf_render_short(song->soundfont, song->samples + offset * song->num_channels, duration_samples, 1);
    tsf_note_off(song->soundfont, preset, key);

#if 0
    float beats_into_the_song = (measure - 1) * song->beats_per_measure + (song->beats_per_measure * (beat.top - 1) / beat.bottom);
    float beats_per_second = song->bpm / 60.0f; // TODO
    float seconds_into_the_song = beats_into_the_song / beats_per_second;
    uint32_t sample_offset = seconds_into_the_song * song->num_channels * song->sample_rate;
    uint32_t duration_val = song->beats_per_measure * duration.top * song->sample_rate / duration.bottom / beats_per_second;
    tsf_note_on(song->soundfont, preset, key, vel);
    tsf_render_short(song->soundfont, song->samples + sample_offset, duration_val, 1);
    tsf_note_off(song->soundfont, preset, key);
#endif
}

int main(int argc, char **argv) {

    tsf *soundfont = tsf_load_filename("/home/paul/Downloads/soundfonts/sal/SalC5Light2.sf2");
    /* tsf *soundfont = tsf_load_filename("/home/paul/Downloads/Grand Piano.sf2"); */


    // SAMPLE USAGE
    // ============================================================
    
    Song song;
    //        SONG   SOUNDFONT  BEATS/MEASURE  BPM     MEASURES
    song_init(&song, soundfont, 3,             100.0f, 26);

    int piano = 0;

#if 0
    //        SONG   INSTRUMENT  NOTE  VELOCITY  MEASURE  BEAT         DURATION 
    song_note(&song, piano,      30,   0.5,     1,       frac(1, 12), frac(1, 4));
    song_note(&song, piano,      31,   0.63,     1,       frac(2, 12), frac(1, 4));
    song_note(&song, piano,      32,   0.50,     1,       frac(3, 12), frac(1, 4));

    song_note(&song, piano,      C4,   0.69,     1,       frac(2, 4), frac(1.2, 4));
    song_note(&song, piano,      F4,   0.63,     1,       frac(2, 4), frac(1.2, 4));
    song_note(&song, piano,      A5,   0.62,     1,       frac(2, 4), frac(1.2, 4));

    song_note(&song, piano,      C4,   0.51,     1,       frac(3, 4), frac(1.2, 4));
    song_note(&song, piano,      E4,   0.63,     1,       frac(3, 4), frac(1.2, 4));
    song_note(&song, piano,      G4,   0.66,     1,       frac(3, 4), frac(1.2, 4));

    song_note(&song, piano,      B4,   0.69,     1,       frac(4, 4), frac(1.2, 4));
    song_note(&song, piano,      F4,   0.55,     1,       frac(4, 4), frac(1.2, 4));
    song_note(&song, piano,      G4,   0.62,     1,       frac(4, 4), frac(1.2, 4));

    song_note(&song, piano,      C4,   0.60,     2,       frac(1, 4), frac(4, 4));
    song_note(&song, piano,      E4,   0.71,     2,       frac(1, 4), frac(4, 4));
    song_note(&song, piano,      G4,   0.69,     2,       frac(1, 4), frac(4, 4));

    //        SONG   INSTRUMENT  NOTE  VELOCITY  BEAT    DURATION 
    song_note(&song, piano,      30,   0.5,     1.0,    1.0);
    song_note(&song, piano,      31,   0.63,     1.333,  1.0);
    song_note(&song, piano,      32,   0.50,     1.667,  1.0);

    song_note(&song, piano,      C4,   0.69,     2.0,    1.2);
    song_note(&song, piano,      F4,   0.63,     2.0,    1.2);
    song_note(&song, piano,      A5,   0.62,     2.0,    1.2);

    song_note(&song, piano,      C4,   0.51,     3.0,    1.2);
    song_note(&song, piano,      E4,   0.63,     3.0,    1.2);
    song_note(&song, piano,      G4,   0.66,     3.0,    1.2);

    song_note(&song, piano,      B4,   0.69,     4.0,    1.2);
    song_note(&song, piano,      F4,   0.55,     4.0,    1.2);
    song_note(&song, piano,      G4,   0.62,     4.0,    1.2);

    song_note(&song, piano,      C4,   0.60,     5.0,    4.0);
    song_note(&song, piano,      E4,   0.71,     5.0,    4.0);
    song_note(&song, piano,      G4,   0.69,     5.0,    4.0);
#endif

    // Measures 1-5
    // ====================================================

    float u = 1.0; // upper
    float o = 1.0; // lOwer
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

    // ============================================================
    return 0;
}

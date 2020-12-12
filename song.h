#include <stdint.h>

#include "lib/tsf.h"

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

#define NUM_CHANNELS 2
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

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

typedef struct {
    float top;
    float bottom;
} Fraction;

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

WavHeader get_wav_header(uint32_t size, uint32_t sample_rate, uint16_t num_channels, uint16_t bits_per_sample);
Fraction frac(float top, float bottom);
void song_init(Song *song, tsf *soundfont, int beats_per_measure, float bpm, int measures);
void song_write(Song *song, char *filename);
void song_note(Song *song, int preset, int key, float vel, float beat, float duration);

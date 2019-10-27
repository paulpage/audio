#include <stdbool.h>
#include <stdint.h>

#define TSF_IMPLEMENTATION
#include "lib/tsf.h"

#define NUM_CHANNELS 2
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16

#define B4 59
#define C4 60
#define E4 64
#define F4 65
#define G4 67
#define A5 69

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
        float measure,
        Fraction beat,
        Fraction duration)
{

    float beats_into_the_song = (measure - 1) * song->beats_per_measure + (song->beats_per_measure * (beat.top - 1) / beat.bottom);
    float beats_per_second = song->bpm / 60.0f; // TODO
    float seconds_into_the_song = beats_into_the_song / beats_per_second;
    uint32_t sample_offset = seconds_into_the_song * song->num_channels * song->sample_rate;
    uint32_t duration_val = song->beats_per_measure * duration.top * song->sample_rate / duration.bottom / beats_per_second;
    tsf_note_on(song->soundfont, preset, key, vel);
    tsf_render_short(song->soundfont, song->samples + sample_offset/*(measure_offset + beat_offset)*/, duration_val, 1);
    tsf_note_off(song->soundfont, preset, key);
}

int main(int argc, char **argv) {

    tsf *soundfont = tsf_load_filename("/usr/share/soundfonts/FluidR3_GM.sf2");


    // SAMPLE USAGE
    // ============================================================
    
    Song song;
    song_init(&song, soundfont, 4, 120.0f, 2);

    int piano = 0;

    /* song.samples[0] = 3; */
    /* printf("%d\n", song.samples[0]); */

    /* tsf_note_on(song.soundfont, piano, C4, 1.0f); */
    /* tsf_render_short(song.soundfont, song.samples, 22050, 0); */
    /* tsf_note_off(song.soundfont, piano, C4); */

    song_note(&song, piano, C4, 0.65, 1, frac(1, 12), frac(1, 4));
    song_note(&song, piano, E4, 0.63, 1, frac(2, 12), frac(1, 4));
    song_note(&song, piano, G4, 0.50, 1, frac(3, 12), frac(1, 4));

    song_note(&song, piano, C4, 0.69, 1, frac(2, 4), frac(1, 4));
    song_note(&song, piano, F4, 0.63, 1, frac(2, 4), frac(1, 4));
    song_note(&song, piano, A5, 0.62, 1, frac(2, 4), frac(1, 4));

    song_note(&song, piano, C4, 0.51, 1, frac(3, 4), frac(1, 4));
    song_note(&song, piano, E4, 0.6343, 1, frac(3, 4), frac(1, 4));
    song_note(&song, piano, G4, 0.66, 1, frac(3, 4), frac(1, 4));

    song_note(&song, piano, B4, 0.69, 1, frac(4, 4), frac(1, 4));
    song_note(&song, piano, F4, 0.55, 1, frac(4, 4), frac(1, 4));
    song_note(&song, piano, G4, 0.62, 1, frac(4, 4), frac(1, 4));

    song_note(&song, piano, C4, 0.60, 2, frac(1, 4), frac(4, 4));
    song_note(&song, piano, E4, 0.71, 2, frac(1, 4), frac(4, 4));
    song_note(&song, piano, G4, 0.69, 2, frac(1, 4), frac(4, 4));

    song_write(&song, "test.wav");
   
    // ============================================================
    return 0;
}

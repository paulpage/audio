#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "song.h"

#define TSF_IMPLEMENTATION
#include "lib/tsf.h"

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

Fraction frac(float top, float bottom) {
    Fraction f = {top, bottom};
    return f;
}


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
    for (int i = 0; i < song->num_samples; i++) {
        song->samples[i] = 0;
    }
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
}

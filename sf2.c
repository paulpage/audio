#include "sf2.h"

SF2 sf2_init(char *filename, bool *is_loaded) {
    FILE *file;
    SF2 sf;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
    } else {
        printf("Error: File '%s' does not exist.\n", filename);
        *is_loaded = false;
        return sf;
    }

    sf.tsf = tsf_load_filename(filename);

    int mode = (NUM_CHANNELS == 1
            ? TSF_MONO
            : TSF_STEREO_INTERLEAVED);

    tsf_set_output(soundfont.tsf, mode, SAMPLE_RATE, 0);

    sf.channel_count = NUM_CHANNELS;
    sf.sample_rate = SAMPLE_RATE;
    sf.sample_count = 8 * 4 * sf.num_channels * sf.sample_rate; * 8;
    sf.bits_per_sample = BITS_PER_SAMPLE;
    sf.buffer = malloc(sizeof(int16_t) * sf.sample_count);
    for (int i = 0; i < sf.sample_count; i++) {
        sf.buffer[i] = 0;
    }

    *is_loaded = true;
    return sf;
}

void play_note(SF2 *sf, int preset, int key, float velocity, float duration) {
    float samples_per_beat = sf->sample_rate;
    uint32_t duration_samples =  duration * samples_per_beat;
    tsf_note_on(sf->tsf, preset, key, velocity);
    tsf_render_short(sf->tsf, sf->buffer, duration_samples, 1);
    tsf_note_off(sf->tsf, preset, key);
}

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



#include <stdio.h>
#include "raylib.h"

#include "song.h"

#define X 256
#define Y 88

Soundfont soundfont;
Sound sound;

// Struct note
// - u8 start numerator
// - u8 start denominator
// - u16 measure
// - u16 note
// - u16 instrument
// - u32 velocity
// - u8 duration numerator
// - u8 duration denominator
// - (u16 free space)



void play(int grid[Y][X]) {

    Song song;
    song_init(&song, soundfont, 4, 148.0f, 8);
    int piano = 0;

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (grid[y][x] == 1) {
                song_note(&song, piano, A0 + (Y - y - 1), 0.5, 1.0f + (float)x/4.0f, 1.0);
            }
        }
    }


    /* song_write(&song, "gui_test.wav"); */
    // TODO load this from the data instead of file
    /* sound = LoadSound("gui_test.wav"); */

    Wave wave;
    wave.frameCount = song.num_samples / 2;
    wave.sampleRate = song.sample_rate;
    wave.sampleSize = 16;
    wave.channels = 2;
    wave.data = song.samples;
    Sound sound = LoadSoundFromWave(wave);
    PlaySound(sound);
}

void play_note(int index, int velocity) {
    int note = A0 + (Y - index - 1);
    Song song;
    song_init(&song, soundfont, 4, 120.0f, 1);
    int piano = 0;
    song_note(&song, piano, note, (float)velocity/128.0f, 1.0f + (float)0/4.0f, 1.0);
    Wave wave;
    wave.frameCount = song.num_samples / 2;
    wave.sampleRate = song.sample_rate;
    wave.sampleSize = 16;
    wave.channels = 2;
    wave.data = song.samples;
    Sound sound = LoadSoundFromWave(wave);
    PlaySound(sound);

}

int main(void) {
    int screen_width = 800;
    int screen_height = 600;

    int x_offset = 30;
    int y_offset = 30;

    int grid[Y][X];
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            grid[y][x] = 0;
        }
    }

    int cell_height = 12;
    int cell_width = 15;

    bool is_loaded = false;
    soundfont = load_soundfont("/home/paul/Downloads/chorium.sf2", &is_loaded);
    if (!is_loaded) {
        return 1;
    }

    InitWindow(screen_width, screen_height, "Music Editor");
    InitAudioDevice();
    /* SetTargetFPS(60); */

    /* FILE *f; */
    /* f = fopen("/dev/snd/midiC3D0", "rb"); */
    /* bool note_on = false; */
    /* int current_note = 0; */
    /* int current_velocity = 0; */

    while (!WindowShouldClose()) {

        /* while(1){ */
        /* int c = fgetc(f); */
        /* if (c == 0x90) { */
        /*     int note = fgetc(f); */
        /*     int velocity = fgetc(f); */
        /*     if (velocity == 0) { */
        /*         note_on = false; */
        /*     } else { */
        /*         note_on = true; */
        /*         /1* printf("Note on %d %d\n", note, velocity); *1/ */
        /*         play_note(note, velocity); */
        /*         current_note = note; */
        /*         current_velocity = velocity; */
        /*     } */
        /* } */
        /* } */

        /* if (note_on) { */
        /*     printf("Current note %d %d\n", current_note, current_velocity); */
        /*     DrawText(TextFormat("note %d %d", current_note, current_velocity), 0, 0, 20, RED); */
        /* } */

        // update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouse_x = GetMouseX();
            int mouse_y = GetMouseY();
            if (mouse_x - x_offset > 0 && mouse_x - x_offset < X * cell_width && mouse_y - y_offset > 0 && mouse_y - y_offset < Y * cell_height) {
                grid[(mouse_y - y_offset) / cell_height][(mouse_x - x_offset) / cell_width] = (grid[(mouse_y - y_offset) / cell_height][(mouse_x - x_offset) / cell_width] == 1 ? 0 : 1);

                play_note((mouse_y - y_offset) / cell_height, 64);
            }
        }

        int wheel = GetMouseWheelMove();
        if (wheel != 0) {
            if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
                x_offset += wheel * cell_width * 3;
            } else {
                y_offset += wheel * cell_height * 3;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            play(grid);

            /* Song song; */
            /* song_init(&song, soundfont, 3, 100.0f, 8); */
            /* int piano = 0; */
            /* float o = 1.0; */
            /* for (int i = 0; i < 32; i++) { */
            /*     song_note(&song, piano, C3, 0.5, o, 1.0); o += 1.0/4.0; */
            /* } */
            /* song_write(&song, "gui_test.wav"); */

        }

        BeginDrawing();

        ClearBackground((Color){60, 60, 60, 255});

        // Draw the grid
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                Color color;
                if (grid[y][x] == 1) {
                    color = WHITE;
                } else {
                    color = (Color){40, 40, 40, 255};
                    if (y % 12 == 11 || y % 12 == 9 || y % 12 == 6 || y % 12 == 4 || y % 12 == 2) {
                        color = BLACK;
                    }
                    /* if ((x / 16) % 2 == 0) { */
                    /*     color = (Color){ 24, 24, 24, 255}; */
                    /* } */
                    /* if ((x / 4) % 2 == 0) { */
                    /*     color.r += 10; */
                    /*     color.g += 10; */
                    /*     color.b += 10; */
                    /* } */
                }
                DrawRectangle(x * cell_width + x_offset, y * cell_height + y_offset, cell_width - 1, cell_height - 1, color);
            }
        }

        // Draw the piano keys
        for (int y = 0; y < Y; y++) {
            Color color = WHITE;
            if (y % 12 == 11 || y % 12 == 9 || y % 12 == 6 || y % 12 == 4 || y % 12 == 2) {
                color = BLACK;
            }
            DrawRectangle(0, y * cell_height + y_offset, 25, cell_height - 2, color);

            // Draw labels for C notes
            switch (A0 + (Y - y - 1)) {
                case C1: DrawText("C1", 5, y * cell_height + y_offset, 12, RED); break;
                case C2: DrawText("C2", 5, y * cell_height + y_offset, 12, RED); break;
                case C3: DrawText("C3", 5, y * cell_height + y_offset, 12, RED); break;
                case C4: DrawText("C4", 5, y * cell_height + y_offset, 12, RED); break;
                case C5: DrawText("C5", 5, y * cell_height + y_offset, 12, RED); break;
                case C6: DrawText("C6", 5, y * cell_height + y_offset, 12, RED); break;
                case C7: DrawText("C7", 5, y * cell_height + y_offset, 12, RED); break;
            }
            if (A0 + (Y - y - 1) == C4) {
            }
        }

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}

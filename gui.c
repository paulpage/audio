#include <stdio.h>
#include "raylib.h"

#include "song.h"

#define X 256
#define Y 88

tsf *soundfont;
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
    song_init(&song, soundfont, 4, 100.0f, 8);
    int piano = 0;

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (grid[y][x] == 1) {
                song_note(&song, piano, A0 + (Y - y), 0.5, 1.0f + (float)x/4.0f, 1.0);
            }
        }
    }


    /* song_write(&song, "gui_test.wav"); */
    // TODO load this from the data instead of file
    /* sound = LoadSound("gui_test.wav"); */
    Wave wave;
    wave.sampleCount = song.num_samples;
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

    int note_height = 15;

    soundfont = tsf_load_filename("/home/paul/Downloads/soundfonts/sal/SalC5Light2.sf2");
    InitWindow(screen_width, screen_height, "Music Editor");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouse_x = GetMouseX();
            int mouse_y = GetMouseY();
            if (mouse_x - x_offset > 0 && mouse_x - x_offset < X * note_height && mouse_y - y_offset > 0 && mouse_y - y_offset < Y * note_height) {
                grid[(mouse_y - y_offset) / note_height][(mouse_x - x_offset) / note_height] = (grid[(mouse_y - y_offset) / note_height][(mouse_x - x_offset) / note_height] == 1 ? 0 : 1);
            }
        }

        int wheel = GetMouseWheelMove();
        if (wheel != 0) {
            if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
                x_offset += wheel * note_height * 3;
            } else {
                y_offset += wheel * note_height * 3;
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

        ClearBackground((Color){40, 40, 40, 255});

        // Draw the grid
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (grid[y][x] == 1) {
                    DrawRectangle(x * note_height + x_offset, y * note_height + y_offset, note_height - 2, note_height - 2, WHITE);
                } else {
                    Color color = BLACK;
                    if ((x / 16) % 2 == 0) {
                        color = (Color){ 24, 24, 24, 255};
                    }
                    DrawRectangle(x * note_height + x_offset, y * note_height + y_offset, note_height - 2, note_height - 2, color);
                }
            }
        }

        // Draw the piano keys
        for (int y = 0; y < Y; y++) {
            Color color = WHITE;
            if (y % 12 == 11 || y % 12 == 9 || y % 12 == 6 || y % 12 == 4 || y % 12 == 2) {
                color = BLACK;
            }
            DrawRectangle(0, y * note_height + y_offset, 25, note_height - 2, color);
            if (A0 + (Y - y - 1) == C4) {
                DrawText("C4", 5, y * note_height + y_offset, 15, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

// Timer
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#include "song.h"

#define X 256
#define Y 88

Soundfont soundfont;
Sound sound;

/* uint64_t get_performance_counter() { */
/*     uint64_t t; */
/*     struct timespec now; */
/*     clock_gettime(CLOCK_MONOTONIC_RAW, &now); */
/*     t = now.tv_sec; */
/*     t *= 1000000000; */
/*     t += now.tv_nsec; */
/*     return t; */
/* } */

/* uint64_t get_performance_frequency() { */
/*     return 1000000000; */
/* } */


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


static Sound the_sounds[128];
static bool question_sounds[128];

void stop_note(int note) {
    if (question_sounds[note]) {
        StopSound(the_sounds[note]);
    }
    question_sounds[note] = false;
}
void play_note(int note, int velocity) {
    Song song;
    song_init(&song, soundfont, 4, 120.0f, 1);
    int piano = 1 - 1;
    song_note(&song, piano, note, (float)velocity/128.0f, 1.0f + (float)0/4.0f, 1.0);
    Wave wave;
    wave.frameCount = song.num_samples / 2;
    wave.sampleRate = song.sample_rate;
    wave.sampleSize = 16;
    wave.channels = 2;
    wave.data = song.samples;
    /* if (question_sounds[note]) { */
    /*     stop_note(note); */
    /* } */
    the_sounds[note] = LoadSoundFromWave(wave);
    PlaySound(the_sounds[note]);
    /* question_sounds[note] = true; */
}

void play_note_index(int index, int velocity) {
    int note = A0 + (Y - index - 1);
    play_note(note, velocity);
}

/* void draw_piano(int screen_width, int screen_height) { */

/*     for (int i = 0; i < 52; i++) { */
/*         DrawRectangle(i * white_key_width, 0, white_key_width, screen_height, BLACK); */
/*         DrawRectangle(i * white_key_width + 1, 0, white_key_width - 1, screen_height, WHITE); */
/*     } */
/*     for (int i = 0; i < 52; i++) { */
/*         if (i % 7 != 1 && i % 7 != 4 && i != 51) { */
/*             DrawRectangle(i * white_key_width + white_key_width - black_key_width / 2, 0, black_key_width, screen_height / 2, BLACK); */
/*         } */
/*     } */
/* } */

void update_keyboard(Rectangle *white_keys, Rectangle *black_keys) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int white_key_width = screen_width / 52;
    int black_key_width = screen_width / 80;
    for (int i = 0; i < 52; i++) {
        white_keys[i] = (Rectangle){i * white_key_width, 0, white_key_width, screen_height};
        /* DrawRectangle(i * white_key_width + 1, 0, white_key_width - 1, screen_height, WHITE); */
    }
    int j = 0;
    for (int i = 0; i < 52; i++) {
        if (i % 7 != 1 && i % 7 != 4 && i != 51) {
            black_keys[j] = (Rectangle){i * white_key_width + white_key_width - black_key_width / 2, 0, black_key_width, screen_height / 2};
            j++;
        }
    }
}

int main(void) {

    bool pedol = false;
    bool sofpedol = false;
    bool gaspedol = false;

    int screen_width = 3000;
    int screen_height = 600;

    int x_offset = 30;
    int y_offset = 30;

    int grid[Y][X];
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            grid[y][x] = 0;
        }
    }

    /* for (int i = 0; i < 52; i++) { */
    /*     white_keys[i] = (Rectangle){i * white_key_width, 0, white_key_width, screen_height}; */
    /*     /1* DrawRectangle(i * white_key_width + 1, 0, white_key_width - 1, screen_height, WHITE); *1/ */
    /* } */
    /* int j = 0; */
    /* for (int i = 0; i < 52; i++) { */
    /*     if (i % 7 != 1 && i % 7 != 4 && i != 51) { */
    /*         black_keys[j] = {j * white_key_width + white_key_width - black_key_width / 2, 0, black_key_width, screen_height / 2}; */
    /*         j++; */
    /*     } */
    /* } */

    int cell_height = 12;
    int cell_width = 15;

    bool is_loaded = false;
    soundfont = load_soundfont("/home/paul/Downloads/chorium.sf2", &is_loaded);
    if (!is_loaded) {
        return 1;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screen_width, screen_height, "Music Editor");
    InitAudioDevice();
    /* SetTargetFPS(60); */

    /* FILE *f; */
    /* f = fopen("/dev/snd/midiC3D0", "rb"); */
    /* bool note_on = false; */
    /* int current_note = 0; */
    /* int current_velocity = 0; */

    Rectangle white_keys[52];
    Rectangle black_keys[36];
    bool is_white_playing[52];
    bool is_black_playing[36];
    for (int i = 0; i < 52; i++) {
        is_white_playing[i] = false;
    }
    for (int i = 0; i < 36; i++) {
        is_black_playing[i] = false;
    }
    while (!WindowShouldClose()) {

        int mouse_x = GetMouseX();
        int mouse_y = GetMouseY();
        update_keyboard(white_keys, black_keys);

        bool black_key_focused = false;
        int focused_index = -1;

        // Set key collision
        for (int i = 0; i < 36; i++) {
            Rectangle r = black_keys[i];
            if (mouse_x >= r.x && mouse_y >= r.y && mouse_x < r.x + r.width && mouse_y < r.y + r.height) {
                black_key_focused = true;
                focused_index = i;
            }
        }

        if (!black_key_focused) {
            for (int i = 0; i < 52; i++) {
                Rectangle r = white_keys[i];
                if (mouse_x >= r.x && mouse_y >= r.y && mouse_x < r.x + r.width && mouse_y < r.y + r.height) {
                    focused_index = i;
                }
            }
        }

        pedol = (IsKeyDown(KEY_SPACE));
        sofpedol = (IsKeyDown(KEY_S));
        gaspedol = (IsKeyDown(KEY_G));

        int velocity = 120;
        if (sofpedol) {
            velocity = 40;
        }

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
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

            bool play = true;
            if (!black_key_focused && is_white_playing[focused_index]) {
                play = false;
            }
            if (black_key_focused && is_black_playing[focused_index]) {
                play = false;
            }

            if (play) {
                if (!black_key_focused && focused_index != -1) {
                    is_white_playing[focused_index] = true;
                    play_note(WHITE_NOTES[focused_index], velocity);
                } else if (black_key_focused && focused_index != -1) {
                    is_black_playing[focused_index] = true;
                    play_note(BLACK_NOTES[focused_index], velocity);
                }

                if (gaspedol) {
                    if (!black_key_focused && focused_index != -1) {
                        play_note(WHITE_NOTES[focused_index], velocity);
            for (int i = 0; i < 52; i++) {
                        play_note(WHITE_NOTES[i], velocity);
            }
                        /* play_note(WHITE_NOTES[focused_index], velocity); */
                        /* play_note(WHITE_NOTES[focused_index], velocity); */
                        /* play_note(WHITE_NOTES[focused_index], velocity); */
                        /* play_note(WHITE_NOTES[focused_index], velocity); */
                        /* play_note(WHITE_NOTES[focused_index], velocity); */
                        /* play_note(WHITE_NOTES[focused_index+8], velocity); */
                        /* play_note(WHITE_NOTES[focused_index+8], velocity); */
                        /* play_note(WHITE_NOTES[focused_index+8], velocity); */
                        /* play_note(WHITE_NOTES[focused_index+8], velocity); */

                        if (focused_index + 7 < 52) {
                            play_note(WHITE_NOTES[focused_index + 7], velocity);
                        }
                        if (focused_index - 7 >= 0) {
                            play_note(WHITE_NOTES[focused_index - 7], velocity);
                        }
                    } else if (black_key_focused && focused_index != -1) {
                        play_note(BLACK_NOTES[focused_index], velocity);
                        /* play_note(BLACK_NOTES[focused_index], velocity); */
                        /* play_note(BLACK_NOTES[focused_index], velocity); */
                        /* play_note(BLACK_NOTES[focused_index], velocity); */
                        /* play_note(BLACK_NOTES[focused_index], velocity); */
                        /* play_note(BLACK_NOTES[focused_index], velocity); */
                        /* play_note(BLACK_NOTES[focused_index+8], velocity); */
                        /* play_note(BLACK_NOTES[focused_index+8], velocity); */
                        /* play_note(BLACK_NOTES[focused_index+8], velocity); */
                        /* play_note(BLACK_NOTES[focused_index+8], velocity); */
                        if (focused_index + 5 < 36) {
                            play_note(BLACK_NOTES[focused_index + 5], velocity);
                        }
                        if (focused_index - 5 >= 0) {
                            play_note(BLACK_NOTES[focused_index - 5], velocity);
                        }
                    }
                }
            }


            /* if (mouse_x - x_offset > 0 && mouse_x - x_offset < X * cell_width && mouse_y - y_offset > 0 && mouse_y - y_offset < Y * cell_height) { */
            /*     grid[(mouse_y - y_offset) / cell_height][(mouse_x - x_offset) / cell_width] = (grid[(mouse_y - y_offset) / cell_height][(mouse_x - x_offset) / cell_width] == 1 ? 0 : 1); */

            /*     play_note_index((mouse_y - y_offset) / cell_height, 64); */
            /* } */
        }

        if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !pedol) {

            for (int i = 0; i < 52; i++) {
                is_white_playing[i] = false;
                stop_note(WHITE_NOTES[i]);
            }
            for (int i = 0; i < 36; i++) {
                is_black_playing[i] = false;
                stop_note(BLACK_NOTES[i]);
            }
            /* if (!black_key_focused && focused_index != -1) { */
            /*     stop_note(WHITE_NOTES[focused_index]); */
            /* } else if (black_key_focused && focused_index != -1) { */
            /*     stop_note(BLACK_NOTES[focused_index]); */
            /* } */
        }


        for (int i = 0; i < 52; i++) {
            if (!black_key_focused && focused_index != i) {
                is_white_playing[i] = false;
            }
        }
        for (int i = 0; i < 36; i++) {
            if (black_key_focused && focused_index != i) {
                is_black_playing[i] = false;
            }
        }

        if (!pedol) {
            for (int i = 0; i < 52; i++) {
                if (!black_key_focused && focused_index != i) {
                    stop_note(WHITE_NOTES[i]);
                }
            }
            for (int i = 0; i < 36; i++) {
                if (black_key_focused && focused_index != i) {
                    stop_note(BLACK_NOTES[i]);
                }
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

        if (IsKeyPressed(KEY_ONE))   {}
        if (IsKeyPressed(KEY_TWO))   { play_note(CS4, 120); }
        if (IsKeyPressed(KEY_THREE)) { play_note(DS4, 120); }
        if (IsKeyPressed(KEY_FOUR))  {}
        if (IsKeyPressed(KEY_FIVE))  { play_note(FS4, 120); }
        if (IsKeyPressed(KEY_SIX))   { play_note(GS4, 120); }
        if (IsKeyPressed(KEY_SEVEN)) { play_note(AS4, 120); }
        if (IsKeyPressed(KEY_EIGHT)) {}
        if (IsKeyPressed(KEY_NINE))  { play_note(CS5, 120); }
        if (IsKeyPressed(KEY_ZERO))  { play_note(DS5, 120); }

        if (IsKeyPressed(KEY_Q)) { play_note(C4, 120); }
        if (IsKeyPressed(KEY_W)) { play_note(D4, 120); }
        if (IsKeyPressed(KEY_E)) { play_note(E4, 120); }
        if (IsKeyPressed(KEY_R)) { play_note(F4, 120); }
        if (IsKeyPressed(KEY_T)) { play_note(G4, 120); }
        if (IsKeyPressed(KEY_Y)) { play_note(A4, 120); }
        if (IsKeyPressed(KEY_U)) { play_note(B4, 120); }
        if (IsKeyPressed(KEY_I)) { play_note(C5, 120); }
        if (IsKeyPressed(KEY_O)) { play_note(D5, 120); }
        if (IsKeyPressed(KEY_P)) { play_note(E5, 120); }

        if (IsKeyPressed(KEY_A)) { play_note(E5, 120); }
        /* if (IsKeyPressed(KEY_S)) { play_note(E5, 120); } */
        if (IsKeyPressed(KEY_D)) { play_note(E5, 120); }
        if (IsKeyPressed(KEY_F)) { play_note(E5, 120); }
        /* if (IsKeyPressed(KEY_G)) { play_note(E5, 120); } */
        if (IsKeyPressed(KEY_H)) { play_note(E5, 120); }
        if (IsKeyPressed(KEY_J)) { play_note(E5, 120); }
        if (IsKeyPressed(KEY_K)) { play_note(E5, 120); }
        if (IsKeyPressed(KEY_L)) { play_note(E5, 120); }

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

        for (int i = 0; i < 52; i++) {

            DrawRectangleRec(white_keys[i], BLACK);

            Rectangle rect = (Rectangle) {
                white_keys[i].x + 1,
                white_keys[i].y,
                white_keys[i].width - 1,
                white_keys[i].height,
            };

            Color color = WHITE;
            if (!black_key_focused && focused_index == i) {
                color = GREEN;
            }
            DrawRectangleRec(rect, color);
        }

        for (int i = 0; i < 36; i++) {
            Color color = BLACK;
            if (black_key_focused && focused_index == i) {
                color = GREEN;
            }
            DrawRectangleRec(black_keys[i], color);
        }


        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
        /* draw_piano(screen_width, screen_height); */

        /* ClearBackground((Color){60, 60, 60, 255}); */

        /* // Draw the grid */
        /* for (int y = 0; y < Y; y++) { */
        /*     for (int x = 0; x < X; x++) { */
        /*         Color color; */
        /*         if (grid[y][x] == 1) { */
        /*             color = WHITE; */
        /*         } else { */
        /*             color = (Color){40, 40, 40, 255}; */
        /*             if (y % 12 == 11 || y % 12 == 9 || y % 12 == 6 || y % 12 == 4 || y % 12 == 2) { */
        /*                 color = BLACK; */
        /*             } */
        /*             /1* if ((x / 16) % 2 == 0) { *1/ */
        /*             /1*     color = (Color){ 24, 24, 24, 255}; *1/ */
        /*             /1* } *1/ */
        /*             /1* if ((x / 4) % 2 == 0) { *1/ */
        /*             /1*     color.r += 10; *1/ */
        /*             /1*     color.g += 10; *1/ */
        /*             /1*     color.b += 10; *1/ */
        /*             /1* } *1/ */
        /*         } */
        /*         DrawRectangle(x * cell_width + x_offset, y * cell_height + y_offset, cell_width - 1, cell_height - 1, color); */
        /*     } */
        /* } */

        /* // Draw the piano keys */
        /* for (int y = 0; y < Y; y++) { */
        /*     Color color = WHITE; */
        /*     if (y % 12 == 11 || y % 12 == 9 || y % 12 == 6 || y % 12 == 4 || y % 12 == 2) { */
        /*         color = BLACK; */
        /*     } */
        /*     DrawRectangle(0, y * cell_height + y_offset, 25, cell_height - 2, color); */

        /*     // Draw labels for C notes */
        /*     switch (A0 + (Y - y - 1)) { */
        /*         case C1: DrawText("C1", 5, y * cell_height + y_offset, 12, RED); break; */
        /*         case C2: DrawText("C2", 5, y * cell_height + y_offset, 12, RED); break; */
        /*         case C3: DrawText("C3", 5, y * cell_height + y_offset, 12, RED); break; */
        /*         case C4: DrawText("C4", 5, y * cell_height + y_offset, 12, RED); break; */
        /*         case C5: DrawText("C5", 5, y * cell_height + y_offset, 12, RED); break; */
        /*         case C6: DrawText("C6", 5, y * cell_height + y_offset, 12, RED); break; */
        /*         case C7: DrawText("C7", 5, y * cell_height + y_offset, 12, RED); break; */
        /*     } */
        /*     if (A0 + (Y - y - 1) == C4) { */
        /*     } */
        /* } */

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}

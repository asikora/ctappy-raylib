#include "raylib.h"
#include "game_state.h"


int main() {


    InitWindow(screen_width, screen_height, "CTappy - raylib");
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);

    float delta_time;
    current_state = game_state_init;
    
    while (!WindowShouldClose()) {

        delta_time = GetFrameTime();
        current_state(delta_time);

        if(quit_game) {

            break;
        }
    }
    game_state_destroy();
    CloseWindow();

    return 0;
}
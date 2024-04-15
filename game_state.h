#include "raylib.h"
#include "player.h"


typedef void (*GameState)(const float delta_time);
extern void game_state_init(const float);
extern void game_state_game_start(const float);
extern void game_state_game(const float);
extern void game_state_gameover(const float);
extern void game_state_menu(const float);
extern void game_state_destroy();
extern void score_add(int count);

extern const int screen_width;
extern const int screen_height;
extern GameState current_state;
extern bool quit_game; 
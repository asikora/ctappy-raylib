#include "game_state.h"
#include "spikes.h"

const int gravity = 800;
const unsigned int num_of_spikes = 15;


Texture2D background;
Texture2D ground;
Texture2D game_over;
Texture2D button; 
Player *player;
Font font;

unsigned score = 0;
unsigned highscore = 0; 

const int screen_width = 800;
const int screen_height = 480;

GameState current_state;
bool quit_game = false;

void score_add(int count) {
    score += count;
    if (score > highscore) {
        highscore = score;
    }
}

void background_draw(const float delta_time,  const Texture2D *background, const float position_y, const float scrolling_spped) {

    static float scrolling_back = 0;

    scrolling_back -= scrolling_spped * delta_time;

    if (scrolling_back <= -background->width) scrolling_back = 0;

    DrawTextureEx(*background, (Vector2){ scrolling_back, position_y }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(*background, (Vector2){ background->width + scrolling_back, position_y }, 0.0f, 1.0f, WHITE);

}

void ground_draw(const float delta_time,  const Texture2D *background, const float position_y, const float scrolling_spped) {

    static float scrolling_back = 0;

    scrolling_back -= scrolling_spped * delta_time;

    if (scrolling_back <= -background->width) scrolling_back = 0;

    DrawTextureEx(*background, (Vector2){ scrolling_back, position_y }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(*background, (Vector2){ background->width + scrolling_back, position_y }, 0.0f, 1.0f, WHITE);

}


void game_state_init(const float delta_time) {
       
    background = LoadTexture("assets/sprites/PNG/background.png");
    ground = LoadTexture("assets/sprites/PNG/groundDirt.png");

    game_over = LoadTexture("assets/sprites/PNG/UI/textGameOver.png");
    player = player_create("assets/sprites/plane.png");
    font = LoadFontEx("assets/fonts/kenvector_future.ttf", 32, 0, 250);
    button = LoadTexture("assets/sprites/PNG/UI/buttonLarge.png");

    current_state = game_state_menu;

}

void game_state_game_start(const float detla_time) {

    score = 0;
    spikes_init(15, screen_width, screen_height);
    player_set_position(player, (Vector2){20,20});
    player_set_velocity(player, 0,0);
    current_state = game_state_game;
}

void game_state_game(const float delta_time) {

    if(IsKeyPressed(KEY_SPACE)) {
        player_set_velocity(player, 0, -300);
    }

        player_move(player, gravity, delta_time);

    BeginDrawing();
        ClearBackground(WHITE);
        background_draw(delta_time, &background, 0.0f, 30.0f);
        ground_draw(delta_time, &ground, screen_height - ground.height, 50.0f);
        player_animate(player, 15, 3);
        if (spikes_draw_move_and_collide(player, num_of_spikes, delta_time, screen_width, screen_height) || player_get_position(player).y > screen_height ) {
            current_state = game_state_gameover;
        }

        const char *highscore_text = TextFormat("High Score: %d", highscore);
        DrawTextEx(font, highscore_text, (Vector2){10, 10}, 32, 2, RED);

        const char *score_text = TextFormat("Score: %d", score);
        DrawTextEx(font, score_text, (Vector2){screen_width - MeasureTextEx(font, score_text, 32, 2).x, 10}, 32, 2, RED);

    EndDrawing();
}

void game_state_gameover(const float delta_time) {
    BeginDrawing(); 
        ClearBackground(BLACK);
        
        DrawTexture(game_over, screen_width / 2 - game_over.width/2 ,150, WHITE);
        
        Vector2 text_pos = MeasureTextEx(font, TextFormat("Score: %d!", score), 32, 2);
        DrawTextEx(font, TextFormat("Score: %d!", score), (Vector2){screen_width/2 - text_pos.x/2, 320}, 32, 2, WHITE);
        
        text_pos = MeasureTextEx(font, "Press space to continue", 32, 2);
        DrawTextEx(font, "Press space to continue", (Vector2){screen_width/2 - text_pos.x/2, 420}, 32, 2, WHITE);
    EndDrawing();

    if(IsKeyPressed(KEY_SPACE)) {
        current_state =  game_state_menu;
    }
}

void game_state_menu(const float delta_time) {

    static bool button_active = true;

    const char *new_game_text = "New Game";
    const char *quit_game_text = "Quit";
    Vector2 new_game_text_size = MeasureTextEx(font, new_game_text, 28, 2);
    Vector2 quit_game_text_size = MeasureTextEx(font, quit_game_text, 28, 2);


    Vector2 button_start_game_pos = {screen_width/2 - button.width/2,screen_height/2 - button.height/2};
    Vector2 button_quit_game_pos = {screen_width/2 - button.width/2,screen_height/2 - button.height/2 + button.height+20};
    Rectangle button_start_game_rect = {0,0, button.width, button.height};

    Vector2 new_game_text_position = (Vector2){(button.width - new_game_text_size.x) / 2 + button_start_game_pos.x, (button.height - new_game_text_size.y) /2 + button_start_game_pos.y }; 
    Vector2 quit_game_text_position = (Vector2){(button.width - quit_game_text_size.x) / 2 + button_quit_game_pos.x, (button.height - quit_game_text_size.y) /2 + button_quit_game_pos.y };

    BeginDrawing();
        ClearBackground(WHITE);

         DrawTextureEx(background, (Vector2){ 0, 0 }, 0.0f, 1.0f, WHITE);

         DrawTextureRec(button, button_start_game_rect, button_start_game_pos, WHITE);
         DrawTextEx(font, "New game", new_game_text_position, 28,2, button_active ? RED : WHITE );

        DrawTextureRec(button, button_start_game_rect, button_quit_game_pos, WHITE);
        DrawTextEx(font, "Quit", quit_game_text_position, 28,2, !button_active ? RED : WHITE );

        const char *highscore_text = TextFormat("High Score: %d", highscore);
        DrawTextEx(font, highscore_text, (Vector2){10, 10}, 32, 2, RED);
    EndDrawing();

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) {
        button_active = !button_active;
    }

    if (IsKeyPressed(KEY_SPACE) && button_active) {
         current_state = game_state_game_start;
    }

    if (IsKeyPressed(KEY_SPACE) && !button_active) {
         quit_game = true;
    }

}

void game_state_destroy() {
    UnloadTexture(background);
    UnloadTexture(ground);
    UnloadTexture(button);
    UnloadTexture(game_over);
    player_destroy(player);
    spikes_destroy(num_of_spikes);
}

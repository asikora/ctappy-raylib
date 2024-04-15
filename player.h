#include "raylib.h"

typedef void Player;

Player *player_create(const char *sprite);
Rectangle player_get_collision_rec(const Player *p);

void player_destroy(Player *p);
void player_draw(const Player *p, int current_frame);
void player_animate(const Player *p, unsigned int frame_speed, unsigned int frames_count);
void player_move(Player *p, const float gravity, const float delta_time);
void player_set_velocity(Player *p, const float velocity_x, const float velocity_y );
void player_destroy(Player *p);

void player_set_position(Player *p, Vector2 target_position);
Vector2 player_get_position(const Player *p);
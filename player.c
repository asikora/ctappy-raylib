#include "raylib.h"
#include "player_internal.h"

#include <stdlib.h>

Player *player_create(const char *sprite) {

    int px,py;
    px = py = 20;

    Player *p;
    p = malloc(sizeof *p);

    p->sprite = LoadTexture(sprite);
    p->velocity = (Vector2){0,0};
    p->position = (Vector2){px,py};

    p->bounding_box.height = p->sprite.height;
    p->bounding_box.width = p->sprite.width/3;
    p->bounding_box.x = px;
    p->bounding_box.y = py;

    p->frame_rec.x = 0;
    p->frame_rec.y = 0;
    p->frame_rec.width = p->sprite.width/3;
    p->frame_rec.height = p->sprite.height;
    return p;
}

void player_draw(const Player *p, int frame) {
    Rectangle current_frame;
    current_frame = p->frame_rec;
    current_frame.x = (float)frame*(float)p->frame_rec.width;
   // DrawRectangleRec(p->bounding_box, RED);
    DrawTextureRec(p->sprite, current_frame, p->position, WHITE);
    
}

void player_animate(const Player *p, unsigned int frames_speed, unsigned int frames_count) {
        
        static unsigned int frames_counter = 0;
        static unsigned int current_frame = 0;

        frames_counter++;

        if (frames_counter >= (60/frames_speed))
        {
            frames_counter = 0;
            current_frame++;

            if (current_frame > frames_count) current_frame = 0;
        }

        player_draw(p, current_frame);

}

void player_set_velocity(Player *p, const float velocity_x, const float velocity_y ) {
    p->velocity.x = velocity_x;
    p->velocity.y = velocity_y;
}

void player_move(Player *p, const float gravity, const float delta_time) {
    p->velocity.y += gravity * delta_time;
    p->position.y += p->velocity.y * delta_time;
    p->bounding_box.x = p->position.x;
    p->bounding_box.y = p->position.y;
}

void player_destroy(Player *p) {
    UnloadTexture(p->sprite);
    free(p);
}

Rectangle player_get_collision_rec(const Player *p) {
    return p->bounding_box;
}

Vector2 player_get_position(const Player *p) {
    return p->position;
}

void player_set_position(Player *p, Vector2 target_position) {
    p->position = target_position;
    p->bounding_box.x = p->position.x;
    p->bounding_box.y = p->position.y;
}
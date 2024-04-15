#include "spike_internal.h"
#include <stdlib.h>

Spike *spike_create(const char *filename,  const int px, const int py) {
    Spike *s;
    s = malloc(sizeof *s);

    s->sprite = LoadTexture(filename);
    s->velocity = (Vector2){-180,0};
    s->position = (Vector2){px,py};

    s->bounding_box.height = s->sprite.height - 20;
    s->bounding_box.width = 40;
    s->bounding_box.x = px;
    s->bounding_box.y = py;

    s->scale = 1;
    s->rotation = 0;

    return s;
}

void spike_draw(const Spike  *s) {

    DrawTextureEx(s->sprite, s->position, s->rotation, s->scale, WHITE);
    //DrawRectangleRec(s->bounding_box, RED);
}

void spike_move(Spike *s, float delta_time) {
    s->position.x += s->velocity.x * delta_time;
    s->bounding_box.x = s->position.x + s->sprite.width/2 - 10;
    s->bounding_box.y = s->position.y;
}

Vector2 spike_get_position(const Spike *s) {
    return s->position;
}

Vector2 spike_get_size(const Spike *s) {
    return (Vector2){s->sprite.height, s->sprite.width};
}

void spike_set_position_v2(Spike *s, Vector2 pos) {
    s->position = pos;
}

void spike_set_position_f(Spike *s, float x, float y) {
    s->position.x = x;
    s->position.y = y;
}

Rectangle spike_get_collision_rec(const Spike *s) {
    return s->bounding_box;
}

void spike_destroy(Spike *s) {
    UnloadTexture(s->sprite);
}
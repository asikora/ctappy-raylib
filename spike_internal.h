#include "raylib.h"

#ifndef SPIKE_INTERNAL_H
#define SPIKE_INTERNAL_H

typedef struct Spike {
    Texture2D sprite;
    Vector2 velocity;
    Vector2 position;
    Rectangle bounding_box;
    float scale;
    float rotation;
} Spike;

#endif //SPIKE_INTERNAL_H
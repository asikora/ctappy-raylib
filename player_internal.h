#include "raylib.h"

typedef struct Player {
    Texture2D sprite;
    Vector2 velocity;
    Vector2 position;
    Rectangle bounding_box;
    Rectangle  frame_rec;
}Player;
#include "spike.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>

typedef struct Spikes {
    Spike *up;
    Spike *down;
    Rectangle between;
}Spikes;



void spikes_init(int count, int screen_width, int screen_height);
bool spikes_draw_move_and_collide(const Player *player, int count, float delta_time, int screen_width, int screen_height);
void spikes_destroy(int count);

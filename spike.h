#include <raylib.h>

typedef void Spike;

Spike *spike_create(const char *filename, int px, int py);
Vector2 spike_get_position(const Spike *s);
Rectangle spike_get_collision_rec(const Spike *s);
Vector2 spike_get_size(const Spike *s);

void spike_draw(const Spike *s);
void spike_move(Spike *s, float delta_time);
void spike_set_position(Spike *s, Vector2 pos);
void spike_set_position_f(Spike *s, float x, float y);
void spike_destroy(Spike *s);
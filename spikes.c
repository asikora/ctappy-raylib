#include "spikes.h"
#include "game_state.h"

Spikes *spikes;

int last_pos_x;

void spikes_init(int count, int screen_width, int screen_height) {

    spikes = malloc(sizeof (*spikes) * count);

    for (size_t i = 0; i<count; i++) {
        int x = GetRandomValue(110, 300);
        int y = GetRandomValue(-100,0);
        if (i > 0) {
            x = x + spike_get_position(spikes[i-1].up).x-screen_width;
        }
        Spikes s;
        s.up = spike_create("assets/sprites/PNG/rock.png", screen_width + x, screen_height + 2*y);
        s.down =  spike_create("assets/sprites/PNG/rockDown.png",screen_width + x, y);
        s.between = (Rectangle){spike_get_position(s.down).x+50, spike_get_position(s.down).y + spike_get_size(s.down).x, 40,220};
        spikes[i] = s;
    }
    last_pos_x = spike_get_position(spikes[count-1].up).x;
}
    

bool spikes_draw_move_and_collide(const Player *player, int count, float delta_time, int screen_width, int screen_height) {
    
    for(size_t i=0;  i<count; i++) {

        int y = GetRandomValue(-100,0);

        Vector2 spike_pos_up = spike_get_position(spikes[i].up);

        if (spike_pos_up.x < -(last_pos_x-screen_width*2)) {
            spike_set_position_f(spikes[i].up, screen_width, screen_height + y*2);
            spike_set_position_f(spikes[i].down, screen_width, y);

        }
        spike_draw(spikes[i].up);
        spike_draw(spikes[i].down);
        spikes[i].between.x += -180 * delta_time;
        spike_move(spikes[i].up, delta_time);
        spike_move(spikes[i].down, delta_time);

        if(CheckCollisionRecs(player_get_collision_rec(player), spikes[i].between)) {
            score_add(1);
            spikes[i].between = (Rectangle){0,0,0,0};
        }
        
        if(CheckCollisionRecs(player_get_collision_rec(player), spike_get_collision_rec(spikes[i].up)) || CheckCollisionRecs(player_get_collision_rec(player), spike_get_collision_rec(spikes[i].down)) ) {
            return true;
        }

    }
    
    return false;
}

void spikes_destroy(int count) {
    
    if(spikes != NULL) {
        for(size_t i=0; i<count;i++) {
            spike_destroy(spikes[i].up);
            spike_destroy(spikes[i].down);
        }
    }

}
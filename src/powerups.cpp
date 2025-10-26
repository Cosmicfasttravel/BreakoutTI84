#include "powerups.h"

void generate_powerup(powerups *p, int *livPtr) {
    if (p->active) {}
    switch (p->type) {
        case MULTIBALL:
            spawn_ball(paddle.x, paddle.y - 20, randInt(1,2) == 1 ? randInt(-2,-1) : randInt(1,2), -2);
            break;
        case EXTRA_LIFE:
            (*livPtr)++;
            break;
        case WIDE_PADDLE:
            paddle.w+=10;
            break;
        default:;
    }
}


void spawn_powerup(int x, int y, powerupTypes type) {
    for (auto & powerups : powerup) {
        if (powerups.active) continue;
        powerups.x = x;
        powerups.y = y;
        powerups.ix = randInt(-1, 1);
        powerups.active = true;
        powerups.type = type;
        break;
    }
}

void clear_powerups(){
    for (auto &p : powerup) {
        if (!p.active) gfx_FillCircle(p.x, p.y, 5);
        gfx_SetColor(0);
        gfx_FillCircle(p.x, p.y - 1, 5);
    }
}

void update_powerups_slow() {
    for (auto &p : powerup) {
        if (!p.active) continue;
        gfx_FillCircle(p.x, p.y, 3);
        p.y += 1;
        if (p.y >= 235) {
            p.active = false;
        }
    }
}

void update_powerups_fast() {
    for (auto &p : powerup) {
        if (!p.active) continue;
        gfx_FillCircle(p.x, p.y, 3);
        p.y += 1;
        p.x += p.ix;
        if (p.x < 5 || p.x > 315) {
            p.ix *= -1;
        }
        if (p.y >= 235) {
            p.active = false;
        }
    }
}
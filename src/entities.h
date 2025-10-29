#ifndef ENTITIES_H
#define ENTITIES_H

#include "global.h"

//functions
void spawn_box(int x, int y, int w, int h);

void delete_balls();

void draw_box();
void update_ball(ball *ball);
void draw_paddle(uint16_t x, uint8_t y);
void draw_ball(const ball *ball);

void clear_box();
void clear_ball();
void clear_misc();

#endif //ENTITIES_H

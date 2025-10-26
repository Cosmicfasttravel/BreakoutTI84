#include "entities.h"
//ball spawning, just setting
void spawn_ball(int x, int y, int ix, int iy) {
    for (auto & ball : balls) {
        if (!ball.active) {
            ball.x = x;
            ball.y = y;
            ball.radius = 8;
            ball.incX = ix;
            ball.incY = iy;
            ball.active = true;
            break;
        }
    }
}
//box spawning, just setting
void spawn_box(int x, int y, int w, int h) {
    for (auto & box : boxes) {
        if (!box.active) {
            box.x = x;
            box.y = y;
            box.w = w;
            box.h = h;
            box.c = random_color();
            box.active = true;
            break;
        }
    }
}

//ball updating
void update_ball(ball *ball) {
    if (!ball->active) return;

    // Save previous position
    ball->prevX = ball->x;
    ball->prevY = ball->y;

    // Update position
    ball->x += ball->incX;
    ball->y += ball->incY;

    // Collision with walls
    if (ball->x - ball->radius < 0) {
        ball->x = ball->radius;
        ball->incX *= -1;
        ball->pHit = false;
    }
    if (ball->x + ball->radius > 319) {
        ball->x = 319 - ball->radius;
        ball->incX *= -1;
        ball->pHit = false;
    }
    if (ball->y - ball->radius < 0) {
        ball->y = ball->radius;
        ball->incY *= -1;
        ball->pHit = false;
    }
    if (ball->y + ball->radius > 239) {
        ball->active = false; // Ball lost


    }
}

//drawing
//--------------------------
//box draw
void draw_box() {
    for (auto & boxes : boxes) {
        if (boxes.active) {
            gfx_SetColor(boxes.c);
            gfx_FillRectangle_NoClip(boxes.x, boxes.y, boxes.w, boxes.h);
        }
    }
}
//simple paddle draw
void draw_paddle(uint16_t x, uint8_t y) {
    gfx_FillRectangle_NoClip(x, y, paddle.w, 2);
}



//clearing
//-----------------------------
//box clear
void clear_box() {
    for (auto &boxe : boxes) {
        if (!boxe.active) {
            gfx_SetColor(0);
            gfx_FillRectangle_NoClip(boxe.x, boxe.y, boxe.w, boxe.h);
        }
    }
}
//ball clear
void draw_ball(const ball *ball) {
    if (!ball->active) return;
    // Center the rectangle on the ball's position
    gfx_FillRectangle(ball->x - ball->radius/2, ball->y - ball->radius/2, ball->radius - 3, ball->radius - 3);
}

void clear_ball() {
    gfx_SetColor(0);
    for (auto &ball : balls) {
        if (ball.active) {
            int clearSize = ball.radius;
            gfx_FillRectangle(ball.prevX - clearSize/2, ball.prevY - clearSize/2, ball.radius - 3, ball.radius - 3);
        } else {
            int clearSize = ball.radius;
            gfx_FillRectangle(ball.prevX - clearSize/2, ball.prevY - clearSize/2, clearSize, clearSize);
            gfx_FillRectangle(ball.x - clearSize/2, ball.y - clearSize/2, clearSize, clearSize);
        }
    }
}
//extra clears
void clear_misc() {
    gfx_SetColor(0);
    gfx_FillRectangle(0, 218, 320, 5);
    gfx_FillRectangle(0, 220, 100, 20);
}

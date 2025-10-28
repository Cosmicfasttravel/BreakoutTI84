#include "entities.h"
//ball spawning, just setting
void spawn_ball(int x, int y, int ix, int iy) {
    for (auto & ball : balls) {
        if (!ball.active) {
            ball.x = x;
            ball.y = y;
            ball.radius = 2;
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
    if (ball->x - ball->radius < 2) {
        ball->x = ball->radius + 2;
        ball->incX *= -1;
        ball->pHit = false;
    }
    if (ball->x + ball->radius > 318) {
        ball->x = 319 - ball->radius - 2;
        ball->incX *= -1;
        ball->pHit = false;
    }
    if (ball->y - ball->radius < 2) {
        ball->y = ball->radius + 2;
        ball->incY *= -1;
        ball->pHit = false;
    }
    if (ball->y + ball->radius > 238) {
        ball->active = false; // Ball lost


    }
}

//drawing
//--------------------------
//box draw
void draw_box() {
    gfx_SetColor(255);
    for (auto & boxes : boxes) {
        if (boxes.active) {
            gfx_SetColor(boxes.c);
            gfx_FillRectangle(boxes.x, boxes.y, boxes.w, boxes.h);
        }
    }
}
//simple paddle draw
void draw_paddle(uint16_t x, uint8_t y) {
    gfx_FillRectangle_NoClip(x, y, paddle.w, 2);
}



//box clear
void clear_box() {
    for (auto &boxe : boxes) {
        if (!boxe.active) {
            gfx_SetColor(0);
            gfx_FillRectangle(boxe.x, boxe.y, boxe.w, boxe.h);
        }
    }
}

//ball draw
void draw_ball(const ball *ball) {
    if (!ball->active) return;
    gfx_FillCircle(ball->x, ball->y, ball->radius);
}

//ball clear
void clear_ball() {
    gfx_SetColor(0);
    for (auto &b : balls) {
        if (b.active) {
            // Clear at previous position
            gfx_FillCircle(b.prevX, b.prevY, b.radius + 2);
        } else {
            // Clear both positions when inactive
            gfx_FillCircle(b.prevX, b.prevY, b.radius + 2);
            gfx_FillCircle(b.x, b.y, b.radius + 1);
        }
    }
}
//extra clears
void clear_misc() {
    gfx_SetColor(0);
    gfx_FillRectangle(0, 218, 320, 5);
    gfx_FillRectangle(0, 220, 100, 20);
}

#include "asteroids.h"

#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <graphx.h>
#include <keypadc.h>
#include <sys/rtc.h>
#include <sys/util.h>

#define MAX_BOXES 200
#define BOX_COLS 18
#define BOX_ROWS 18
#define MAX_BALLS 3
#define BOX_WIDTH 15
#define BOX_HEIGHT 10
#define START_X 30
#define START_Y 0
#define MAX_POWERUPS 5
struct paddle {
    uint16_t x = 160;
    uint8_t y = 220;
};
struct ball {
    uint16_t x{};
    uint8_t y{};
    uint8_t radius{};
    int incX{};
    int incY{};
    bool active{};
    bool pHit = false;
};
struct box {
    int x{};
    int y{};
    int w{};
    int h{};
    int c{};
    bool active = false;
};

enum powerupTypes {
    MULTIBALL,
    WIDE_PADDLE,
    EXTRA_LIFE,
};
struct powerups {
    int x{};
    int y{};
    powerupTypes type{};
    bool active{};
};

struct paddle paddle;
struct ball balls[MAX_BALLS];
struct powerups powerup[MAX_POWERUPS];
box boxes[MAX_BOXES];
uint16_t random_color() {
    int i = randInt(0,3);
        switch (i) {
            case 0:
                return 7;
            case 1:
                return 20;
            case 2:
                return 79;
            case 3:
                return 255;
            default:
                return 0;
        }
}

void generate_powerup() {
    for (auto & powerups : powerup) {
        if (!powerups.active) continue;
        switch (powerups.type) {
            case powerupTypes::MULTIBALL:
                spawn_ball(randInt(10,310), 10, 2, -2);
                break;
            case powerupTypes::WIDE_PADDLE:
                spawn_ball(randInt(10,310), 10, 2, -2);
                break;
            case powerupTypes::EXTRA_LIFE:
                spawn_ball(randInt(10,310), 10, 2, -2);
                break;
            default:;
        }
    }
}

void spawn_powerup(int x, int y, powerupTypes type) {
    for (auto & powerups : powerup) {
        if (powerups.active) continue;
        powerups.x = x;
        powerups.y = y;
        powerups.type = type;
        powerups.active = true;
    }
}

void generate_connected_level() {
    for (auto & boxe : boxes) {
        boxe.active = false;
    }
    uint16_t maxBoxes = 20 + randInt(0,49);
    uint16_t startRow = 5 + randInt(0,9);
    uint16_t startCol = 5 + randInt(0,9);

    //map
    bool placed[BOX_ROWS][BOX_COLS] = {{false}};

    // start from one box
    int curRow = startRow;
    int curCol = startCol;
    placed[curRow][curCol] = true;
    int placedCount = 1;

    while (placedCount < maxBoxes) {
        const int dirY[6] = { 0, 0, 1, -1, 2, -2};
        const int dirX[6] = { 1, -1, 0, 0, 2, -2};
        int dir = randInt(0, 5);
        int newRow = curRow + dirY[dir];
        int newCol = curCol + dirX[dir];

        // keep within grid
        if (newRow >= 0 && newRow < BOX_ROWS && newCol >= 0 && newCol < BOX_COLS) {
            if (!placed[newRow][newCol]) {
                placed[newRow][newCol] = true;
                placedCount++;
            }
            curRow = newRow;
            curCol = newCol;
        }
    }

    // convert placed map into box coordinates
    int boxIndex = 0;
    for (int row = 0; row < BOX_ROWS; row++) {
        for (int col = 0; col < BOX_COLS; col++) {
            if (placed[row][col]) {
                boxes[boxIndex].x = START_X + col * BOX_WIDTH;
                boxes[boxIndex].y = START_Y + row * BOX_HEIGHT;
                boxes[boxIndex].w = BOX_WIDTH;
                boxes[boxIndex].h = BOX_HEIGHT;
                boxes[boxIndex].active = true;
                boxes[boxIndex].c = random_color();
                boxIndex++;
            }
        }
    }
}
void spawn_ball(int x, int y, int ix, int iy) {
    for (auto & ball : balls) {
        if (!ball.active) {
            ball.x = x;
            ball.y = y;
            ball.radius = 3;
            ball.incX = ix;
            ball.incY = iy;
            ball.active = true;
            break;
        }
    }
}
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

void draw_box() {
    for (auto & boxes : boxes) {
        if (boxes.active) {
            gfx_SetColor(boxes.c);
            gfx_FillRectangle_NoClip(boxes.x, boxes.y, boxes.w, boxes.h);
        }
    }
}

void update_ball(ball *ball) {
    if (!ball->active) return;

    ball->x += ball->incX;
    ball->y += ball->incY;

    // Left wall
    if (ball->x - ball->radius < 0) {
        ball->x = ball->radius;
        ball->incX *= -1;
        ball->pHit = false;
    }

    // Right wall
    if (ball->x + ball->radius > 319) {
        ball->x = 319 - ball->radius;
        ball->incX *= -1;
        ball->pHit = false;
    }

    // Top wall
    if (ball->y - ball->radius < 0) {
        ball->y = ball->radius;
        ball->incY *= -1;
        ball->pHit = false;
    }

    // Bottom wall
    if (ball->y + ball->radius > 239) {
        ball->active = false;
    }
}

void draw_ball(const ball *ball) {
    if (!ball->active) return;
    gfx_FillCircle(ball->x, ball->y, ball->radius);
}

void pause() {
    while (!os_GetCSC()) {}
}
void draw_paddle( uint16_t x, uint8_t y) {
    gfx_FillRectangle_NoClip(x, y, 40, 2);
}
void clear(){
    for (auto &boxe : boxes) {
        if (!boxe.active) {
            gfx_SetColor(0);
            gfx_FillRectangle_NoClip(boxe.x, boxe.y, boxe.w, boxe.h);
        }
    }
    for (auto &ball : balls) {
        gfx_SetColor(0);
        if (!ball.active) gfx_FillCircle(ball.x, ball.y, ball.radius + 10);;
        gfx_FillCircle(ball.x, ball.y, ball.radius + 10);


    }
    gfx_FillRectangle(0, 218, 320, 5);
    gfx_FillRectangle(0, 0, 100, 20);
    for (auto &p : powerup) {
        if (!p.active) gfx_FillCircle(p.x, p.y, 5);
        gfx_SetColor(0);
        gfx_FillCircle(p.x, p.y - 1, 5);
    }
}

void update_powerups() {
    for (auto &p : powerup) {
        if (!p.active) continue;
        gfx_SetColor(random_color());
        gfx_FillCircle(p.x, p.y, 3);
        p.y += 1;
        if (p.y >= 235) {
            p.active = false;
        }
    }
}

int main() {
    char buf[1];
    gfx_Begin();
    srand(rtc_Time());
    gfx_SetDrawBuffer();
    gfx_FillScreen(0);
    gfx_SwapDraw();
    gfx_FillScreen(0);

    //box spawn loop
    int lives = 3;
    generate_connected_level();

    gfx_SetColor(255);
    bool allBallsInactive = false;
    bool isBallSpawned = false;
    while(true) {
        kb_Scan();
        if (kb_Data[7] & kb_Left) {
            paddle.x -= 4;
            if (paddle.x <= 4) {
                paddle.x = 4;
            }
        }
        if (kb_Data[7] & kb_Right) {
            paddle.x += 4;
            if (paddle.x > 276) {
                paddle.x = 276;
            }
        }
        if (kb_Data[7] & kb_Up && isBallSpawned == false) {
            spawn_ball(paddle.x + 10, paddle.y - 10, randInt(1,2) == 2 ? 1 : -1, -2);

            isBallSpawned = true;
        }

        clear();
        gfx_SetColor(255);
        draw_paddle(paddle.x, paddle.y);

        // ball draw
        if (lives<=0) {
            gfx_FillScreen(0);
            gfx_SetTextTransparentColor(0);
            gfx_SetTextBGColor(0);
            gfx_SetTextFGColor(0xFF);
            gfx_PrintStringXY("Game Over", 120, 120);
            gfx_SetTextTransparentColor(255);
            gfx_SetTextBGColor(255);
            gfx_SwapDraw();
            pause();
            break;
        }
        for (auto &p : powerup) {
            if (!isBallSpawned) {
                if (p.active) {
                    p.active = false;
                    gfx_SetColor(0);
                    gfx_FillCircle(p.x, p.y - 1, 5);
                }
            }
        }
        if (isBallSpawned == true) {
            allBallsInactive = true;
            for (auto &ball : balls) {
                if (ball.active) {
                    allBallsInactive = false;
                    break; // stop early — found one active
                }
            }
            if (allBallsInactive == true) {
                isBallSpawned = false;
                lives--;
            }
            for (auto &p : powerup) {
                if (p.x >= paddle.x && p.x <= paddle.x + 40 ) {
                    if (p.y >= paddle.y){
                        p.active = false;
                        generate_powerup();
                    }
                }
            }
            for (auto & ball : balls) {
                if (ball.active == false) continue;
                update_ball(&ball);
                draw_ball(&ball);
                if (ball.y >= paddle.y - 3 - ball.radius && ball.y <= paddle.y - ball.radius) {

                    if (ball.x >= paddle.x && ball.x <= paddle.x + 20) {
                        if (!ball.pHit) {
                            if (ball.incX == 0) ball.incX = (randInt(1,2) == 1) ? 1 : -1;
                            ball.incY = -1;
                            ball.incX = -1;
                            ball.pHit = true;
                        }
                    }else if (ball.x >= paddle.x + 20 && ball.x <= paddle.x + 40) {
                        if (!ball.pHit) {
                            if (ball.incX == 0) ball.incX = (randInt(1,2) == 1) ? 1 : -1;
                            ball.incY = -1;
                            ball.incX = 1;
                            ball.pHit = true;
                        }
                    }
                }


            }
            // box draw
            draw_box();
            update_powerups();
            for (auto &boxe : boxes) {
                if (!boxe.active) continue;
                for (auto &ball : balls) {
                    if (!ball.active) continue;
                    if (ball.x >= boxe.x && ball.x <= boxe.x + boxe.w &&
                        ball.y >= boxe.y && ball.y <= boxe.y + boxe.h) {
                        int prevX = ball.x - ball.incX;
                        if (prevX < boxe.x || prevX > boxe.x + boxe.w){
                            ball.incX *= -1;
                            ball.pHit = false;
                        }
                        else {
                            ball.pHit = false;
                            ball.incY *= -1;
                        }
                        spawn_powerup(boxe.x, boxe.y, MULTIBALL);
                        boxe.active = false;
                        }
                }
            }
        }
        gfx_SetTextTransparentColor(0);
        gfx_SetTextBGColor(0);
        gfx_SetTextFGColor(0xFF);
        boot_sprintf(buf, "%d", lives);
        gfx_PrintStringXY("Lives: ", 5, 10);
        gfx_PrintStringXY(buf, 50, 10);
        gfx_SetTextTransparentColor(255);
        gfx_SetTextBGColor(255);
        gfx_SwapDraw();
    }
    gfx_End();
}

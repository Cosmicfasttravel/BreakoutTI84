#include "asteroids.h"
#include "entities.h"
#include "levels.h"
#include "powerups.h"

#include <ti/getcsc.h>
#include <ti/sprintf.h>
#include <graphx.h>
#include <keypadc.h>
#include <sys/rtc.h>
#include <sys/util.h>

#include "menu.h"
#include "ui.h"

void pause() {
    while (!os_GetCSC()) {}
}
int game() {
    static renderingMode renderMode = {};
    //initialize
    srand(rtc_Time());
    int currentLevel = 0;
    gfx_Begin();
    if (!main_menu(&renderMode)) {
        gfx_End();
        return 0;
    }
    gfx_SetDrawBuffer();
    gfx_FillScreen(0);
    gfx_SwapDraw();
    gfx_FillScreen(0);
    lives = 3;
    //box spawn loop
    if (level == 0) {
        generate_connected_level(1);
        currentLevel = 0;
    }else if (level == 1) {
        load_level(level1);
        currentLevel = 1;
    }else {

    }
    draw_box();
    gfx_SwapDraw();
    draw_box();
    gfx_SetColor(255);
    bool allBallsInactive = false;
    bool isBallSpawned = false;
    bool allBoxesInactive = false;

    while(true) {
        //key checks
        kb_Scan();
        if (kb_Data[7] & kb_Left) {
            paddle.x -= 4;
            if (paddle.x <= 4) {
                paddle.x = 4;
            }
        }
        if (kb_Data[7] & kb_Right) {
            paddle.x += 4;
            if (paddle.x > 316-paddle.w) {
                paddle.x = 316-paddle.w;
            }

        }
        if (kb_Data[7] & kb_Up && isBallSpawned == false) {
            spawn_ball(paddle.x + 10, paddle.y - 10, randInt(1,2) == 2 ? 1 : -1, -2);
            isBallSpawned = true;
        }

        //game over
        if (lives<=0) {
            gfx_FillScreen(0);
            gfx_SetTextTransparentColor(0);
            gfx_SetTextBGColor(0);
            gfx_SetTextFGColor(0xFF);
            gfx_PrintStringXY("Game Over", 120, 120);
            gfx_SetTextTransparentColor(255);
            gfx_SetTextBGColor(255);
            gfx_SwapDraw();
            gfx_End();
            break;
        }

        //I actually don't know :(
        for (auto &p : powerup) {
            if (!isBallSpawned) {
                if (p.active) {
                    p.active = false;
                    gfx_SetColor(0);
                    gfx_FillCircle(p.x, p.y - 1, 5);
                }
            }
        }


        if (!isBallSpawned) {
            gfx_SetColor(0);
            clear_misc();
            gfx_SetColor(255);
            draw_paddle(paddle.x, paddle.y);
        }
        //make sure there are still balls before pausing
        if (isBallSpawned) {
            gfx_SetColor(0);
            if (renderMode == SLOW) {
                clear_box();
            }
            clear_ball();
            clear_misc();
            clear_powerups();
            for (auto &boxes : boxes) {
                if (!boxes.active) {gfx_FillRectangle_NoClip(boxes.x, boxes.y, boxes.w, boxes.h);}
            }
            gfx_SetColor(255);
            draw_paddle(paddle.x, paddle.y);

            allBallsInactive = true;
            for (auto &ball : balls) {
                if (ball.active) {
                    allBallsInactive = false;
                    break; // stop early — found one active
                }
            }
            allBoxesInactive = true;
            for (auto &boxes : boxes) {
                if (boxes.active) {
                    allBoxesInactive = false;
                    break; // stop early — found one active
                }
            }
            if (allBoxesInactive) {
                if (currentLevel == 1) {
                    load_level(level2);
                    currentLevel = 2;
                }
                else if (currentLevel == 2) {
                    load_level(level3);
                    currentLevel = 3;
                }
                if (currentLevel == 0) {
                    game();
                }

            }

            //live decrement
            if (allBallsInactive == true) {
                isBallSpawned = false;
                lives--;
            }

            //powerup collecting
            for (auto &p : powerup) {
                if (!p.active) continue;
                if (p.x >= paddle.x && p.x <= paddle.x + paddle.w ) {
                    if (p.y >= paddle.y){
                        p.active = false;
                        generate_powerup(&p ,&lives);
                    }
                }
            }

            //ball paddle collisions
            for (auto & ball : balls) {
                if (ball.active == false) continue;
                update_ball(&ball);
                draw_ball(&ball);
                if (ball.y >= paddle.y - 3 - ball.radius && ball.y <= paddle.y - ball.radius) {
                    if (ball.x >= paddle.x && ball.x <= paddle.x + 0.5*paddle.w) {
                        if (!ball.pHit) {
                            if (ball.incX == 0) ball.incX = (randInt(1,2) == 1) ? 1 : -1;
                            ball.incY = -1 * static_cast<int>randInt(1, 2);
                            ball.incX = -1 * static_cast<int>randInt(1, 2);
                            ball.pHit = true;
                        }
                    }else if (ball.x >= paddle.x + 0.5*paddle.w && ball.x <= paddle.x + paddle.w) {
                        if (!ball.pHit) {
                            if (ball.incX == 0) ball.incX = (randInt(1,2) == 1) ? 1 : -1;
                            ball.incY = -1 * static_cast<int>randInt(1, 2);
                            ball.incX = 1 * static_cast<int>randInt(1, 2);
                            ball.pHit = true;
                        }
                    }
                }
            }

            // box draw
            if (renderMode == SLOW) {
                draw_box();
            }
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

                        switch (randInt(1,30)) {
                            case 1:
                                spawn_powerup(boxe.x, boxe.y, MULTIBALL);
                                break;
                            case 2:
                                spawn_powerup(boxe.x, boxe.y, EXTRA_LIFE);
                                break;
                            case 3:
                                spawn_powerup(boxe.x, boxe.y, WIDE_PADDLE);
                                break;
                            default:;
                        }
                        if (renderMode == FAST) {
                            gfx_SetColor(0);
                            gfx_FillRectangle_NoClip(boxe.x, boxe.y, boxe.w, boxe.h);
                        }
                        boxe.active = false;
                        }
                }
            }
        }
        lives_text();
    }
    return 0;
}
int main() {
    game();
}

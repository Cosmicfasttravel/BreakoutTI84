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

int main() {
    //initialize
    gfx_Begin();
    if (!main_menu()) {
        gfx_End();
        return 0;
    }
    srand(rtc_Time());
    gfx_SetDrawBuffer();
    gfx_FillScreen(0);
    gfx_SwapDraw();
    gfx_FillScreen(0);
    lives = 3;
    //box spawn loop
    generate_connected_level();

    gfx_SetColor(255);
    bool allBallsInactive = false;
    bool isBallSpawned = false;
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

        //normal clears
        clear_box();
        clear_ball();
        clear_misc();
        clear_powerups();

        gfx_SetColor(255);
        draw_paddle(paddle.x, paddle.y);

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

        //make sure there are still balls before pausing
        if (isBallSpawned == true) {
            allBallsInactive = true;
            for (auto &ball : balls) {
                if (ball.active) {
                    allBallsInactive = false;
                    break; // stop early — found one active
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

                        boxe.active = false;
                        }
                }
            }
        }
        lives_text();

    }

}

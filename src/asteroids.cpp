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
    while (!os_GetCSC()) {
    }
}

int game() {
    bool reset = true;
    bool allBallsInactive = false;
    bool isBallSpawned = false;
    bool allBoxesInactive = false;
    static renderingMode renderMode = {};
    int currentLevel = -1;
    gfx_Begin();
    srand(rtc_Time());
    gfx_PrintInt(rtc_Time(), 9);
    pause();
    gfx_SetDrawBuffer();
    while (true) {
        if (reset) {
            delete_balls();
            reset = false;
            //initialize
            if (!main_menu(&renderMode)) {
                return 0;
            }
            gfx_FillScreen(0);
            gfx_BlitBuffer();
            lives = 3;
            if (level == -1) {
                generate_connected_level(1);
                currentLevel = 0;
            } else if (level == 1) {
                load_level(level1);
                currentLevel = 1;
            } else if (level == 2) {
                load_level(level2);
                currentLevel = 2;
            }else if (level == 3) {
                load_level(level3);
                currentLevel = 3;
            }
            else {
                gfx_FillScreen(255);
                gfx_PrintStringXY("You didn't create a level", 80, 120);
                gfx_BlitBuffer();
                pause();
                reset = true;
            }
            draw_box();
            gfx_SetColor(255);

        } else {
            while (true) {
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
                    if (paddle.x > 316 - paddle.w) {
                        paddle.x = 316 - paddle.w;
                    }
                }
                if (kb_Data[7] & kb_Up && isBallSpawned == false) {
                    spawn_ball(paddle.x + 10, paddle.y - 10, randInt(1, 2) == 2 ? 1 : -1, -2);
                    isBallSpawned = true;
                }

                if (kb_Data[6] & kb_Clear && pause_menu()) {
                    gfx_SwapDraw();
                    reset = true;
                    break;
                }
                //game over
                if (lives <= 0) {
                    gfx_FillScreen(0);
                    gfx_SetTextTransparentColor(0);
                    gfx_SetTextBGColor(0);
                    gfx_SetTextFGColor(0xFF);
                    gfx_PrintStringXY("Game Over", 120, 120);
                    gfx_SetTextTransparentColor(255);
                    gfx_SetTextBGColor(255);
                    gfx_SwapDraw();
                    reset = true;
                    break;
                }


                //I actually don't know :(
                for (auto &p: powerup) {
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

                    gfx_SetColor(255);
                    draw_paddle(paddle.x, paddle.y);

                    allBallsInactive = true;
                    for (auto &ball: balls) {
                        if (ball.active) {
                            allBallsInactive = false;
                            break; // stop early — found one active
                        }
                    }
                    allBoxesInactive = true;
                    for (auto &boxes: boxes) {
                        if (boxes.active) {
                            allBoxesInactive = false;
                            break; // stop early — found one active
                        }
                    }
                    if (allBoxesInactive) {
                        if (currentLevel == 1) {
                            load_level(level2);
                            currentLevel = 2;
                        } else if (currentLevel == 2) {
                            load_level(level3);
                            currentLevel = 3;
                        }
                        if (currentLevel == 0) {
                            reset = true;
                            break;
                        }
                    }

                    //live decrement
                    if (allBallsInactive == true) {
                        isBallSpawned = false;
                        lives--;
                    }

                    //powerup collecting
                    for (auto &p: powerup) {
                        if (!p.active) continue;
                        if (p.x >= paddle.x && p.x <= paddle.x + paddle.w) {
                            if (p.y >= paddle.y) {
                                p.active = false;
                                generate_powerup(&p, &lives);
                            }
                        }
                    }

                    //ball paddle collisions
                    for (auto &ball: balls) {
                        if (ball.active == false) continue;
                        update_ball(&ball);
                        draw_ball(&ball);
                        if (ball.y >= paddle.y - ball.radius && ball.y <= paddle.y + ball.radius) {
                            if (ball.x >= paddle.x && ball.x <= paddle.x + 0.5 * paddle.w) {
                                if (!ball.pHit) {
                                    if (ball.incX == 0) ball.incX = (randInt(1, 2) == 1) ? 1 : -1;
                                    ball.incY = -1 * static_cast<int>randInt(1, 2);
                                    ball.incX = -1 * static_cast<int>randInt(1, 2);
                                    ball.pHit = true;
                                }
                            } else if (ball.x >= paddle.x + 0.5 * paddle.w && ball.x <= paddle.x + paddle.w) {
                                if (!ball.pHit) {
                                    if (ball.incX == 0) ball.incX = (randInt(1, 2) == 1) ? 1 : -1;
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
                        update_powerups_slow();
                    } else {
                        update_powerups_fast();
                    }

                    for (auto &boxe: boxes) {
                        if (!boxe.active) continue;
                        for (auto &ball: balls) {
                            if (!ball.active) continue;
                            if (ball.x >= boxe.x && ball.x <= boxe.x + boxe.w &&
                                ball.y >= boxe.y && ball.y <= boxe.y + boxe.h) {
                                int prevX = ball.x - ball.incX;
                                if (prevX < boxe.x || prevX > boxe.x + boxe.w) {
                                    ball.incX *= -1;
                                    ball.pHit = false;
                                } else {
                                    ball.pHit = false;
                                    ball.incY *= -1;
                                }

                                switch (randInt(1, 30)) {
                                    case 1:
                                        if (renderMode == SLOW) {
                                            spawn_powerup(boxe.x, boxe.y, MULTIBALL);
                                        } else {
                                            spawn_powerup(randInt(1, 319), 180, MULTIBALL);
                                        }
                                        break;
                                    case 2:
                                        if (renderMode == SLOW) {
                                            spawn_powerup(boxe.x, boxe.y, EXTRA_LIFE);
                                        } else {
                                            spawn_powerup(randInt(1, 319), 180, EXTRA_LIFE);
                                        }
                                        break;
                                    case 3:
                                        if (renderMode == SLOW) {
                                            spawn_powerup(boxe.x, boxe.y, WIDE_PADDLE);
                                        } else {
                                            spawn_powerup(randInt(1, 319), 180, WIDE_PADDLE);
                                        }
                                        break;
                                    default: ;
                                }
                                boxe.active = false;
                                if (renderMode == FAST) {
                                    clear_box();
                                    draw_box();
                                    gfx_SetColor(0);
                                }
                            }
                        }
                    }
                }

                lives_text();
                gfx_BlitBuffer();
            }
        }
    }
}

int main() {
    game();
    gfx_End();
}

#include "menu.h"
#include <keypadc.h>

#include "entities.h"
#include "../../include/graphx.h"
#include "../../include/ti/getcsc.h"
//box
int level1[BOX_ROWS][BOX_COLS] = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
};
// Level 2 - Pyramid
int level2[BOX_ROWS][BOX_COLS] = {
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
};
// Level 3 - Smiley Face
int level3[BOX_ROWS][BOX_COLS] = {
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int main_menu(renderingMode *mode) {
    menuOption = MENU_START;
    while (true) {
        // Draw menu
        gfx_FillScreen(255);
        gfx_SetTextFGColor(0);
        gfx_SetTextScale(2, 2);
        gfx_PrintStringXY("Breakout TI-84", 10, 20);
        gfx_PrintStringXY("_______________", 10, 22);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY((menuOption == MENU_START) ? "-> Start" : "   Start", 60, 100);
        gfx_PrintStringXY((menuOption == MENU_OPTIONS) ? "-> Options" : "   Options", 60, 120);
        gfx_PrintStringXY((menuOption == MENU_LEVELS) ? "-> Levels" : "   Levels", 60, 140);
        gfx_PrintStringXY((menuOption == MENU_EXIT) ? "-> Exit" : "   Exit", 60, 160);
        gfx_BlitBuffer();

        // Get input
        sk_key_t key;
        while (!((key = os_GetCSC()))) {
        }
        switch (key) {
            case sk_Up:
                menuOption = static_cast<MenuOption>((menuOption - 1 + 4) % 4);
                break;
            case sk_Down:
                menuOption = static_cast<MenuOption>((menuOption + 1) % 4);
                break;
            case sk_Enter:
                if (menuOption == MENU_EXIT) return 0;
                if (menuOption == MENU_OPTIONS) {
                    options_menu(mode);
                    menuOption = MENU_OPTIONS;
                }
                if (menuOption == MENU_START) return 1; // Start game
                if (menuOption == MENU_LEVELS) {
                    levels_menu();
                    menuOption = MENU_LEVELS;
                }
            default:
                break; // Ignore other keys
        }
    }
}

int options_menu(renderingMode *mode) {
    static bool options1 = true;

    while (true) {
        gfx_FillScreen(255);
        gfx_SetTextFGColor(0);
        gfx_SetTextScale(2, 2);
        gfx_PrintStringXY("Options", 10, 20);
        gfx_PrintStringXY("_______________", 10, 22);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY((options == OPTIONS_1) ? "-> Fast Render: " : "   Fast render: ", 60, 100);
        gfx_PrintStringXY((options1) ? "   On" : "   Off", 160, 100);
        gfx_PrintStringXY((options == OPTIONS_2) ? "-> Theme" : "   Theme", 60, 120);
        if (theme == WARM) {
            gfx_PrintStringXY("Warm", 160, 120);
        }
        if (theme == COOL) {
            gfx_PrintStringXY("Cool", 160, 120);
        }
        if (theme == GRAYSCALE) {
            gfx_PrintStringXY("Grayscale", 160, 120);
        }
        if (theme == RANDOM) {
            gfx_PrintStringXY("Random", 160, 120);
        }
        if (theme == CREATE) {
            gfx_PrintStringXY("Created theme", 160, 120);
        }
        gfx_PrintStringXY((options == OPTIONS_3) ? "-> Create theme" : "   Create theme", 60, 140);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY("2nd to quit", 235, 229);
        gfx_Rectangle(230, 225, 80, 15);
        gfx_BlitBuffer();
        sk_key_t key;
        while (!((key = os_GetCSC()))) {
        }
        switch (key) {
            case sk_Up:
                options = static_cast<Options>((options - 1 + 3) % 3);
                break;
            case sk_Down:
                options = static_cast<Options>((options + 1) % 3);
                break;
            case sk_Enter:
                if (options == OPTIONS_1) {
                    if (*mode == SLOW) {
                        *mode = FAST;
                    } else {
                        *mode = SLOW;
                    }
                    options1 = !options1;
                }
                if (options == OPTIONS_2) {
                    theme = static_cast<ThemeOptions>((theme + 1) % 5);
                }
                if (options == OPTIONS_3) {
                    create_theme();
                }

                break;
            case sk_2nd:
                return 0;
            default:
                break; // Ignore other keys
        }
    }
}

int levels_menu() {
    while (true) {
        gfx_FillScreen(255);
        gfx_SetTextFGColor(0);
        gfx_SetTextScale(2, 2);
        gfx_PrintStringXY("Levels", 10, 20);
        gfx_PrintStringXY("_______________", 10, 22);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY((levelOption == LOPTION_0) ? "-> Random level" : "   Random level", 60, 80);
        gfx_PrintStringXY((levelOption == LOPTION_1) ? "-> Level 1" : "   Level 1", 60, 100);
        gfx_PrintStringXY((levelOption == LOPTION_2) ? "-> Level 2" : "   Level 2", 60, 120);
        gfx_PrintStringXY((levelOption == LOPTION_3) ? "-> Level 3" : "   Level 3", 60, 140);
        gfx_PrintStringXY((levelOption == LCREATED) ? "-> Created Level" : "   Created Level", 60, 160);
        gfx_PrintStringXY((levelOption == LPREVIEW) ? "-> Preview" : "   Preview", 60, 180);
        gfx_PrintStringXY((levelOption == LCREATE) ? "-> Create" : "   Create", 60, 200);
        gfx_PrintStringXY((levelOption == LSAVE) ? "-> Save" : "   Save", 200, 80);
        gfx_PrintStringXY((levelOption == LLOAD) ? "-> Load" : "   Load", 200, 100);
        if (level != -1 && level != 5 && level != 6 && level != 4 && level != 7 && level != 8) {
            // make sure 4 is preview value
            gfx_PrintStringXY("Level selected: ", 30, 50);
            gfx_SetTextXY(140, 50);
            gfx_PrintInt(level, 1);
        } else if (level == -1) {
            gfx_PrintStringXY("Level selected: Random level", 30, 50);
        }
        else if (level == 4) {
            gfx_PrintStringXY("Level selected: Created Level", 30, 50);
        }
        gfx_PrintStringXY("________________________________________", 0, 51);


        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY("2nd to quit", 235, 229);
        gfx_Rectangle(230, 225, 80, 15);
        gfx_BlitBuffer();
        sk_key_t key;
        while (!((key = os_GetCSC()))) {
        }
        switch (key) {
            case sk_Up:
                levelOption = static_cast<LevelOptions>((levelOption - 1 + 9) % 9);
                break;
            case sk_Down:
                levelOption = static_cast<LevelOptions>((levelOption + 1) % 9);
                break;
            case sk_Enter:
                if (levelOption != LPREVIEW && levelOption != LCREATE && levelOption != LSAVE && levelOption != LLOAD) {
                    level = static_cast<int>(levelOption) == 0 ? -1 : static_cast<int>(levelOption);
                }
                else if (levelOption == LPREVIEW) {
                    preview_level(level);
                }
                else if (levelOption == LCREATE) {
                    create_level();
                }
                else if (levelOption == LSAVE) {
                    create_level_in_list();
                }
                else if (levelOption == LLOAD) {
                    load_level_from_list();
                }
                break;
            case sk_2nd:
                return 0;
            default:
                break; // Ignore other keys
        }
    }
}

void preview_level(int level) {
    gfx_SetTransparentColor(0);
    gfx_FillScreen(0);
    if (level == -1) {
        generate_connected_level(0);
        draw_box();
    }
    if (level == 1) {
        load_level(level1);
        draw_box();
    }
    if (level == 2) {
        load_level(level2);
        draw_box();
    }
    if (level == 3) {
        load_level(level3);
        draw_box();
    }
    if (level == 4) {
        load_created_level(createdLevelX, createdLevelY, boxNum);
        draw_box();
    }
    gfx_BlitBuffer();
    while (!os_GetCSC()) {
    }
}

bool pause_menu() {
    while (true) {
        gfx_FillScreen(0);
        gfx_SetTextFGColor(255);
        gfx_SetTextBGColor(0);
        gfx_SetTextTransparentColor(0);
        gfx_SetTransparentColor(0);
        gfx_SetTextScale(2, 2);
        gfx_PrintStringXY("Paused", 10, 20);
        gfx_PrintStringXY("_______________", 10, 22);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY((pauseOption == PAUSE_RESUME) ? "-> Resume" : "   Resume", 60, 100);
        gfx_PrintStringXY((pauseOption == PAUSE_EXIT) ? "-> Exit" : "   Exit", 60, 160);
        gfx_BlitBuffer();

        sk_key_t key;
        do {
            key = os_GetCSC();
        } while (key == 0); // wait for key press

        switch (key) {
            case sk_Up:
                pauseOption = static_cast<PauseOptions>((pauseOption - 1 + 2) % 2);
                break;
            case sk_Down:
                pauseOption = static_cast<PauseOptions>((pauseOption + 1) % 2);
                break;
            case sk_Enter:
                if (pauseOption == PAUSE_RESUME) {
                    gfx_FillScreen(0);
                    draw_box();
                    return false;
                }
                if (pauseOption == PAUSE_EXIT) {
                    gfx_FillScreen(255);
                    gfx_SetTextFGColor(0);
                    gfx_SetTextBGColor(255);
                    gfx_SetTextTransparentColor(255);
                    gfx_SetTransparentColor(255);
                    return true;
                }
                break;
            default:
                break; // Ignore other keys
        }
    }
}

void create_theme() {
    int boxNum = 0;
    for (int i = 0; i < 255; i++) {
        createdTheme[i] = 0;
    }

    while (boxNum < 255) {
        char inputStr[4] = "";
        int inputNum = 0;
        int curDigit = 0;
        bool entering = true;

        while (entering) {
            gfx_FillScreen(0);
            gfx_SetTextFGColor(255);
            gfx_SetTextBGColor(0);
            gfx_SetTextTransparentColor(0);
            gfx_SetTransparentColor(0);
            gfx_SetTextScale(1, 1);
            gfx_PrintStringXY("Theme Creator", 10, 20);
            gfx_PrintStringXY("_____________________________________", 13, 22);
            gfx_PrintStringXY("Enter color (0-255) for box ", 10, 80);
            gfx_SetTextXY(210, 80);
            gfx_PrintInt(boxNum + 1, 3);
            gfx_SetColor(inputNum);
            gfx_FillRectangle(10, 30, 300, 30);
            gfx_SetColor(255);
            gfx_PrintStringXY("Input: ", 10, 100);
            gfx_PrintStringXY(inputStr, 60, 100);

            gfx_SetTextScale(1, 1);
            gfx_PrintStringXY("Del to delete", 10, 140);
            gfx_PrintStringXY("2nd to quit", 235, 229);
            gfx_Rectangle(230, 225, 80, 15);
            gfx_BlitBuffer();

            sk_key_t key;
            do {
                key = os_GetCSC();
            } while (key == 0);

            int digit = -1;
            switch (key) {
                case sk_0: digit = 0;
                    break;
                case sk_1: digit = 1;
                    break;
                case sk_2: digit = 2;
                    break;
                case sk_3: digit = 3;
                    break;
                case sk_4: digit = 4;
                    break;
                case sk_5: digit = 5;
                    break;
                case sk_6: digit = 6;
                    break;
                case sk_7: digit = 7;
                    break;
                case sk_8: digit = 8;
                    break;
                case sk_9: digit = 9;
                    break;
                case sk_Del:
                    if (curDigit > 0) {
                        curDigit--;
                        inputStr[curDigit] = '\0';
                        inputNum /= 10;
                    }
                    break;
                case sk_Enter:
                    if (curDigit > 0 && inputNum <= 255) {
                        createdTheme[boxNum] = inputNum;
                        boxNum++;
                        entering = false; // Exit inner loop
                    }
                    break;
                case sk_2nd:
                    gfx_SetTextFGColor(0);
                    gfx_SetTextBGColor(255);
                    gfx_SetTextTransparentColor(255);
                    gfx_SetTransparentColor(255);
                    return;
                default:
                    break;
            }

            if (digit >= 0 && curDigit < 3) {
                int newNum = inputNum * 10 + digit;
                if (newNum <= 255) {
                    inputStr[curDigit] = '0' + digit;
                    curDigit++;
                    inputStr[curDigit] = '\0';
                    inputNum = newNum;
                }
            }
        }
    }

    gfx_SetTextFGColor(0);
    gfx_SetTextBGColor(255);
    gfx_SetTextTransparentColor(255);
    gfx_SetTransparentColor(255);
}

void create_level() {
    while (boxNum < 255) {
        int boxX = 0;
        int boxY = 0;
        while (true) {
            gfx_FillScreen(0);
            for (int i = 0; i < boxNum; i++) {
                gfx_SetColor(74);
                gfx_FillRectangle(createdLevelX[i], createdLevelY[i], 15, 10);
            }
            gfx_SetColor(107);
            gfx_FillRectangle(boxX, boxY, 15, 10);
            gfx_SetTextFGColor(255);
            gfx_SetTextBGColor(0);
            gfx_SetTextTransparentColor(0);
            gfx_SetTransparentColor(0);
            gfx_SetTextScale(1, 1);
            gfx_PrintStringXY("Level Creator", 10, 20);
            gfx_PrintStringXY("_____________________________________", 13, 22);

            gfx_SetTextXY(215, 80);
            gfx_SetColor(255);
            gfx_SetTextScale(1, 1);
            gfx_PrintStringXY("2nd to quit", 235, 229);
            gfx_Rectangle(230, 225, 80, 15);
            gfx_BlitBuffer();
            sk_key_t key;
            do {
                key = os_GetCSC();
            } while (key == 0);
            switch (key) {
                case sk_Left:
                    if (boxX >= 15) {
                        boxX -= 15;
                    }
                    break;
                case sk_Right:
                    if (boxX <= 305) {
                        boxX += 15;
                    }
                    break;
                case sk_Up:
                    if (boxY >= 10) {
                        boxY -= 10;
                    }
                    break;
                case sk_Down:
                    if (boxY <= 230) {
                        boxY += 10;
                    }
                    break;
                case sk_Enter:
                    createdLevelX[boxNum] = boxX;
                    createdLevelY[boxNum] = boxY;
                    boxNum++;
                    break;
                case sk_2nd:
                    gfx_SetTextFGColor(0);
                    gfx_SetTextBGColor(255);
                    gfx_SetTextTransparentColor(255);
                    gfx_SetTransparentColor(255);
                    return;
                default:
                    break;
            }
        }
    }
    gfx_SetTextFGColor(0);
    gfx_SetTextBGColor(255);
    gfx_SetTextTransparentColor(255);
    gfx_SetTransparentColor(255);
}

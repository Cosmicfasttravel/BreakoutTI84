#ifndef MENU_H
#define MENU_H

#include <ti/getcsc.h>
#include "levels.h"
#include "global.h"
enum MenuOption {
    MENU_START,
    MENU_OPTIONS,
    MENU_LEVELS,
    MENU_EXIT,
};
enum Options {
    OPTIONS_1,
    OPTIONS_2,
    OPTIONS_3,
};
enum LevelOptions {
    LOPTION_0 = 0,
    LOPTION_1 = 1,
    LOPTION_2 = 2,
    LOPTION_3 = 3,
    LPREVIEW,
};

static enum MenuOption menuOption;
static enum Options options;
static enum LevelOptions levelOption;
int main_menu();
int options_menu();
int levels_menu();
void preview_level(int level);

extern int level1[BOX_ROWS][BOX_COLS];
extern int level2[BOX_ROWS][BOX_COLS];
extern int level3[BOX_ROWS][BOX_COLS];

#endif //MENU_H

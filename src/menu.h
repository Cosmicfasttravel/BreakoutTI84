#ifndef MENU_H
#define MENU_H
#include "asteroids.h"
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

enum ColorOptions {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    PURPLE,
};

enum LevelOptions {
    LOPTION_0 = 0,
    LOPTION_1 = 1,
    LOPTION_2 = 2,
    LOPTION_3 = 3,
    LPREVIEW,
    LCREATE
};
enum PauseOptions {
    PAUSE_RESUME,
    PAUSE_EXIT,
};

enum XYOPTIONS {
    INPUTX,
    INPUTY
};

static enum MenuOption menuOption;
static enum Options options;
static enum LevelOptions levelOption;
static enum PauseOptions pauseOption;
static enum ColorOptions colorOption;
static enum XYOPTIONS xyOption;

int main_menu(renderingMode *mode);
int options_menu(renderingMode *mode);
int levels_menu();
void preview_level(int level);
void create_theme();
void create_level();
bool pause_menu();
extern int level1[BOX_ROWS][BOX_COLS];
extern int level2[BOX_ROWS][BOX_COLS];
extern int level3[BOX_ROWS][BOX_COLS];

#endif //MENU_H

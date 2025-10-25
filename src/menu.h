#ifndef MENU_H
#define MENU_H
#include <ti/getcsc.h>
enum MenuOption {
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT,
};
enum Options {
    OPTIONS_1,
    OPTIONS_2,
    OPTIONS_3,
};

static enum MenuOption menuOption;
int main_menu();
int options_menu();
#endif //MENU_H

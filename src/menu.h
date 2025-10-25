#ifndef MENU_H
#define MENU_H
#include <ti/getcsc.h>
enum MenuOption {
    MENU_NONE = 0,
    MENU_EXIT,
    MENU_START,
};

static enum MenuOption menuOption;
int main_menu();
void options_menu();
#endif //MENU_H

#include "menu.h"
#include <keypadc.h>
#include "../../include/graphx.h"

int main_menu() {
    if (menuOption == MENU_NONE) {
        menuOption = MENU_START;
    }
    gfx_FillScreen(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Breakout TI-84", 10, 20);
    gfx_PrintStringXY("_______________", 10, 22);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY((menuOption == MENU_START) ? "--(Start)--" : "Start", 60, 100);
    gfx_PrintStringXY((menuOption == MENU_EXIT) ? "--(Exit)--" : "Exit", 60, 120);

    while (!os_GetCSC()) {
    }
    switch (key) {
        case sk_Up:
            if (menuOption == MENU_EXIT) {
                menuOption = MENU_START;
            }else if (menuOption == MENU_START) {
                menuOption = MENU_EXIT;
            }
            main_menu();
            break;
        case sk_Down:
            if (menuOption == MENU_EXIT) {
                menuOption = MENU_START;
            }else if (menuOption == MENU_START) {
                menuOption = MENU_EXIT;
            }
            main_menu();
            break;
        case sk_Enter: {
            if (menuOption == MENU_EXIT) {
                gfx_End();
                return 0;
                break;
            }
            if (menuOption == MENU_START) {
                return 1;
                break;
            }
            break;
        }
        default: main_menu();
    }
}

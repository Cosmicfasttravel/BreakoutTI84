#include "menu.h"
#include <keypadc.h>
#include "../../include/graphx.h"
#include "../../include/ti/getcsc.h"

int main_menu() {
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
            gfx_PrintStringXY((menuOption == MENU_EXIT) ? "-> Exit" : "   Exit", 60, 140);
            gfx_SwapDraw();

            // Get input
            sk_key_t key;
            while (!((key = os_GetCSC()))) {}
            switch (key) {
                case sk_Up:
                    menuOption = static_cast<MenuOption>((menuOption - 1 + 3) % 3);
                    break;
                case sk_Down:
                    menuOption = static_cast<MenuOption>(abs((menuOption + 1) % 3));
                    break;
                case sk_Enter:
                    if (menuOption == MENU_EXIT) return 0;
                    if (menuOption == MENU_OPTIONS) {
                        options_menu();
                        menuOption = MENU_OPTIONS;
                    }
                    if (menuOption == MENU_START) return 1;  // Start game
                default:
                    break;  // Ignore other keys
            }
        }
    }

int options_menu() {
    while (true) {
        gfx_FillScreen(255);
        gfx_SetTextFGColor(0);
        gfx_SetTextScale(2, 2);
        gfx_PrintStringXY("Options", 10, 20);
        gfx_PrintStringXY("_______________", 10, 22);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY((menuOption == OPTIONS_1) ? "-> Option 1" : "   Option 1", 60, 100); // replace options with actual options
        gfx_PrintStringXY((menuOption == OPTIONS_2) ? "-> Option 2" : "   Option 2", 60, 120);
        gfx_PrintStringXY((menuOption == OPTIONS_3) ? "-> Option 3" : "   Option 3", 60, 140);
        gfx_SetTextScale(1, 1);
        gfx_PrintStringXY("2nd to quit", 235, 229);
        gfx_Rectangle(230, 225, 80, 15);
        gfx_SwapDraw();
        sk_key_t key;
        while (!((key = os_GetCSC()))) {}
        switch (key) {
            case sk_Up:
                menuOption = static_cast<MenuOption>((menuOption - 1 + 3) % 3);
                break;
            case sk_Down:
                menuOption = static_cast<MenuOption>(abs((menuOption + 1) % 3));
                break;
            case sk_Enter:
                break;
            case sk_2nd:
                return 0;
            default:
                break;  // Ignore other keys
        }
    }
}
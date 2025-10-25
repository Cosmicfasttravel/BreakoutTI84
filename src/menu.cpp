#include "menu.h"
#include <keypadc.h>
#include "../../include/graphx.h"

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
            gfx_PrintStringXY((menuOption == MENU_EXIT) ? "-> Exit" : "   Exit", 60, 120);
            gfx_SwapDraw();

            // Get input
            sk_key_t key;
            while (!(key = os_GetCSC()));
            switch (key) {
                case sk_Up:
                    menuOption = static_cast<MenuOption>((menuOption - 1) % 2);
                    break;
                case sk_Down:
                    menuOption = static_cast<MenuOption>((menuOption + 1) % 2);
                    break;
                case sk_Enter:
                    if (menuOption == MENU_EXIT) {
                        return 0;  // Exit game
                    }
                    return 1;  // Start game
                default:
                    break;  // Ignore other keys
            }
        }
    }
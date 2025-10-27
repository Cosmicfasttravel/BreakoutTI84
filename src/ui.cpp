#include "ui.h"
#include "global.h"
#include <ti/sprintf.h>

void lives_text() {
    char buf[3];
    gfx_SetTextTransparentColor(0);
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(0xFF);
    boot_sprintf(buf, "%d", lives);
    gfx_PrintStringXY("Lives: ", 5, 230);
    gfx_PrintStringXY(buf, 50, 230);
    gfx_SetTextTransparentColor(255);
    gfx_SetTextBGColor(255);
}
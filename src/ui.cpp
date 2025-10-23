#include "ui.h"
#include "global.h"
#include <ti/sprintf.h>

void lives_text() {
    char buf[1];
    gfx_SetTextTransparentColor(0);
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(0xFF);
    boot_sprintf(buf, "%d", lives);
    gfx_PrintStringXY("Lives: ", 5, 10);
    gfx_PrintStringXY(buf, 50, 10);
    gfx_SetTextTransparentColor(255);
    gfx_SetTextBGColor(255);
    gfx_SwapDraw();
}
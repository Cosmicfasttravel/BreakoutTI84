#include "global.h"
struct paddle paddle;
struct ball balls[MAX_BALLS];
struct powerups powerup[MAX_POWERUPS];
struct box boxes[MAX_BOXES];
enum renderingMode mode;
enum ThemeOptions theme;
//vars
int lives;
int level;
int boxNum;
int createdTheme[200];
uint16_t createdLevelX[200];
uint16_t createdLevelY[200];


#ifndef LEVELS_H
#define LEVELS_H

#include <sys/util.h>
#include "global.h"

void generate_connected_level(int create);
void load_level(const int levelData[BOX_ROWS][BOX_COLS]);


#endif //LEVELS_H

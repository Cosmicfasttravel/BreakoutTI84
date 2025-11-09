#ifndef LEVELS_H
#define LEVELS_H

#include <sys/util.h>
#include "global.h"

void generate_connected_level(int create);
void load_level(const int levelData[BOX_ROWS][BOX_COLS]);
void load_created_level(const int xCord[200], const int yCord[200]);

#endif //LEVELS_H

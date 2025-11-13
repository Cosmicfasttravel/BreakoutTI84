#ifndef LEVELS_H
#define LEVELS_H

#include <sys/util.h>
#include <fileioc.h>
#include "global.h"

void generate_connected_level(int create);
void load_level(const int levelData[BOX_ROWS][BOX_COLS]);
void load_created_level(const uint16_t xCord[200], const uint16_t yCord[200], int count);
void create_level_in_list(int levelSave);
void load_level_from_list(int levelSave);

#endif //LEVELS_H

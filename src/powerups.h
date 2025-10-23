#ifndef POWERUPS_H
#define POWERUPS_H

#include <cstdint>
#include <graphx.h>
#include <sys/util.h>
#include "global.h"

//functions
void generate_powerup(powerups *p, int *livPtr);
void spawn_powerup(int x, int y, powerupTypes type);
void clear_powerups();
void update_powerups();

#endif //POWERUPS_H

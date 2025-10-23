#ifndef GLOBAL_H
#define GLOBAL_H

#define START_X 30
#define START_Y 0
#define MAX_POWERUPS 5
#define BOX_COLS 18
#define BOX_ROWS 18
#define BOX_WIDTH 15
#define BOX_HEIGHT 10
#define MAX_BOXES 200
#define MAX_BALLS 3

#include <cstdint>
//enum
enum powerupTypes {
    MULTIBALL,
    WIDE_PADDLE,
    EXTRA_LIFE,
};
//structs
struct powerups {
    int x{};
    int y{};
    powerupTypes type{};
    bool active{};
};
struct paddle {
    uint16_t x = 160;
    uint8_t y = 220;
    uint8_t w = 40;
};
struct ball {
    uint16_t x{};
    uint8_t y{};
    uint8_t radius{};
    int incX{};
    int incY{};
    bool active{};
    bool pHit = false;
};
struct box {
    int x{};
    int y{};
    int w{};
    int h{};
    int c{};
    bool active = false;
};

//struct vars
extern struct paddle paddle;
extern struct ball balls[MAX_BALLS];
extern struct powerups powerup[MAX_POWERUPS];
extern struct box boxes[MAX_BOXES];

//global functions
uint16_t random_color();
void spawn_ball(int x, int y, int ix, int iy);
#endif //GLOBAL_H

#include "levels.h"





//color (cool)
uint16_t random_color() {
    int i = randInt(0,3);
    switch (i) {
        case 0:
            return 7;
        case 1:
            return 20;
        case 2:
            return 79;
        case 3:
            return 255;
        default:
            return 0;
    }
}
//very big random level creating through multidimensional array
void generate_connected_level() {
    for (auto & boxe : boxes) {
        boxe.active = false;
    }
    uint16_t maxBoxes = 20 + randInt(0,49);
    uint16_t startRow = 5 + randInt(0,9);
    uint16_t startCol = 5 + randInt(0,9);

    //map
    bool placed[BOX_ROWS][BOX_COLS] = {{false}};

    // start from one box
    int curRow = startRow;
    int curCol = startCol;
    placed[curRow][curCol] = true;
    int placedCount = 1;

    while (placedCount < maxBoxes) {
        constexpr int dirY[6] = { 0, 0, 1, -1, 2, -2};
        constexpr int dirX[6] = { 1, -1, 0, 0, 2, -2};
        int dir = randInt(0, 5);
        int newRow = curRow + dirY[dir];
        int newCol = curCol + dirX[dir];

        // keep within grid
        if (newRow >= 0 && newRow < BOX_ROWS && newCol >= 0 && newCol < BOX_COLS) {
            if (!placed[newRow][newCol]) {
                placed[newRow][newCol] = true;
                placedCount++;
            }
            curRow = newRow;
            curCol = newCol;
        }
    }

    // convert placed map into box coordinates
    int boxIndex = 0;
    for (int row = 0; row < BOX_ROWS; row++) {
        for (int col = 0; col < BOX_COLS; col++) {
            if (placed[row][col]) {
                boxes[boxIndex].x = START_X + col * BOX_WIDTH;
                boxes[boxIndex].y = START_Y + row * BOX_HEIGHT;
                boxes[boxIndex].w = BOX_WIDTH;
                boxes[boxIndex].h = BOX_HEIGHT;
                boxes[boxIndex].active = true;
                boxes[boxIndex].c = random_color();
                boxIndex++;
            }
        }
    }
}

void load_level(const int levelData[BOX_ROWS][BOX_COLS]) {
    // Clear all boxes first
    for (auto & boxe : boxes) {
        boxe.active = false;
    }

    // Read the level array and create boxes
    int boxIndex = 0;
    for (int row = 0; row < BOX_ROWS; row++) {
        for (int col = 0; col < BOX_COLS; col++) {
            if (levelData[row][col] == 1) {  // If there's a box here
                boxes[boxIndex].x = START_X + col * BOX_WIDTH;
                boxes[boxIndex].y = START_Y + row * BOX_HEIGHT;
                boxes[boxIndex].w = BOX_WIDTH;
                boxes[boxIndex].h = BOX_HEIGHT;
                boxes[boxIndex].active = true;
                boxes[boxIndex].c = random_color();
                boxIndex++;
            }
        }
    }
}
#include "levels.h"

#include <ti/getcsc.h>


//color (cool)
uint16_t random_color() {
    int i = randInt(0,3);
    if (theme == WARM) {
        switch (i) {
            case 0:
                return 226;
            case 1:
                return 231;
            case 2:
                return 232;
            case 3:
                return 192;
            default:
                return 255;
        }
    }
    if (theme == COOL) {
        switch (i) {
            case 0:
                return 18;
            case 1:
                return 5;
            case 2:
                return 30;
            case 3:
                return 152;
            default:
                return 255;
        }
    }
    if (theme == GRAYSCALE) {
        switch (i) {
            case 0:
                return 74;
            case 1:
                return 255;
            case 2:
                return 107;
            case 3:
                return 181;
            default:
                return 255;
        }
    }
    if (theme == RANDOM) {
        return randInt(2,253);
    }
    if (theme == CREATE) {
        for (int j = 0; j < 255; j++) {
            if (createdTheme[j] == 0) {
                i = randInt(0,j-1);
                break;
            }
            i = randInt(0,j);
        }
        return createdTheme[i];
    }
    return 255;
}
//very big random level creating through multidimensional array
void generate_connected_level(int create) {

    static bool placed[BOX_ROWS][BOX_COLS];
    if (create == 0) {
        for (auto & boxe : boxes) {
            boxe.active = false;
        }
        for (auto & row : placed) {
            for (bool & col : row) {
                col = false;
            }
        }
        uint16_t maxBoxes = 20 + randInt(0,49);
        uint16_t startRow = 5 + randInt(0,9);
        uint16_t startCol = 5 + randInt(0,9);

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
    else if (create == 1) {



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

void load_created_level(const uint16_t xCord[200], const uint16_t yCord[200], int count) {
    for (auto & boxe : boxes) {
        boxe.active = false;
    }

    for (int i = 0; i < count; i++) {
        boxes[i].x = xCord[i];
        boxes[i].y = yCord[i];
        boxes[i].w = BOX_WIDTH;
        boxes[i].h = BOX_HEIGHT;
        boxes[i].active = true;
        boxes[i].c = random_color();
    }
}
void create_level_in_list(int levelSave) {
    for (auto & boxe : boxes) {
        boxe.active = false;
    }
    ti_var_t appvar = 0;
    switch (levelSave) {
        case 1:
            appvar = ti_Open("LvlDat1", "w");
            gfx_PrintStringXY("Saved to level 1", 60, 60);
            gfx_BlitBuffer();
            while (!(os_GetCSC())) {}
            break;
        case 2:
            appvar = ti_Open("LvlDat2", "w");
            gfx_PrintStringXY("Saved to level 2", 60, 60);
            gfx_BlitBuffer();
            while (!(os_GetCSC())) {}
            break;
        case 3:
            appvar = ti_Open("LvlDat3", "w");
            gfx_PrintStringXY("Saved to level 3", 60, 60);
            gfx_BlitBuffer();
            while (!(os_GetCSC())) {}
            break;
        default: ;
    }


    // Write data
    ti_Write(&boxNum, sizeof(int), 1, appvar);
    ti_Write(createdLevelX, sizeof(uint16_t), boxNum, appvar);
    ti_Write(createdLevelY, sizeof(uint16_t), boxNum, appvar);

    // Close to save
    ti_Close(appvar);

}

void load_level_from_list(int levelSave) {
    for (auto & boxe : boxes) {
        boxe.active = false;
    }
    ti_var_t appvar = 0;
    switch (levelSave) {
        case 1:
            appvar = ti_Open("LvlDat1", "r");
            gfx_PrintStringXY("Loaded level 1", 60, 60);
            gfx_BlitBuffer();
            while (!(os_GetCSC())) {}
            break;
        case 2:
            appvar = ti_Open("LvlDat2", "r");
            gfx_PrintStringXY("Loaded level 2", 60, 60);
            gfx_BlitBuffer();
            while (!(os_GetCSC())) {}
            break;
        case 3:
            appvar = ti_Open("LvlDat3", "r");
            gfx_PrintStringXY("Loaded level 3", 60, 60);
            gfx_BlitBuffer();
            while (!(os_GetCSC())) {}
            break;
        default: ;
    }



    ti_Read(&boxNum, sizeof(int), 1, appvar);
    ti_Read(createdLevelX, sizeof(uint16_t), boxNum, appvar);
    ti_Read(createdLevelY, sizeof(uint16_t), boxNum, appvar);

    ti_Close(appvar);
}

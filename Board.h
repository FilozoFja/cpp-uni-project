//
// Created by kornel on 12/9/25.
//

#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H
#include <vector>

#include "Cell.h"


class Board {
private:
    int rows;
    int columns;
    bool boundsEnabled;
    std::vector<std::vector<Cell>> grid;
public:
    //Constructor
    Board(int rows, int columns, bool boundsEnabled);

    //Cell related
    Cell* getCell(int row, int col);
    std::vector<Cell *> getCellsAround(int row, int col);

    //Board size
    int getRows();
    int getCols();
};


#endif //UNTITLED_BOARD_H
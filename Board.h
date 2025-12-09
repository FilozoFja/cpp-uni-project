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
    Board(int rows, int columns, bool boundsEnabled);
    ~Board();

    Cell *getCell(int x, int y);
    Cell *getCellOverBounds(int x, int y);

};


#endif //UNTITLED_BOARD_H
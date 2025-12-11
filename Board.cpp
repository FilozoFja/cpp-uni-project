//
// Created by kornel on 12/9/25.
//

#include <vector>


#include "Board.h"
#include "Cell.h"

#include <stdexcept>

Board::Board(int rows, int columns, bool boundsEnabled) {
    if (rows < 0 and columns < 0) {
        throw std::invalid_argument("Board size must be >= 0 and <= 0");
    }

    this->rows = rows;
    this->columns = columns;
    this->boundsEnabled = boundsEnabled;

    grid.resize(rows);
    for (int i = 0; i < rows; i++) {
        grid[i].resize(columns);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j].setPos(i,j);
        }
    }
}
Board::~Board() {
    for (int i = 0; i < grid.size(); i++) {
        grid[i].clear();
    }
    grid.clear();
}

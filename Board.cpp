//
// Created by kornel on 12/9/25.
//

#include <vector>


#include "Board.h"
#include "Cell.h"

#include <stdexcept>

Board::Board(const int rows,const int columns,const bool boundsEnabled) {
    if (rows <= 0 || columns <= 0) {
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

Cell* Board::getCell(const int row, const int col) {
    if (row < 0 || row >= rows || col < 0 || col >= columns) {
        throw std::invalid_argument("row or col is out of bounds");
    }
    return &grid[row][col];
}

std::vector<Cell *> Board::getCellsAround(const int row, const int col) {
    std::vector<Cell *> cellsToReturn;
    cellsToReturn.reserve(8);

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;

            int nRow = row + dy;
            int nCol = col + dx;

            if (!boundsEnabled) {
                nRow = (nRow + rows) % rows;
                nCol = (nCol + columns) % columns;
            } else {
                if (nRow < 0 || nRow >= rows || nCol < 0 || nCol >= columns) {
                    continue;
                }
            }
            cellsToReturn.push_back(&grid[nRow][nCol]);
        }
    }
    return cellsToReturn;
}

int Board::getRows(){ return rows;}
int Board::getCols(){ return columns;}



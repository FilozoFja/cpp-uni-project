//
// Created by korne on 12/11/2025.
//

#include "Immune.h"

bool Immune::updateCell(Board& board, const std::vector<Cell *> cellToCheck ) {
    if (cellToCheck.empty()) {
        return false;
    }
    time -= 1;
    for (auto cell : cellToCheck) {
        if (cell -> getState() == IMMUNE and time <=0) {
            cell -> setState(HEALTHY);
        }
    }
    return true;
}
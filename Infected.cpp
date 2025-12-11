//
// Created by kornel on 12/9/25.
//

#include "Infected.h"

#include <cstdlib>

bool Infected::updateCell(Board& board, std::vector<Cell *> cellToCheck) {
    for (Cell* neightboor : cellToCheck) {
        if ( neightboor != nullptr and neightboor->getState() == HEALTHY) {
            if (rand() % 2 == 0) {
                neightboor->setState(INFECTED);
            }
        }
        this->time -= 1;
        if (neightboor != nullptr and neightboor -> getState() == INFECTED and time <= 0) {

        }
    }
}

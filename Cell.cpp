//
// Created by kornel on 12/9/25.
//

#include "Cell.h"

int Cell::getX()const {return x;}
int Cell::getY()const {return y;}
CellState Cell::getState()const {return state;}

void Cell::setPos(int newX, int newY) {
    x = newX;
    y = newY;
}

void Cell::setState(CellState newState) {
    state = newState;
}

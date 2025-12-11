#include "Cell.h"
#include <stdexcept>

void Cell::setPos(const int newX,const int newY) {
    x = newX;
    y = newY;
}

int Cell::getX() const { return x; }
int Cell::getY() const { return y; }

CellState Cell::getCurrentState() const {
    return currentState;
}

void Cell::swapNextStateToCurrent() {
    if (haveNextState()) {
        currentState = nextState;
        cleanNextState();
    }
}

void Cell::setNextState(const CellState newNextState) {
    if (nextState == UNDEFINED) {
        nextState = newNextState;
    } else {
        throw std::logic_error("Cell already has a next state assigned for this tick.");
    }
}

bool Cell::haveNextState() const {
    return nextState != UNDEFINED;
}

void Cell::cleanNextState() {
    nextState = UNDEFINED;
}
//
// Created by kornel on 12/9/25.
//

#ifndef UNTITLED_INFECTED_H
#define UNTITLED_INFECTED_H
#include "SkinProblem.h"


class Infected : public SkinProblem {
private:

public:
    Infected(Cell* cell, int infectionTime): SkinProblem(cell, infectionTime){}
    bool updateCell(Board &board, std::vector<Cell *> cellToCheck) override;
};

#endif //UNTITLED_INFECTED_H
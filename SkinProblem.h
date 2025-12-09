//
// Created by kornel on 12/9/25.
//

#ifndef UNTITLED_SKINPROBLEM_H
#define UNTITLED_SKINPROBLEM_H

#include <vector>

#include "Board.h"
#include "Cell.h"

class SkinProblem {
protected:
    Cell* cell;
    int time;
public:
    SkinProblem(Cell* cell, int time): cell(cell), time(time) {};
    virtual ~SkinProblem() {}
    virtual bool updateCell (Board& board, std::vector<Cell*> cellToCheck ) =0;
};


#endif //UNTITLED_SKINPROBLEM_H
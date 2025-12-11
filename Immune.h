//
// Created by korne on 12/11/2025.
//

#ifndef UNTITLED_IMMUNE_H
#define UNTITLED_IMMUNE_H
#include "SkinProblem.h"


class SkinProblem;
class Cell;

class Immune: public SkinProblem {
public:
    Immune(Cell* cell, int infectionTime): SkinProblem(cell, infectionTime){}
    bool updateCell(Board& board, std::vector<Cell *> cellToCheck ) override;
};


#endif //UNTITLED_IMMUNE_H
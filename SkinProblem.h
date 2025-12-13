//
// Created by kornel on 12/9/25.
//

#ifndef UNTITLED_SKINPROBLEM_H
#define UNTITLED_SKINPROBLEM_H

#include <vector>
class Board;
class Cell;

class SkinProblem {
protected:
    std::vector<Cell*> cells;
    int time;
public:
    //Constructor
    SkinProblem(Cell* originCell, int time) ;

    //Destructor
    virtual ~SkinProblem() = default;

    //Adding cell to vector
    void addCell(Cell* cell);

    //Getting list of cells because run is not inheriting from skinproblem
    std::vector<Cell*>& getCells();

    //Round time
    bool tick();

    //Adding one of two effect
    virtual void applyEffect(Board &board) =0;
};


#endif //UNTITLED_SKINPROBLEM_H


#ifndef UNTITLED_RUN_H
#define UNTITLED_RUN_H

#include <vector>
#include "Board.h"

class SkinProblem;

class Run {
private:
    Board board;
    std::vector<SkinProblem*> problems;

public:
    //Constructor
    Run(int rows, int cols);

    //Destructor to clean all pointers
    ~Run();

    //Main updating loop
    void updateGame();

    //GUI clicking input
    void spawnInfection(int r, int c);

};

#endif //UNTITLED_RUN_H
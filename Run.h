#ifndef UNTITLED_RUN_H
#define UNTITLED_RUN_H

#include <vector>
#include "Board.h"

class SkinProblem;

class Run {
private:
    Board board;
    std::vector<SkinProblem*> problems;

    int settingsInfectionTime;
    int settingsImmunityTime;

public:
    Run(int rows, int cols);
    ~Run();

    void updateGame();
    void spawnInfection(int r, int c);
    Board& getBoard();

    void setInfectionTime(int t);
    void setImmunityTime(int t);

    [[nodiscard]]int getInfectionTime() const;
    [[nodiscard]]int getImmunityTime() const;

    void setBoardBounds(bool enabled);
    [[nodiscard]]bool isBoundsEnabled() const;
};

#endif //UNTITLED_RUN_H
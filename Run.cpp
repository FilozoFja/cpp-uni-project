#include "Run.h"
#include "Infected.h"
#include "Immune.h"
#include "SkinProblem.h"

Run::Run(int rows, int cols)
    : board(rows, cols, true),
      settingsInfectionTime(5),
      settingsImmunityTime(10)
{
}

Run::~Run() {
    for (auto p : problems) delete p;
    problems.clear();
}

void Run::spawnInfection(int r, int c) {
    if (r < 0 || r >= board.getRows() || c < 0 || c >= board.getCols()) return;

    Cell* cell = board.getCell(r, c);
    if (cell->getCurrentState() == HEALTHY) {
        cell->setNextState(INFECTED);
        cell->swapNextStateToCurrent();
        cell->cleanNextState();

        problems.push_back(new Infected(cell, settingsInfectionTime));
    }
}

void Run::updateGame() {
    std::vector<SkinProblem*> remainingProblems;
    std::vector<SkinProblem*> newProblems;

    for (auto problem : problems) {
        problem->applyEffect(board);

        if (problem->tick()) {
            remainingProblems.push_back(problem);
        }
        else {
            std::vector<Cell*>& cells = problem->getCells();

            if (dynamic_cast<Infected*>(problem)) {
                for (Cell* c : cells) {
                    c->setNextState(IMMUNE);
                }
            }
            else if (dynamic_cast<Immune*>(problem)) {
                for (Cell* c : cells) {
                    c->setNextState(HEALTHY);
                }
            }
            delete problem;
        }
    }

    int rows = board.getRows();
    int cols = board.getCols();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            Cell* cell = board.getCell(r, c);

            if (cell->haveNextState()) {
                if (cell->getCurrentState() == HEALTHY) {
                    newProblems.push_back(new Infected(cell, settingsInfectionTime));
                }
                else if (cell->getCurrentState() == INFECTED) {
                    newProblems.push_back(new Immune(cell, settingsImmunityTime));
                }

                cell->swapNextStateToCurrent();
                cell->cleanNextState();
            }
        }
    }

    problems = remainingProblems;
    problems.insert(problems.end(), newProblems.begin(), newProblems.end());
}

Board& Run::getBoard(){ return board; }

void Run::setInfectionTime(const int t) { settingsInfectionTime = (t > 1) ? t : 1; }

void Run::setImmunityTime(const int t) { settingsImmunityTime = (t > 1) ? t : 1; }

int Run::getInfectionTime() const { return settingsInfectionTime; }

int Run::getImmunityTime() const { return settingsImmunityTime; }

void Run::setBoardBounds(bool enabled) { board.setBoundsEnabled(enabled); }

bool Run::isBoundsEnabled() const { return board.isBoundsEnabled(); }
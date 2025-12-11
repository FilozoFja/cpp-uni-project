//
// Created by kornel on 12/9/25.
//

#ifndef UNTITLED_CELL_H
#define UNTITLED_CELL_H

//Undefined = empty
enum CellState {UNDEFINED ,HEALTHY, IMMUNE, INFECTED};

class Cell {
private:
    int x,y;
    CellState currentState;
    CellState nextState;
public:
    //Constructor
    Cell(): x(0), y(0), currentState(HEALTHY), nextState(UNDEFINED) {}

    //Position
    void setPos(int newX, int newY);
    [[nodiscard]] int getX()const ;
    [[nodiscard]] int getY()const ;

    //Current state
    [[nodiscard]] CellState getCurrentState()const;

    //State swapper (
    void swapNextStateToCurrent();

    //Next state
    void setNextState(CellState newNextState);
    [[nodiscard]] bool haveNextState() const;
    void cleanNextState();

};


#endif //UNTITLED_CELL_H
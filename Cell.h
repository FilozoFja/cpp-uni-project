//
// Created by kornel on 12/9/25.
//

#ifndef UNTITLED_CELL_H
#define UNTITLED_CELL_H

enum CellState {HEALTHY, IMMUNE, INFECTED};

class Cell {
private:
    int x,y;
    CellState state;
public:
    Cell(): state(HEALTHY) {}
    void setPos(int newX, int newY);
    void setState(CellState newState);
    int getX()const ;
    int getY()const ;
    CellState getState()const;

};


#endif //UNTITLED_CELL_H
#include "MatrixSearchable.h"

MatrixSearchable::MatrixSearchable(vector<int> matrix, int n, int m, int initialState, int goalState):
    initialState(new State<int>(initialState, matrix[initialState])),
    goalState(new State<int>(goalState, matrix[goalState])) {
    this->matrix = matrix;
    this->row = n;
    this->column = m;

    for(int i = 0; i < this->matrix.size(); i++) {
        this->states.push_back(new State<int>(i, matrix[i]));
    }
}
State<int>* MatrixSearchable:: getInitialState() {
    return this->initialState;
}

State<int>* MatrixSearchable:: getGoalState(){
    return this->goalState;
}
list<State<int>*> MatrixSearchable::getAllPossibleStates(State<int>* s) {
    list<State<int>*> neighbors;
    int current = s->getState();
    if (current >= column && this->states[current - column]->getCost() != -1) { // upper neighbor
        neighbors.push_back(this->states[current - column]);
    }
    if (current < row * column - column && this->states[current + column]->getCost()!=-1) { // down neighbor
        neighbors.push_back(this->states[current + column]);
    }
    if (current % column != 0 && this->states[current - 1]->getCost()!=-1) { // left neighbor
        neighbors.push_back(this->states[current - 1]);
    }
    if (current % column != column - 1 && this->states[current + 1]->getCost()!=-1) { // right neighbor
        neighbors.push_back(this->states[current + 1]);
    }
    return neighbors;
}

int MatrixSearchable::getNumOfColumns(){
    return this->column;
}

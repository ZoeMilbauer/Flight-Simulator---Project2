#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H

#include <string>
using namespace std;
template <typename T> class State{
    T state;
    double cost;
    State<T>* cameFrom;
public:
    State(T state, double cost) {
        this->state = state;
        this->cost = cost;
        cameFrom = NULL;
    }
    bool equals(State<T> s) {
        return this->state == s.state;
    }
    T getState() {
        return this->state;
    }
    double getCost() {
        return this->cost;
    }
    State <T>* getCameFrom() {
        return this->cameFrom;
    }
    void setCameFrom(State<T>* s){
        this->cameFrom=s;
    }

};

#endif
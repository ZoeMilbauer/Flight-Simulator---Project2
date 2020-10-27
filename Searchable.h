#ifndef PROJECT2_SEARCHABLE_H
#define PROJECT2_SEARCHABLE_H

#include "State.h"
#include <list>

using namespace std;

template <typename T> class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual list<State<T>*> getAllPossibleStates(State<T>* s) = 0;
};

#endif

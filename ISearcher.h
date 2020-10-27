#ifndef PROJECT2_ISEARCHER_H
#define PROJECT2_ISEARCHER_H

#include "Searchable.h"
#include <vector>

template<typename T> class ISearcher {

public:
    // the search method
    virtual vector<T> search(Searchable<T>* searchable) = 0;

    // get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() = 0;

};

#endif
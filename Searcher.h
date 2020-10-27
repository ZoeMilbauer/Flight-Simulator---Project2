#ifndef PROJECT2_SEARCHER_H
#define PROJECT2_SEARCHER_H

#include "ISearcher.h"
#include "State.h"
#include "MyPriorityQueue.h"
template <typename T> class Searcher : public ISearcher<T> {

public:

    // the search method
    virtual vector<T> search(Searchable<T>* searchable) = 0;

    // get how many nodes were evaluated by the algorithm
    int getNumberOfNodesEvaluated() {
        return this->evaluateNodes;
    }
    int getCost() {
        return this->cost;
    }

protected:
    int cost=0;
    int evaluateNodes = 0;

    vector<T> reconstructPath(State<T> *current, State<T> *start) {
        vector<T> path;
        while (!current->equals(*start)) {
            path.insert(path.begin(), current->getState());
            this->cost+=current->getCost();
            current = current->getCameFrom();
        }
        path.insert(path.begin(), current->getState()); // insert the initial state
        return path;
    }


};

#endif
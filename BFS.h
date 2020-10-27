#ifndef PROJECT2_BFS_H
#define PROJECT2_BFS_H

#include "Searcher.h"
#include <queue>
#include <bits/stdc++.h>
using namespace std;

template <typename T> class BFS : public Searcher<T> {

public:
    bool isInVector(State<T> element, vector<State<T>> v) {

        for (typename std::vector<State<T>>::iterator it = v.begin();
             it != v.end(); it++) {
            if (element.equals(*it)) {
                return true;
            }
        }
        return false;
    }

    vector<T> search(Searchable<T>* searchable) {
        deque<State<T>*> queue;
        vector<State<T>> visited;
        // add start to queue
        queue.push_back(searchable->getInitialState());
        // add start to visited
        visited.push_back(*(searchable->getInitialState()));

        State<T>* node;
        list<State<T>*> successors;
        while (!queue.empty()) {
            this->evaluateNodes++;
            node = (queue.front());
            queue.pop_front();
            //path.push_back(node->getState());
            if (node->equals(*(searchable->getGoalState()))) {
                return this->reconstructPath(node, searchable->getInitialState());
            }
            successors = searchable->getAllPossibleStates(node);
            // go over each neighbor of node
            for (typename std::list<State<T>*>::iterator it = successors.begin(); it != successors.end(); it++) {
                if (!isInVector(*(*it), visited)) {
                    visited.push_back(*(*it));
                    (*it)->setCameFrom(node);
                    queue.push_back(*it);
                }
            }
        }
        // there is no path from start to goal
        vector<T> path;
        return path;
    };
};


#endif


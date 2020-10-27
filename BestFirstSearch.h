#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>
#include <algorithm>
using namespace std;
template<class T> class BestFirstSearch: public Searcher<T> {
public:


    class cmp {
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return left->getCost() < right->getCost();
        }
    };

    bool isInVector(State<T> element, vector<State<T>> v) {

        for (typename std::vector<State<T>>::iterator it = v.begin();
             it != v.end(); it++) {
            if (element.equals(*it)) {
                return true;
            }
        }
        return false;
    }


    State<T>* min(vector<State<T>*> open) {
        typename vector<State<T>*>:: iterator it = open.begin();
        State<T>* min = (*it);
        it++;
        while (it != open.end()) {
            if ((*it)->getCost() < min->getCost()) {
                min = (*it);
            }
            it++;
        }
        return min;
    }
    vector<T> search(Searchable<T>* searchable) {
        vector<State<T>*> open;
        vector<State<T>> visited;
        vector<State<T>> costs;
        // insert initial  state to open list
        open.push_back(searchable->getInitialState());
        State<T>* u;
        vector<T> path;
        list<State<T>*> succesors;
        while (!open.empty()) {
            this->evaluateNodes++;
           //auto min_it = min_element(open.begin(), open.end(), cmp());
            u = min(open);
           // u = *min_it;
            typename vector<State<T>*>::iterator it = find(open.begin(), open.end(), u);
            open.erase(it);
            if (u->equals(*(searchable->getGoalState()))) {
                // return path
                return this->reconstructPath(u, searchable->getInitialState());
            }
            else {
                succesors = searchable->getAllPossibleStates(u);
                for (typename list<State<T>*>::iterator i = succesors.begin(); i != succesors.end(); i++) {

                    if (!isInVector(*(*i), visited)) {
                        visited.push_back(*(*i));
                        open.push_back((*i));
                        (*i)->setCameFrom(u);
                    }
                }
            }
        }
        // there is no path from start to goal
        path.clear();
        return path;

    }


};

#endif

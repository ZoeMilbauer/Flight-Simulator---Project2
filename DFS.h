#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#include "Searcher.h"
#include <queue>

using namespace std;

template<typename T>
class DFS : public Searcher<T> {
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

    vector<T> search(Searchable<T> *searchable) {
        vector<State<T>> visited;
        vector<T> path;
        State<T>* goal = searchable->getGoalState();
        State<T>* init = searchable->getInitialState();
        return dfs(path, init, *goal, visited, searchable);
    }

    vector<T> dfs(vector<T> path, State<T>* current, State<T> goal, vector<State<T>> visited, Searchable<T> *searchable) {
        visited.push_back(*current);
        this->evaluateNodes++;
        if (current->equals(goal)) {
            path.push_back(current->getState());
            this->cost+= current->getCost();
            return path;
        }
        list<State<T>*> successors = searchable->getAllPossibleStates(current);
        // go over each neighbor of node
        for (typename std::list<State<T>*>::iterator it = successors.begin(); it != successors.end(); it++) {

            if (!isInVector(*(*it), visited)) {
                path.push_back(current->getState());
                vector<T> tempPath = dfs(path, (*it), goal, visited, searchable);
                if(!tempPath.empty()){
                    return tempPath;
                }
                else{
                    path.pop_back();
                }
            }
        }
        path.clear();
        return path; // no path to goal
    }


};

#endif

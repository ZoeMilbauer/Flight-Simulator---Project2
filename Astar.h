#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include "MatrixSearchable.h"
#include "Searcher.h"
#include <map>

class Astar : public Searcher<int> {
    int numOfColumns;
public:

    Astar(int numOfColumns) {
        this->numOfColumns = numOfColumns;
    }

    State<int> *nodeWithTheLeastCost(map<int, State<int> *> open, map<State<int> *, int> costs) {
        map<int, State<int> *>::iterator it = open.begin();
        State<int> *state = it->second;
        int min = costs[state];
        it++;
        while (it != open.end()) {
            if (costs[it->second] < min) {
                min = costs[it->second];
                state = it->second;
            }
            it++;
        }
        return state;
    }

    vector<int> search(Searchable<int> *searchable) {
        map<int, State<int> *> open;
        map<int, State<int> *> close;

        map<State<int> *, int> costFromStart;
        map<State<int> *, int> costs;

        open[0] = searchable->getInitialState();
        State<int> *current = searchable->getInitialState();
        costs[searchable->getInitialState()] = distanceToGoal(current, searchable->getGoalState());
        list<State<int> *> successors;
        while (!open.empty()) {
            current = nodeWithTheLeastCost(open, costs);
            this->evaluateNodes++;
            if (current->equals(*searchable->getGoalState())) {
                return reconstructPath(current, searchable->getInitialState());
            }

            successors = searchable->getAllPossibleStates(current);
            list<State<int> *>::iterator it = successors.begin();

            open.erase(current->getState());

            close[current->getState()] = current;
            while (it != successors.end()) {

                int successorG = costFromStart[current] + (*it)->getCost();
                int successorIndex = (*it)->getState();
                if (close.count(successorIndex) || (costFromStart.count(*it) && costFromStart[*it] <= successorG)) {
                    it++;
                    continue;
                }

                if (open.count(successorIndex) == 0 || (costFromStart.count(*it) && successorG < costFromStart[*it])) {
                    (*it)->setCameFrom(current);
                    costFromStart[*it] = successorG;
                    costs[*it] = costFromStart[*it] + distanceToGoal(*it, searchable->getGoalState());
                    if (open.count(successorIndex) == 0) {
                        open[successorIndex] = (*it);
                    }
                }
                it++;
            }

        }
        vector<int> path;
        return path;
    }

    int distanceToGoal(State<int> *current, State<int> *goal) {
        int xCurrent = current->getState() / numOfColumns;
        int xGoal = goal->getState() / numOfColumns;
        int yCurrent = current->getState() - xCurrent * numOfColumns;
        int yGoal = goal->getState() - xGoal * numOfColumns;
        return abs(xCurrent - xGoal) + abs(yCurrent - yGoal);

    }
};

#endif

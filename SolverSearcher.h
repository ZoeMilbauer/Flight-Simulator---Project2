#ifndef PROJECT2_SOLVERSEARCHER_H
#define PROJECT2_SOLVERSEARCHER_H

#include "Solver.h"
#include "Searcher.h"
#include "Searchable.h"
template <typename T> class SolverSearcher : public Solver<vector<T>, Searchable<T>*> {
    Searcher<T>* searcher;
public:
    SolverSearcher(Searcher<T> *searcher) {
        this->searcher = searcher;
    }
    vector<T> solve(Searchable<T>* searchable) {
        return this->searcher->search(searchable);
    }
};


#endif

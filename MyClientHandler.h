#ifndef PROJECT2_MYCLIENTHANDLER_H
#define PROJECT2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <vector>
#include "Searchable.h"
#include "FileCacheManager.h"
#include "SolverSearcher.h"
#include "BFS.h"
#include "DFS.h"

class MyClientHandler : public ClientHandler {
    unordered_map<string, string> & ProblemsAndSolutions;
    Solver<vector<int>,Searchable<int>*>* s;
    CacheManager<string, string>* cm;
public:
    MyClientHandler(CacheManager<string, string>* cm, Solver<vector<int>,Searchable<int>*>* s,
            unordered_map<string, string> & ProblemsAndSolutions);
    MyClientHandler* clone() const {
        return new MyClientHandler(new FileCacheManager("a.txt", ref(this->ProblemsAndSolutions)), new SolverSearcher<int>(new DFS<int>()),
               ref(ProblemsAndSolutions));
    }
    void handleClient(char* input, char* output);
    ~MyClientHandler(){}
};

#endif

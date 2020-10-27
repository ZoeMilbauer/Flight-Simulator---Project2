#include <iostream>
#include "FileCacheManager.h"
#include <unordered_map>
#include <string>
#include "MatrixSearchable.h"
#include <fstream>
#include "Searcher.h"
#include <vector>
#include "BFS.h"
#include "DFS.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "SolverSearcher.h"
#include "MyParallelServer.h"
#include "BestFirstSearch.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include "Astar.h"
using  namespace std;

int main() {
//    vector<int> matrix;
//    for(int i=0; i<16;i++){
//        matrix.push_back(i);
//    }
//
//    int a = 15;
//    int b = 0;
//  //  Searchable<int>* se = new MatrixSearchable(matrix,4, a, b);
//    Searcher<int>* bfs = new BFS<int>();
//    vector<int> path1= bfs->search(se);
//
//    Searcher<int>* dfs = new DFS<int>();
//    vector<int> path2= dfs->search(se);

    //string input = "1,2*,3,4*,0,0*,1,1*,";


    unordered_map<string, string> ProblemsAndSolutions = {};
    CacheManager<string, string>* cm = new FileCacheManager("a.txt", ProblemsAndSolutions);
    Searcher<int>* bfs = new DFS<int>();
    Solver<vector<int>, Searchable<int>*>* solver = new SolverSearcher<int>(bfs);
    ClientHandler* m = new MyClientHandler(cm, solver, ProblemsAndSolutions);
    //string output = m.handleClient(input);


    Server* s = new MyParallelServer();



    s->open(5400, m);
   s->stop();
//   while (true) {
//
//    }

//
//

//    ofstream out("matrix.txt", ios::app);
//
//    vector<int> mat = {};
//    int val;
//    for (int i = 1; i <= 100; i++) {
//        val = rand() % 52 + 1;
//        mat.push_back(val);
//        out << val;
//        if (i%10 != 0) {
//            out <<", ";
//        }
//        else{
//            out<<endl;
//
//        }
//    }
//
//
//    Searchable<int>* se = new MatrixSearchable(mat,10,10, 0, 99);
//    Searcher<int>* bfs = new BFS<int>();
//    vector<int> path1= bfs->search(se);
//    out << "number of nodes of BFS " << bfs->getNumberOfNodesEvaluated() << endl;
//    out << "cost of BFS " << bfs->getCost() << endl;
//    Searcher<int>* dfs = new DFS<int>();
//    vector<int> path2= dfs->search(se);
//    int cost =0;
//    for (int j = 0; j < mat.size(); j++ ) {
//        cost+= mat[j];
//
//    }
//    out << "number of nodes of DFS " << dfs->getNumberOfNodesEvaluated() << endl;
//    out << "cost of DFS " << cost << endl;
//    Searcher<int>* best = new BestFirstSearch<int>();
//    vector<int> path3= best->search(se);
//    out << "number of nodes of Best " << best->getNumberOfNodesEvaluated() << endl;
//    out << "cost of Best " << best->getCost() << endl;
//    Searcher<int>* astar = new Astar(10);
//    vector<int> path4= astar->search(se);
//    out << "number of nodes of Astar " << astar->getNumberOfNodesEvaluated() << endl;
//    out << "cost of Astar " << astar->getCost() << endl;
//
//
//    out.close();

//
//    vector <int> a = {1,100,1,1,1,10,
//                      1,100,1,50,1,10,
//                      1,1,10,20,1,10,
//                      1,2,2,100,1,10,
//                      10,10,10,10,10,10};
//    Searchable<int>* se = new MatrixSearchable(a,5,6, 0, 29);
//    Searcher<int>* astar = new Astar(6);
//    vector<int> path1= astar->search(se);
//   Searcher<int>* best = new BestFirstSearch<int>();
//   vector<int> path2= best->search(se);
    return 0;
}
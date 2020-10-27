#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <mutex>


using namespace std;

class FileCacheManager : public CacheManager<string, string> {
    unordered_map<string, string> & ProblemsAndSolutions;
    string fileName;
public:
    // constructor of FileCacheManager.
    // loads map of problems and solutions from given file
    FileCacheManager(string fileName, unordered_map<string, string> & ProblemsAndSolutions)
    :ProblemsAndSolutions(ProblemsAndSolutions) {
        this->fileName = fileName;
        string problem;
        string solution;
        // open file for reading
        ifstream in(fileName);
        string line;
        // read lines
        while (getline(in, line)) {
            problem = line;
            getline(in, line);
            solution = line;
            // insert problem and solution to map
            ProblemsAndSolutions.insert(pair<string, string> (problem, solution));
        }
        // close file
        in.close();
    }
    // returns true if there is a solution for the given problem
    bool search(string problem) {
        if (ProblemsAndSolutions.find(problem) != ProblemsAndSolutions.end()) {
            return true;
        }
        return false;
     }
     // returns the solution of a given problem
    string getSol(string problem) {
        return ProblemsAndSolutions[problem];
    }
    // adds a problem and solution
    void add(string problem, string solution) {
        ProblemsAndSolutions.insert(pair<string, string > (problem, solution));
       // mtx.lock();
        ofstream out(this->fileName, ios::app);
        out << problem << endl << solution << endl;
        out.close();
        //mtx.unlock();
    }
};

#endif

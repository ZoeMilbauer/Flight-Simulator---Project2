#include "MyClientHandler.h"
#include <string>
#include <string.h>
#include <cstring>
#include "MatrixSearchable.h"
#include "BFS.h"

using namespace std;
MyClientHandler::MyClientHandler(CacheManager<string, string>* cm, Solver<vector<int>,Searchable<int>*>* s,
                                 unordered_map<string, string> & ProblemsAndSolutions)
                                 :ProblemsAndSolutions(ProblemsAndSolutions){
    this->s = s;
    this->cm = cm;
}


void MyClientHandler::handleClient(char* input, char* output) {
    string tempInput = string(input);
    // if there is a solution for the given problem, save it to output
    if (this->cm->search(tempInput)) {
        // copy solution to output
        strcpy(output,(this->cm->getSol(tempInput)).c_str());
    }
    else {
        char* temp = new char[tempInput.length()];
        //strcpy(temp, input);
        char* inputBackUp = new char[tempInput.length()];
        strcpy(inputBackUp, input);
        char* token = strtok(inputBackUp, "*");
        int n = 0;
        while (token != NULL) {
           strcat(temp, token);
            n++; // number of lines
            token = (strtok(NULL, "*"));
        }
        n-=3;
        vector<int> matrix = {};
        //strcpy(temp, (lines.c_str()));
        char* number = strtok(temp, ",");
        while (number != NULL) {
            matrix.push_back(atoi(number));
            number = (strtok(NULL, ","));
        }
        int goalC = matrix[matrix.size() - 1];
        matrix.pop_back();
        int goalR = matrix[matrix.size() - 1];
        matrix.pop_back();
        int startC = matrix[matrix.size() - 1];
        matrix.pop_back();
        int startR = matrix[matrix.size() - 1];;
        matrix.pop_back();
        int m = matrix.size() / n;

        Searchable<int>* se = new MatrixSearchable(matrix, n, m,
                (startR*m + startC), (goalR*m + goalC));
        vector<int> path= this->s->solve(se);
        int current;
        int next;
        string directions = "";
        if (path.empty()) {
            directions = "-1";
        }
        else {
            for (int i = 0; i <= path.size() - 2; i++) {
                current = path[i];
                next = path[i + 1];
                if (next == (current - m)) {
                    directions += "Up,";
                } else if (next == (current + m)) {
                    directions += "Down,";
                } else if (next == current - 1) {
                    directions += "Left,";
                } else if (next == current + 1) {
                    directions += "Right,";
                }
            }
            directions.pop_back();
        }
        strcpy(output, directions.c_str());
        this->cm->add(input, directions);
    }
}


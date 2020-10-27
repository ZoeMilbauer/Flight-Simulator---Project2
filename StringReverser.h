#ifndef PROJECT2_STRINGREVERSER_H
#define PROJECT2_STRINGREVERSER_H

#include "Solver.h"
#include <string>
using namespace std;
class StringReverser : public Solver<string, string> {
public:
    string solve(string problem);
};

#endif

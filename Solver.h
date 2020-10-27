#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H

template <typename S, typename P>
class Solver {

public:
    virtual S solve(P problem) = 0;
};

#endif


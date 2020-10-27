#ifndef PROJECT2_MYPRIORITYQUEUE_H
#define PROJECT2_MYPRIORITYQUEUE_H

#include "PriorityQueue.h"

template<class T> class MyPriorityQueue: public PriorityQueue<T> {

public:
    void AddToQueue(State<T> s){
        for (typename deque<State<T>>::iterator it = this->queue.begin(); it != this->queue.end(); it++){
            if(it->getCost()>s.getCost()){
                this->queue.insert(it, s);
                return;
            }
        }
        this->queue.push_back(s);
    }
};
#endif

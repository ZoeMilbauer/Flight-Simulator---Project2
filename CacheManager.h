#ifndef PROJECT2_CACHEMANAGER_H
#define PROJECT2_CACHEMANAGER_H

template <typename S, typename P>
class CacheManager {
    
public:
    virtual bool search(P problem) = 0;
    virtual S getSol(P problem) = 0;
    virtual void add(P problem, S solution) = 0;
};

#endif

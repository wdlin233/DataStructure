#ifndef STATE_H_
#define STATE_H_
#include "suan_png.h"
#include "pxl.h"
#include <set>
#include <vector>
#include <queue>

class State {
private:
    //TODO
public:
    State();
    State(State &other);
    State(State &&other);
    ~State();
    State &operator=(State &&other);
    State &operator =(State &other);
    void parse(PNG *p);
    int solve();

};


#endif

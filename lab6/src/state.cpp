#include "state.h"
#include <iostream>
#include <climits>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f;

struct point {
    int x, y, val;
    bool operator<(const point& a, const point& b) {
        return a.val > b.val;
    }
    bool operator>(const point& a, const point& b) {
        return a.val < b.val;
    }
    point(int x, int y, int val): x(x), y(y), val(val) {}
};

State::State() {
    //TODO
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            dis[i][j] = INF;
            vis[i][j] = false;
        }
    }
    row = 0;
    column = 0;
}

State::State(State &other) {
    //TODO
    this->row = other.row;
    this->column = other.column;
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            this->dis[i][j] = other.dis[i][j];
            this->vis[i][j] = other.vis[i][j];
            this->pic[i][j] = other.pic[i][j];
        }
    }
    return;
}

State::State(State &&other) {
    //TODO
    this->row = other.row;
    this->column = other.column;
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            this->dis[i][j] = other.dis[i][j];
            this->vis[i][j] = other.vis[i][j];
            this->pic[i][j] = other.pic[i][j];
        }
    }
    return;
}

State::~State() {
    //TODO
}

State &State::operator=(State &other) {
    //TODO
    this->row = other.row;
    this->column = other.column;
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            this->dis[i][j] = other.dis[i][j];
            this->vis[i][j] = other.vis[i][j];
            this->pic[i][j] = other.pic[i][j];
        }
    }
    return *this;
}

State &State::operator=(State &&other) {
    //TODO
    this->row = other.row;
    this->column = other.column;
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            this->dis[i][j] = other.dis[i][j];
            this->vis[i][j] = other.vis[i][j];
            this->pic[i][j] = other.pic[i][j];
        }
    }
    return *this;
}

void State::parse(PNG *p) {
    //TODO
    int height = p->get_height();
    int width = p->get_width();
    int column_tmp = 0;
    int row= 0;
    for (int h = 6; h < height; h+= 8, row++){
        column = 0;
        for(int w = 1, j = -1; w < width; w++) {
            int r,g,b;
            r = p->get_pxl(w, h)->red;
            g = p->get_pxl(w, h)->green;
            b = p->get_pxl(w, h)->blue;
            if (r == 0 && g== 0 && b==0) {
                column += 1;
                continue;
            }
            pic[row][column] = 255 * 255 * 3 - r * r - g * g - b * b;
            if (line == 0 && pic[row][column] == 0) 
                pic[row][column] = -1;
        }
        column_tmp = column > column_tmp ? column : column_tmp;
    }
    column = column_tmp;
    return;
}



int State::solve() {
    //TODO
    std::priority_queue<point> q;
    
    return 0;
}

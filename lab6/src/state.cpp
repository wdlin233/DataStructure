#include "state.h"
#include <iostream>
#include <climits>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f;

struct point {
    int x, y, val;
    friend bool operator<(const point& a, const point& b) {
        return a.val > b.val;
    }
    friend bool operator>(const point& a, const point& b) {
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
            this->picture[i][j] = other.picture[i][j];
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
            this->picture[i][j] = other.picture[i][j];
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
            this->picture[i][j] = other.picture[i][j];
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
            this->picture[i][j] = other.picture[i][j];
        }
    }
    return *this;
}

void State::parse(PNG *p) {
    //TODO
    int height = p->get_height();
    int width = p->get_width();
    int column_tmp = 0;
    row= 0; // it cant be `int row = 0`
    for (int h = 6; h < height; h+= 8, row++){
        column = 0;
        for(int w = 1; w < width; w++) {
            int r,g,b;
            r = p->get_pxl(w, h)->red;
            g = p->get_pxl(w, h)->green;
            b = p->get_pxl(w, h)->blue;


            if (r == 0 && g== 0 && b==0) {
                column += 1;
                continue;
            }
            picture[row][column] = 255 * 255 * 3 - r * r - g * g - b * b;
            if (column == 0 && picture[row][column] == 0) 
                picture[row][column] = -1;
        }


        column_tmp = column > column_tmp ? column : column_tmp;
    }
    column = column_tmp;
    return;
}



int State::solve() {
    std::priority_queue<point> qu_point;
     int pos_x1[6]{-1, 1, 0, 0, -1, 1};
    int pos_y1[6]{0, 0, -1, 1, 1, 1};
    int pos_x2[6]{-1, 1, 0, 0, -1, 1};
    int pos_y2[6]{0, 0, -1, 1, -1, -1};


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            dis[i][j] = INF;
        }
    }
    if (picture[0][0] != 0) {
        qu_point.push(point(0, 0, 0));
    } 
    else {
        qu_point.push(point(0, 1, 0));
    }

   

    while (qu_point.size())
    {
        point index = qu_point.top();
        qu_point.pop();
        if(vis[index.x][index.y] == 1) continue;
        
        vis[index.x][index.y] = 1;
        dis[index.x][index.y] = index.val;
        
        if (index.x % 2 == 0) {
            for (int i = 0; i < 6; i++) {
                int next_x = index.x + pos_x1[i];
                int next_y = index.y + pos_y1[i];
                if (next_x < 0 || next_x >= row || next_y < 0 
                    || next_y >= column || vis[next_x][next_y] == 1 
                    || picture[next_x][next_y] == -1
                    ) 
                    {
                        continue;
                    }
                qu_point.push(point(next_x, next_y, dis[index.x][index.y] + picture[next_x][next_y]));
            }
        }
        else {
            for (int i = 0; i < 6; i++) {
                int next_x = index.x + pos_x2[i];
                int next_y = index.y + pos_y2[i];
                if (next_x < 0 || next_x >= row || next_y < 0 
                    || next_y >= column || vis[next_x][next_y] == 1 
                    || picture[next_x][next_y] == -1) {
                    continue;
                }
                qu_point.push(point(next_x, next_y, dis[index.x][index.y] + picture[next_x][next_y]));
            }
        }
    }
    if (row > 0 && column > 0)  {
        return dis[row - 1][column - 1];
    }
    else {
    return 0;}
}

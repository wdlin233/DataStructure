#ifndef TREE_H_
#define TREE_H_
#include <cstdint>
#include <cmath>
#include <utility>
#include <iostream>
#include <stdio.h>
#include "pxl.h"
#include "suan_png.h"

class Node {
private:
    PNG *p; //the upper left pixel
    Node **children; //pointer to four other node
    int width; //当前像素区块的宽度
    int height; //当前像素区块的高度
    bool leaf; //是否是叶子节点，true 代表是叶子节点
    int x; //当前像素区块左上角顶点像素的横坐标
    int y; //当前像素区块左上角顶点像素的纵坐标
    int mean_r; //Rmean
    int mean_g; //Gmean
    int mean_b; //Bmean
    bool judge_twice;
public:
    Node();
    Node(PNG* corner, int input_width, int input_height, int x, int y);
    Node(Node &other);
    Node(Node &&other);
    Node& operator=(Node &other);
    Node& operator=(Node &&other);
    ~Node();
    void print();
    pxl *get_pxl();
    void reset_png(Node *node, int mean_r, int mean_g, int mean_b);
    PNG *get_png();
    int get_width();
    int get_height();
    int get_x();
    int get_y();
    int *get_mean();
    bool is_leaf();
    void set_pxl(int r, int g, int b);
    int get_color(int index);
    Node *&get_child(int i);
};


class Tree {
private:
    Node *root; //根结点
    Node *load_png_node(PNG *png, int width, int height, int x, int y); 
public:
    Tree();
    ~Tree();
    Tree(Tree &other);
    Tree& operator=(Tree &other);
    void judge(int threshold);
    pxl *get_pxl();
    void load_png(PNG *png);
    void print();
    void reset_png(Node *node, int mean_r, int mean_g, int mean_b);
};
#endif

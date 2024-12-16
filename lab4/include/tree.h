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
    Node **children; //pointer to four other node
    int width; //当前像素区块的宽度
    int height; //当前像素区块的高度
    bool leaf; //是否是叶子节点，true 代表是叶子节点
    int x; //当前像素区块左上角顶点像素的横坐标
    int y; //当前像素区块左上角顶点像素的纵坐标
    int mean_r; //Rmean
    int mean_g; //Gmean
    int mean_b; //Bmean
    int mean_alpha;
    
public:
    int mean_alpha;
    
public:
    int r_r;
    int r_g;
    int r_b;
    int judged_times;
    Node*& get_child(int index);
    int get_width();
    int get_heigth();
    int get_x();
    int get_y();
    bool is_leaf();
    int& get_rgb(int index);
    void set_rgb(int r,int g,int b);
    Node();
    Node(PNG* corner, int input_width, int input_height, int x, int y);
    Node(const Node &other);
    Node(Node &&other);
    Node& operator=(const Node &other);
    Node& operator=(Node &&other);
    ~Node();
    void print();
    pxl *get_pxl();
    
};


class Tree {
private:
    Node *root; //根结点
public:
    Tree();
    ~Tree();
    Tree(Tree &other);
    Tree& operator=(Tree &other);
    void judge(int threshold);
    void load_png(PNG *png);
    void set_node_average_color(Node *node);
    void build_tree(Node *node, PNG *png);
    void print();
    void pre_judge(Node *node, int threshold);
    int max_judged_times(Node *node);
    int set_mean(Node *node, int r, int g, int b);
    int restore(Node *node);
};
#endif
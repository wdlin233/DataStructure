#include "tree.h"

Node::Node() {
    p = nullptr; 
    children = new Node*[4];
    for (int i = 0; i < 4; i++) {
        children[i] = nullptr;
    } 
    width = 0; 
    height = 0; 
    leaf = false; 
    x = 0; 
    y = 0; 
    mean_r = 0; 
    mean_g = 0; 
    mean_b = 0; 
}

Node::Node(PNG* corner, int input_width, int input_height, int x, int y) {
    corner = p;
    children = new Node*[4];
    for (int i = 0; i < 4; i++) {
        children[i] = nullptr;
    }
    width = input_width;
    height = input_height;
    if (input_width == 1 && input_height == 1) {
        leaf = true;
    } else {
        leaf = false;
    }
    x = x;
    y = y;
    mean_r = 0;
    mean_g = 0;
    mean_b = 0; 
}

Node::Node(Node &other) {
    //TODO
}

Node::Node(Node &&other) {
    //TODO
}

Node& Node::operator=(Node &other) {
    //TODO
}

Node& Node::operator=(Node &&other) {
    //TODO
}

void Tree::judge(int threshold) {
    //TODO
    return;
}

void Tree::load_png(PNG *png) {
    png->get_pxl
}

/*
 ================================================
 ====DO NOT MODIFY ANY OF THE FUNCTIONS BELOW====
 ==============请不要修改以下任何函数================
 ================================================
 */

Node::~Node() {
    for (int i = 0; i < 4; i++) {
        if (children[i]!=NULL) {
            delete children[i];
        }
    }
    delete[] children;
}

void Node::print() {
    if (children[0] != NULL) {
        children[0]->print();
    }
    if (children[1] != NULL) {
        children[1]->print();
    }
    if (children[2] != NULL) {
        children[2]->print();
    }
    if (children[3] != NULL) {
        children[3]->print();
    }
    printf("Red: %u, Green: %u, Blue: %u, Width: %d, Height: %d\n", mean_r, mean_g, mean_b, width, height);
    //printf("Red: %u, Green: %u, Blue: %u, Width: %d, Height: %d,", p->red, p->green, p->blue, width, height);
    std::cout << "Leaf: " << leaf << std::endl;
    return;
}

pxl* Node::get_pxl() {
    return p->get_pxl(x,y);
}

Tree::Tree() {
    root = new Node();
}

Tree::~Tree() {
    delete root;
}

Tree::Tree(Tree &other) {
    if (other.root != NULL) {
        root = new Node(*other.root);
    }
}

Tree& Tree::operator=(Tree &other) {
    if (other.root != NULL && &other != this) {
        root = new Node(*(other.root));
    }
    return *this;
}

pxl *Tree::get_pxl() {
    return root->get_pxl();
}

void Tree::print() {
    root->print();
}

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
    judge_twice = false; 
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
    judge_twice = false; 
}

Node::Node(Node &other) {
    // copy constructor implementation
    this->p = other.p ? new SomeType(*other.p) : nullptr; // Deep copy if p is not null
    if (other.children) {
        this->children = new SomeType(*other.children); // Deep copy if children is not null
    } else {
        this->children = nullptr;
    }
    this->width = other.width;
    this->height = other.height;
    this->leaf = other.leaf;
    this->x = other.x;
    this->y = other.y;
    this->mean_r = other.mean_r;
    this->mean_g = other.mean_g;
    this->mean_b = other.mean_b;
    this->judge_twice = other.judge_twice;
}

Node::Node(Node &&other) {
    // Move constructor implementation
    this->p = other.p;
    this->children = other.children;
    this->width = other.width;
    this->height = other.height;
    this->leaf = other.leaf;
    this->x = other.x;
    this->y = other.y;
    this->mean_r = other.mean_r;
    this->mean_g = other.mean_g;
    this->mean_b = other.mean_b;
    this->judge_twice = other.judge_twice;
    other.p = nullptr;
    other.children = nullptr;
}

Node& Node::operator=(Node &other) {
    // copy assignment implementation
    if (this != &other) {
        delete this->p;
        delete this->children;
        this->p = other.p ? new SomeType(*other.p) : nullptr; // Deep copy if p is not null
        if (other.children) {
            this->children = new SomeType(*other.children); // Deep copy if children is not null
        } else {
            this->children = nullptr;
        }
        this->width = other.width;
        this->height = other.height;
        this->leaf = other.leaf;
        this->x = other.x;
        this->y = other.y;
        this->mean_r = other.mean_r;
        this->mean_g = other.mean_g;
        this->mean_b = other.mean_b;
        this->judge_twice = other.judge_twice;
    }
    return *this;
}

Node& Node::operator=(Node &&other) {
    // Move assignment implementation
    if (this != &other) {
        delete this->p;
        delete this->children;
        this->p = other.p;
        this->children = other.children;
        this->width = other.width;
        this->height = other.height;
        this->leaf = other.leaf;
        this->x = other.x;
        this->y = other.y;
        this->mean_r = other.mean_r;
        this->mean_g = other.mean_g;
        this->mean_b = other.mean_b;
        this->judge_twice = other.judge_twice;
        other.p = nullptr;
        other.children = nullptr;
    }
    return *this;
}

void Node::reset_png(Node *node, int mean_r, int mean_g, int mean_b) {
    if (node->leaf) {
        pxl *pxls = node->p->get_pxl();
        pxls->red = mean_r;
        pxls->green = mean_g;
        pxls->blue = mean_b;
        return;
    }
    if (judge_twice == false) {
        judge_twice = true;
        for (int i = 0; i < 4; i++) {
            reset_png(node->children[i], mean_r, mean_g, mean_b);
        }
    }
    return;
}

void Tree::judge(int threshold) {
    pxl *pxls = this->root->p->get_pxl();
    int size = this->root->width * this->root->height;
    int sum_r = 0, sum_g = 0, sum_b = 0;
    for (int i = 0; i < size; i++) {
        sum_r += pxls[i].red;
        sum_g += pxls[i].green;
        sum_b += pxls[i].blue;
    }
    this->root->mean_r = sum_r / size;
    this->root->mean_g = sum_g / size;
    this->root->mean_b = sum_b / size;
    int r_bias = 0, g_bias = 0, b_bias = 0;
    for (int i = 0; i < size; i++) {
        r_bias += (pxls[i].red - this->root->mean_r) * (pxls[i].red - this->root->mean_r);
        g_bias += (pxls[i].green - this->root->mean_g) * (pxls[i].green - this->root->mean_g);
        b_bias += (pxls[i].blue - this->root->mean_b) * (pxls[i].blue - this->root->mean_b);
    }
    int var = (r_bias + g_bias + b_bias) / (size * 30);
    if (var < threshold) {
        reset_png(this->root, this->root->mean_r, this->root->mean_g, this->root->mean_b);
    }
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

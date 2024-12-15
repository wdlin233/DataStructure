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
    p = corner;
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
    root = load_png_node(png, png->get_width(), png->get_height(), 0, 0);
    //int size = png->get_width() * png->get_height();
    int tile_width = png->get_width() / 4;
    int tile_height = png->get_height() / 4; 
    pxl *image = new pxl[png->get_width() * png->get_height()];
    for (int i = 0; i < png->get_width(); i++) {
        for (int j = 0; j < png->get_height(); j++) {
            image[png->get_width() * j + i] = *(png->get_pxl(i, j));
        }
    }
    for (int j = 0; j < 4; j++) {
        root->children[j] = load_png_node(png, png->get_width() / 2, png->get_height() / 2, tile_width * j, tile_height * j);
    }

}

Node *Tree::load_png_node(PNG *png, int width, int height, int x, int y) {
    if (width == 1 && height == 1) {
        return new Node(png, 1, 1, x, y);
    } else {
        return new Node(png, width, height, x, y);
    }
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

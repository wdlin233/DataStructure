#include "tree.h"
#include <queue>

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
    judge_twice = false; 
}

Node::Node(Node &other) {
    // copy constructor implementation
    // this->p = other.p ? new SomeType(*other.p) : nullptr; // Deep copy if p is not null
    // if (other.children) {
    //     this->children = new SomeType(*other.children); // Deep copy if children is not null
    // } else {
    //     this->children = nullptr;
    // }
    this->p = new PNG();
    *(this->p)=*(other.p);
    this->children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(this->children+i)=other.children[i];
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
        // this->p = other.p ? new SomeType(*other.p) : nullptr; // Deep copy if p is not null
        // if (other.children) {
        //     this->children = new SomeType(*other.children); // Deep copy if children is not null
        // } else {
        //     this->children = nullptr;
        // }
        this->p = new PNG();
        *(this->p)=*(other.p);
        this->children = new Node*[4];
        for(int i=0;i<4;i++)
        {
            *(this->children+i)=other.children[i];
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
        pxl *pxls = node->p->get_image();
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

Node *&Node::get_child(int i) {
    return children[i];
}

void Node::set_pxl(int r, int g, int b) {
    mean_r = r;
    mean_g = g;
    mean_b = b;
}

void Tree::judge(int threshold) {
    pxl *pxls = this->root->get_png()->get_image();
    int size = this->root->get_width() * this->root->get_height();
    int sum_r = 0, sum_g = 0, sum_b = 0;
    for (int i = 0; i < size; i++) {
        sum_r += pxls[i].red;
        sum_g += pxls[i].green;
        sum_b += pxls[i].blue;
    }
    this->root->get_mean()[0] = sum_r / size;
    this->root->get_mean()[1] = sum_g / size;
    this->root->get_mean()[2] = sum_b / size;
    int r_bias = 0, g_bias = 0, b_bias = 0;
    for (int i = 0; i < size; i++) {
        r_bias += (pxls[i].red - this->root->get_mean()[0]) * (pxls[i].red - this->root->get_mean()[0]);
        g_bias += (pxls[i].green - this->root->get_mean()[1]) * (pxls[i].green - this->root->get_mean()[1]);
        b_bias += (pxls[i].blue - this->root->get_mean()[2]) * (pxls[i].blue - this->root->get_mean()[2]);
    }
    int var = (r_bias + g_bias + b_bias) / (size * 30);
    if (var < threshold) {
        reset_png(this->root, this->root->get_mean()[0], this->root->get_mean()[1], this->root->get_mean()[2]);
    }
    return;
}

void create_children(Node* node, PNG* png) {
    int width[4], height[4], x[4], y[4];
    width[0] = width[2] = node->get_width() / 2;
    width[1] = width[3] = node->get_width() - width[0];
    height[0] = height[1] = node->get_height() / 2;
    height[2] = height[3] = node->get_height() - height[0];
    x[0] = x[2] = node->get_x();
    x[1] = x[3] = node->get_x() + width[0];
    y[0] = y[1] = node->get_y();
    y[2] = y[3] = node->get_y() + height[0];

    for (int i = 0; i < 4; i++) {
        if (width[i] == 0 || height[i] == 0) continue;
        node->get_child(i) = new Node(png, width[i], height[i], x[i], y[i]);
        if (width[i] > 1 && height[i] > 1) {
            create_children(node->get_child(i), png);
        }
    }
}

int Node::get_color(int index) {
    if (index == 0)
        return mean_r;
    else if (index == 1)
        return mean_g;
    else
        return mean_b;

}

void load_png_pxl(Node *node) {
    if (node->is_leaf()) return;
    int vaild=0,sum_r=0,sum_g=0,sum_b=0;
    for(int i=0;i<4;i++)
    {
        if(node->get_child(i)!=NULL)
        {
            vaild++;
            load_png_pxl(node->get_child(i));
            sum_r+=node->get_child(i)->get_color(0);
            sum_g+=node->get_child(i)->get_color(1);
            sum_b+=node->get_child(i)->get_color(2);
        }
    }
    node->set_pxl(sum_r/vaild,sum_g/vaild,sum_b/vaild);
}

void Tree::load_png(PNG *png) {
    Node *tmp = new Node(png, png->get_width(), png->get_height(), 0, 0);
    root = tmp;
    std::queue<Node*> q;
    q.push(root);
    //create_children(root, png);
    while (!q.empty()) {
        Node *node = q.front();
        q.pop();
        int width[4], height[4], x[4], y[4];
        width[0] = width[2] = node->get_width() / 2;
        width[1] = width[3] = node->get_width() - width[0];
        height[0] = height[1] = node->get_height() / 2;
        height[2] = height[3] = node->get_height() - height[0];
        x[0] = x[2] = node->get_x();
        x[1] = x[3] = node->get_x() + width[0];
        y[0] = y[1] = node->get_y();
        y[2] = y[3] = node->get_y() + height[0];

        for (int i = 0; i < 4; i++) {
            if (width[i]==1 && height[i] == 1)
                node->get_child(i) = new Node(png, width[i], height[i], x[i], y[i]);
            else if(width[i] == 0 || height[i] == 0)
                continue;
            else {
                node->get_child(i) = new Node(png, width[i], height[i], x[i], y[i]);
                q.push(node->get_child(i));
            }
        }
    }
}



Node *Tree::load_png_node(PNG *png, int width, int height, int x, int y) {
    if (width == 1 && height == 1) {
        return new Node(png, 1, 1, x, y);
    } else {
        return new Node(png, width, height, x, y);
    }
}

void Tree::reset_png(Node *node, int mean_r, int mean_g, int mean_b) {
    node->reset_png(node, mean_r, mean_g, mean_b);
    return;
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

PNG *Node::get_png() {
    return p;
}

int Node::get_width() {
    return width;
}

int Node::get_height() {
    return height;
}

int *Node::get_mean() {
    int *mean = new int[3];
    mean[0] = mean_r;
    mean[1] = mean_g;
    mean[2] = mean_b;
    return mean;
}

int Node::get_x() {
    return x;
}

int Node::get_y() {
    return y;
}

bool Node::is_leaf() {
    return leaf;
}
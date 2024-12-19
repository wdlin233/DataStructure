#include "tree.h"
#include <queue>
using namespace std;
//默认构造函数
Node::Node() {
    //初始化孩子节点
    children = new Node * [4];
    for (int i = 0;i < 4;i++) {
        children[i] = NULL;
    }
    p = NULL;//the upper left pixel
    width = 0;//当前像素区块的宽度
    height = 0;//当前像素区块的高度
    leaf = false;//是否是叶子节点，true 代表是叶子节点
    x = 0;//当前像素区块左上角顶点像素的横坐标
    y = 0;//当前像素区块左上角顶点像素的纵坐标
    mean_r = 0;//Rmean
    mean_g = 0; //Gmean
    mean_b = 0;//Bmean
    before_r = 0;
    before_g = 0;
    before_b = 0;
    cuttimes = 0;
}
//带参数的构造函数
Node::Node(PNG* corner, int input_width, int input_height, int x, int y) {
    children = new Node * [4];
    for (int i = 0;i < 4;i++) {
        children[i] = NULL;
    }
    p = corner;
    width = input_width;
    height = input_height;
    this->x = x;
    this->y = y;
    leaf = (input_width == 1 && input_height == 1);//构建时默认是子节点
    mean_r = get_pxl()->red;
    mean_g = get_pxl()->green;
    mean_b = get_pxl()->blue;
    this->before_r = this->mean_r;
    this->before_g = this->mean_g;
    this->before_b = this->mean_b;
    cuttimes = 0;
}
// 拷贝构造函数
Node::Node(Node& other) { 
    children = new Node * [4];
    for (int i = 0;i < 4;i++) {
        children[i] = other.children[i];
    }
    *p = *other.p;
    width = other.width;
    height = other.height;
    x = other.x;
    y = other.y;
    leaf = other.leaf;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    cuttimes = other.cuttimes;
}
// 右值拷贝构造函数，最后保留一份
Node::Node(Node&& other) { 
    p = other.p;
    children = other.children;
    width = other.width;
    height = other.height;
    x = other.x;
    y = other.y;
    leaf = other.leaf;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    cuttimes = other.cuttimes;
    other.p = NULL;
    other.children = NULL;
}
//重载node 的赋值操作符
Node& Node::operator=(Node& other) {
    for (int i = 0;i < 4;i++) {
        children[i] = other.children[i];
    }
    if (this == &other) return *this;
        p = other.p;
    width = other.width;
    height = other.height;
    x = other.x;
    y = other.y;
    leaf = other.leaf;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    cuttimes = other.cuttimes;
    return *this;
}
//重载右值等号赋值操作符
Node& Node::operator=(Node&& other) {
    if (this == &other) return *this;
    if (this->children != NULL) delete children;
    if (this->p != NULL) delete p;
    p = other.p;
    children = other.children;
    width = other.width;
    height = other.height;
    x = other.x;
    y = other.y;
    leaf = other.leaf;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
    cuttimes = other.cuttimes;
    other.p = NULL;
    other.children = NULL;
    return *this;
}
//进行判断和剪枝
void Tree::judge(int threshold) {
    if (root != NULL) {
        child_judge(root, threshold);
        remake(root);
        mean_RGB(root);
    }
    return;
}

//计算RGB的均值函数
void Tree::mean_RGB(Node* op) {
    if (op->leaf) return;
    int r, g, b, sum;
    r = g = b = sum = 0;
    for (int i = 0;i < 4;i++) {
        if (op->children[i] != NULL) {
            mean_RGB(op->children[i]);
            r += op->children[i]->mean_r;
            g += op->children[i]->mean_g;
            b += op->children[i]->mean_b;
            sum++;
        }
    }
    op->mean_r = r / sum;
    op->mean_g = g / sum;
    op->mean_b = b / sum;
}

int Tree::remake(Node* op)
{
    if (op == NULL)
        return -1;
    if (op->leaf == true)
    {
        op->mean_r = op->before_r;
        op->mean_g = op->before_g;
        op->mean_b = op->before_b;
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        if (op->children[i] != NULL)
        {
            remake(op->children[i]);
        }
    }
    return 1;
}

void Tree::child_judge(Node* op, int threshold) {
    int sum = 0, var = 0;
    if (op->leaf) return;
    for (int i = 0;i < 4;i++) {
        if (op->children[i] != NULL)
        {
            child_judge(op->children[i], threshold);
            sum++;
        }
    }
    op->cuttimes = getmaxtimes(op);
    if (op->cuttimes > 2) return; // 剪枝次数大于2，放弃剪枝
    // 剪枝
    op->mean_r = op->mean_g = op->mean_b = 0;
    for (int i = 0;i < 4;i++) {
        if (op->children[i] != NULL) {
            op->mean_r += op->children[i]->mean_r;
            op->mean_g += op->children[i]->mean_g;
            op->mean_b += op->children[i]->mean_b;
        }
    }
    op->mean_r /= sum;
    op->mean_g /= sum;
    op->mean_b /= sum;
    for (int i = 0;i < 4;i++) {
        if (op->children[i] != NULL) {
            var += pow((op->children[i]->mean_r - op->mean_r), 2) + pow((op->children[i]->mean_g - op->mean_g), 2) + pow((op->children[i]->mean_b - op->mean_b), 2);
        }
    }
    var /= (30 * sum);
    if (threshold > var) {
        pruning(op, op->mean_r, op->mean_g, op->mean_b);
    }
}

int Tree::getmaxtimes(Node* op) {
    int ans;
    if (op->leaf) {
        return op->cuttimes;
    }
    ans = 0;
    for (int i = 0;i < 4;i++) {
        if (op->children[i] != NULL) {
            ans = max(ans, getmaxtimes(op->children[i]));
        }
    }
    return ans;
}

void Tree::pruning(Node* op, int r, int g, int b) {
    if (op != NULL) {
        op->mean_r = r;
        op->mean_g = g;
        op->mean_b = b;
        if (op->leaf) {
            op->cuttimes++;
            op->get_pxl()->red = r;
            op->get_pxl()->green = g;
            op->get_pxl()->blue = b;
        }
        else {
            for (int i = 0;i < 4;i++) {
                if (op->children[i] != NULL) {
                    pruning(op->children[i], r, g, b);
                    op->cuttimes = op->cuttimes > op->children[i]->cuttimes ? op->cuttimes : op->children[i]->cuttimes;
                }
            }
        }
    }
    return;
}
//读取PNG对象并创建数，每个节点对应图片上一个像素块
void Tree::load_png(PNG* png) {
    queue <Node*> op; 
    root->p = png;
    root->height = png->get_height();
    root->width = png->get_width();
    root->leaf = false;
    root->x = 0;
    root->y = 0;
    if (root->width == 1 && root->height == 1) root->leaf = true;
    op.push(root);
    while (!op.empty()) {
        Node* tmp = op.front();
        op.pop();
        // 子图大小、位置
        int wid[4], hei[4], x[4], y[4]; 
        wid[0] = wid[2] = tmp->width / 2;
        wid[1] = wid[3] = tmp->width - tmp->width / 2; 
        hei[0] = hei[1] = tmp->height / 2;
        hei[2] = hei[3] = tmp->height - tmp->height / 2;
        x[0] = x[2] = tmp->x;
        x[1] = x[3] = tmp->x + wid[0];
        y[0] = y[1] = tmp->y;
        y[2] = y[3] = tmp->y + hei[0];
        for (int i = 0;i < 4;i++) {
            if (wid[i] == 1 && hei[i] == 1)
                tmp->children[i] = new Node(png, wid[i], hei[i], x[i], y[i]);
            else if (wid[i] == 0 || hei[i] == 0)
                continue;
            else
            {
                tmp->children[i] = new Node(png, wid[i], hei[i], x[i], y[i]);
                op.push(tmp->children[i]);
            }
        }
    }
    mean_RGB(root);
}

/*
 ================================================
 ====DO NOT MODIFY ANY OF THE FUNCTIONS BELOW====
 ==============请不要修改以下任何函数================
 ================================================
 */

Node::~Node() {
    for (int i = 0; i < 4; i++) {
        if (children[i] != NULL) {
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
    return p->get_pxl(x, y);
}

Tree::Tree() {
    root = new Node();
}

Tree::~Tree() {
    delete root;
}

Tree::Tree(Tree& other) {
    if (other.root != NULL) {
        root = new Node(*other.root);
    }
}

Tree& Tree::operator=(Tree& other) {
    if (other.root != NULL && &other != this) {
        root = new Node(*(other.root));
    }
    return *this;
}

pxl* Tree::get_pxl() {
    return root->get_pxl();
}

void Tree::print() {
    root->print();
}

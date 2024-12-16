#include "tree.h"
#include <queue>

Node::Node() {
    p=NULL;
    children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(children+i)=NULL;
    }
    width=0;
    height=0;
    leaf=false;
    x=0;
    y=0;
    mean_b=0;
    mean_g=0;
    mean_r=0;
    judged_times=0;

}

Node::Node(PNG* corner, int input_width, int input_height, int x, int y) {
    p=corner;
    children = new Node*[4];
    for(int i=0;i<4;i++)
    {
        *(children+i)=NULL;
    }   
    width=input_width;
    height=input_height;
    if(input_width==1 && input_height==1)
        leaf=true;
    else
        leaf=false;
    this->x=x;
    this->y=y;
    mean_r=get_pxl()->red;
    mean_g=get_pxl()->green;
    mean_b=get_pxl()->blue;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    judged_times=0;

}

Node::Node(const Node &other) {
    p = new PNG(*other.p); // Deep copy of PNG object
    children = new Node*[4];
    for (int i = 0; i < 4; ++i) {
        children[i] = other.children[i] ? new Node(*other.children[i]) : nullptr; // Deep copy of children
    }
    width = other.width;
    height = other.height;
    leaf = other.leaf;
    x = other.x;
    y = other.y;
    mean_r = other.mean_r;
    mean_g = other.mean_g;
    mean_b = other.mean_b;
}

Node::Node(Node &&other) {
    p=other.p;
    children=other.children;
    width=other.width;
    height=other.height;
    leaf=other.leaf;
    this->x=other.x;
    this->y=other.y;
    mean_r=other.mean_r;
    mean_g=other.mean_g;
    mean_b=other.mean_b;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    judged_times=other.judged_times;
    other.p=nullptr;
    other.children=nullptr;
}

Node& Node::operator=(const Node &other) {
    if (this != &other) {
        delete p;
        for (int i = 0; i < 4; ++i) {
            delete children[i];
        }
        delete[] children;

        p = new PNG(*other.p); // Deep copy of PNG object
        children = new Node*[4];
        for (int i = 0; i < 4; ++i) {
            children[i] = other.children[i] ? new Node(*other.children[i]) : nullptr; // Deep copy of children
        }
        width = other.width;
        height = other.height;
        leaf = other.leaf;
        x = other.x;
        y = other.y;
        mean_r = other.mean_r;
        mean_g = other.mean_g;
        mean_b = other.mean_b;
    }
    return *this;
}

Node& Node::operator=(Node &&other) {
    if(this==&other)return *this;
    if(p!=NULL) delete p;
    if(children!=NULL) delete[] p;
    p=other.p;
    children=other.children;
    width=other.width;
    height=other.height;
    leaf=other.leaf;
    this->x=other.x;
    this->y=other.y;
    mean_r=other.mean_r;
    mean_g=other.mean_g;
    mean_b=other.mean_b;
    r_r=mean_r;
    r_g=mean_g;
    r_b=mean_b;
    judged_times=other.judged_times;
    other.p=nullptr;
    other.children=nullptr;
    return *this;

}
int Node::get_heigth(){
    return height;
}
int Node::get_width(){
    return width;
}
int Node::get_x(){
    return x;
}
int Node::get_y(){
    return y;
}
bool Node::is_leaf(){
    return leaf;
}
void Node::set_rgb(int r,int g,int b){
    mean_r=r;
    mean_g=g;
    mean_b=b;
    return;
}

void Tree::judge(int threshold) {
    if(this->root==NULL)return;
    pre_judge(root,threshold);
    restore(root);
    set_node_average_color(root);

    return;
}
void Tree::pre_judge(Node *node, int threshold){
    int vaild=0;
    if(node->is_leaf()) return;
    for(int i=0;i<4;i++){
        if(node->get_child(i)!=NULL){
            pre_judge(node->get_child(i),threshold);
            vaild++;
        }
    }
    node->judged_times=max_judged_times(node);
    if(node->judged_times>2)return;

    // calculate mean value
    int sum_r=0,sum_g=0,sum_b=0;
    for(int i=0;i<4;i++){
        if(node->get_child(i)!=NULL)
        {
            sum_r+=node->get_child(i)->get_rgb(0);
            sum_g+=node->get_child(i)->get_rgb(1);
            sum_b+=node->get_child(i)->get_rgb(2);
        }
    }
    //
    int mean_r=0,mean_g=0,mean_b=0;
    node->get_rgb(0)=mean_r=sum_r/vaild;
    node->get_rgb(1)=mean_g=sum_g/vaild;
    node->get_rgb(2)=mean_b=sum_b/vaild;
    // D(X)
    int var_sum=0,var;
    for(int i=0;i<4;i++){
        if(node->get_child(i)!=NULL){
            Node *child=node->get_child(i);
            var_sum+=(child->get_rgb(0)-mean_r)*(child->get_rgb(0)-mean_r)+(child->get_rgb(1)-mean_g)*(child->get_rgb(1)-mean_g)+(child->get_rgb(2)-mean_b)*(child->get_rgb(2)-mean_b);
        }
    }
    var=var_sum/(30*vaild);
    // threshold
    if(var<threshold){
        set_mean(node,mean_r,mean_g,mean_b);
    }
        
}
int Tree::set_mean(Node *node, int r, int g, int b){
    if(node==NULL) return -1;
    node->set_rgb(r,g,b);
    if(node->is_leaf()){
        node->judged_times++;
        node->get_pxl()->red = node->get_rgb(0);
        node->get_pxl()->green = node->get_rgb(1);
        node->get_pxl()->blue = node->get_rgb(2);
        return 0;
    }
    for(int i=0;i<4;i++){
        if(node->get_child(i)!=NULL){
            set_mean(node->get_child(i),r,g,b);
            node->judged_times=(node->judged_times)>(node->get_child(i)->judged_times)?(node->judged_times):(node->get_child(i)->judged_times);

        }
    }
    return 1;
}

int Tree::restore(Node *node){
    if(node==NULL)return -1;
    if(node->is_leaf()){
        node->get_rgb(0)=node->r_r;
        node->get_rgb(1)=node->r_g;
        node->get_rgb(2)=node->r_b;
        return 0;
    }
    for(int i=0;i<4;i++){
        if(node->get_child(i)!=NULL){
            restore(node->get_child(i));
        }
    }
    return 1;
}


int Tree::max_judged_times(Node *node){
    if(node->is_leaf())return node->judged_times;
    int ans=0;
    for(int i=0;i<4;i++){
        if(node->get_child(i)!=NULL){
            ans=ans>max_judged_times(node->get_child(i))?ans:max_judged_times(node->get_child(i));
        }
    }
    return ans;
}

void Tree::build_tree(Node *node, PNG *png) {
    // build CBT
    std::queue<Node*> q;
    q.push(node);
    while(!q.empty())
    {
        Node *current_node=q.front();
        q.pop();
        int width[4],height[4],x[4],y[4];
        width[0]=width[2]=current_node->get_width()/2;
        width[1]=width[3]=current_node->get_width()-width[0];
        height[0]=height[1]=current_node->get_heigth()/2;
        height[2]=height[3]=current_node->get_heigth()-height[0];
        x[0]=x[2]=current_node->get_x();
        x[1]=x[3]=current_node->get_x()+width[0];
        y[0]=y[1]=current_node->get_y();
        y[2]=y[3]=current_node->get_y()+height[0];

        for(int i=0;i<4;i++)
        {
            if (width[i] == 0 || height[i] == 0)
                continue;
            else
                current_node->get_child(i)=new Node(png,width[i],height[i],x[i],y[i]);

            if (width[i] > 1 || height[i] > 1)
                q.push(current_node->get_child(i));
        }
    }
}

void Tree::load_png(PNG *png) {
    Node *tmp=new Node(png,png->get_width(),png->get_height(),0,0);
    root=tmp;
    build_tree(root, png);
    set_node_average_color(root);
}

void Tree::set_node_average_color(Node *node){
    if(node->is_leaf())return;
    int vaild=0,sum_r=0,sum_g=0,sum_b=0;
    for(int i=0;i<4;i++)
    {
        if(node->get_child(i)!=NULL)
        {
            vaild++;
            set_node_average_color(node->get_child(i));
            sum_r+=node->get_child(i)->get_rgb(0);
            sum_g+=node->get_child(i)->get_rgb(1);
            sum_b+=node->get_child(i)->get_rgb(2);
        }
    }
    node->set_rgb(sum_r/vaild,sum_g/vaild,sum_b/vaild);
}

int& Node::get_rgb(int index) {
    if (index == 0)
        return mean_r;
    else if (index == 1)
        return mean_g;
    else if (index == 2)
        return mean_b;
    else
        return mean_alpha;
}

Node*& Node::get_child(int index) {
    return children[index];
}
/*
 ================================================
 ====DO NOT MODIFY ANY OF THE FUNCTIONS BELOW====
 ==============请不要修改以下任何函数================
 ================================================
 */

Node::~Node() {
    delete p; // Delete the PNG object
    for (int i = 0; i < 4; ++i) {
        delete children[i]; // Delete each child node
    }
    delete[] children; // Delete the array of child pointers
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

void Tree::print() {
    root->print();
}
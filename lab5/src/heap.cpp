#include "heap.h"
#define LEFT true
#define RIGHT false

#define LIST_SIZE 2000

void swap(Player_info &a, Player_info &b) {
    Player_info temp = a;
    a = b;
    b = temp;
}

// #define swap(x, y) \
//     do { \
//         Player_info tmp = x; \
//         x = y; \
//         y = tmp; \
//     }while(0) \

Heap::~Heap() {
    //TODO
    delete[] arr;
    num = 0;
}

Heap::Heap(Heap &other) {
    //TODO
    arr = new Player_info[LIST_SIZE];
    for (int i = 0; i < LIST_SIZE; i++) {
        arr[i] = other.arr[i];
    }
    num = other.num;
}

Heap &Heap::operator=(Heap &other) {
    //TODO
    arr = new Player_info[LIST_SIZE];
    for (int i = 0; i < LIST_SIZE; i++) {
        arr[i] = other.arr[i];
    }
    num = other.num;
    return *this;
}

void Heap::heapify_up() {
    int index = num - 1;
    while (index > 0) {
        int parent = get_father(index);
        if (arr[index] < arr[parent]) {
            swap(arr[index], arr[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void Heap::heapify_down() {
    int index = 0;
    while (true) {
        int left_child = get_child(LEFT, index);
        int right_child = get_child(RIGHT, index);
        int smallest = index;

        if (left_child != -1 && arr[left_child] < arr[smallest]) {
            smallest = left_child;
        }
        if (right_child != -1 && arr[right_child] < arr[smallest]) {
            smallest = right_child;
        }
        
        if (smallest != index) {
            swap(arr[index], arr[smallest]);
            index = smallest;
        } else {
            break;
        }
        // if ((left_child >= 0 && left_child <num) && (right_child >= 0 && right_child < num)) {
        //     smallest = (arr[left_child] < arr[right_child]) ? left_child : right_child;
        // }
        // else if (left_child >= 0 && left_child < num) {
        //     smallest = left_child;
        // }
        // else {
        //     smallest = right_child;
        // }

        // if (smallest >= 0 && smallest < num) {
        //     if (arr[index] > arr[smallest]) {
        //         swap(arr[index], arr[smallest]);
        //         index = smallest;
        //         continue;
        //     }
        // }
        // return;
    }
}

int Heap::get_child(bool direction, int index) {
    //TODO
    int child = direction == LEFT ? 2 * index + 1 : 2 * index + 2;
    if (child < num) {
        return child;
    } else {
        return -1;
    }
}

int Heap::get_father(int index) {
    //TODO
    int father = (index - 1) / 2;
    if (father < 0 || father >= num) {
        return -1;
    }
    else {
        return father;
    }
}

int Heap::insert(Player_info &p) {
    if (num < 2000) {
        arr[num] = p;
        heapify_up();
        num += 1;
        return 1;
    }
    else {
        if (p > arr[0]) {
            arr[0] = p;
            heapify_down();
            return 1;
        }
    }
    return 0;
}

Player_info *Heap::sort() {
    //TODO
    int n = num;
    Player_info *vec = new Player_info[2000];
    for (int i = 0; i < num; i++) {
        num--;
        if (num <= 0)
            break;
        swap(arr[0], arr[num]);
        heapify_down();
    }
    num = n;
    for (int i = 0; i < 2000; i++) {
        vec[i] = arr[i];
    }
    return vec;
}

/*
 =========================================================
 ================ WARNING ===== 警告 ======================
 ===Please Do Not Modify Any of the Following Functions===
 ===================请不要修改以下函数=======================
 =========================================================
 */

int Heap::get_num() const {
    return num;
}

Heap::Heap() {
    num = 0;
    arr = new Player_info[LIST_SIZE];
}

void Heap::print() {
    for (int i = 0; i < num; i++) {
        arr[i].print();
    }
    printf("\nSize of the heap is %d\n", num);
}

Player_info::Player_info() {
    username = std::string("#");
    uid = 0;
    score = 0;
}

Player_info::~Player_info() {

}

Player_info::Player_info(Player_info &other) {
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
}

Player_info::Player_info(std::string in_name, long in_uid, int in_score) {
    username = std::string(in_name);
    score = in_score;
    uid = in_uid;
}

Player_info &Player_info::operator=(Player_info &other) {
    username = std::string((other.username));
    score = other.score;
    uid = other.uid;
    return *this;
}

int Player_info::get_score() const {
    return score;
}

const std::string &Player_info::get_name() const {
    return username;
}

bool Player_info::operator==(Player_info &other) const {
    if(score == other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator!=(Player_info &other) const {
    if(score == other.score) {
        return false;
    }
    return true;
}

bool Player_info::operator<(Player_info &other) const {
    if(score < other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator<=(Player_info &other) const {
    if(score <= other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator>(Player_info &other) const {
    if(score > other.score) {
        return true;
    }
    return false;
}

bool Player_info::operator>=(Player_info &other) const {
    if(score >= other.score) {
        return true;
    }
    return false;
}

void Player_info::print() {
    printf("[%ld]%s - %d\n", uid, username.c_str(), score);
    return;
}

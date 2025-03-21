#include <iostream>
using namespace std;
typedef struct ThreadNode {
    int data;
    ThreadNode *left, *right;
    int ltag, rtag;
} ThreadNode, *ThreadTree;

// 中序线索化
void InThread(ThreadTree T, ThreadNode *&pre) {
    if (T != nullptr) {
        InThread(T->left, pre);
        if (T->left == nullptr) {
            T->left = pre;
            T->ltag = 1;
        }
        if (pre != nullptr && pre->right == nullptr) {
            pre->right = T;
            pre->rtag = 1;
        }
        pre = T;
        InThread(T->right, pre);
    }
}

// 中序遍历
void InOrderTraverse(Thread T) {
    if (T == nullptr) {
        return;
    }
    // generated by AI
    ThreadNode *p = T->left;
    while (p != T) {
        while (p->ltag == 0) p = p->left;
        cout << p->data << " ";
        while (p->rtag == 1 && p->right != T) {
            p = p->right;
            cout << p->data << " ";
        }
        p = p->right;
    }
    // or you can use this way
    ThreadNode *temp = T;
    while (temp != nullptr && temp->ltag == 0) {
        temp = temp->left;
    }
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->right;
    }
}


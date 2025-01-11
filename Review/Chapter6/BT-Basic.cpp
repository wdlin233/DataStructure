#include <iostream>
/*
1. 二叉树的顺序存储
*/
int const MAX_SIZE = 1<<10;
typedef int Tree[MAX_SIZE];

void CreateTree(Tree T, int n) {
    for (int i = 0; i < n; i++) {
        std::cin >> T[i];
    }
}

/*
2. 二叉树的链式存储
*/
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(BiTree &T) {
    int num;
    std::cin >> num;
    if (num == 0) {
        T = NULL;
    } else {
        T = new BiTNode;
        T->data = num;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

/*
3. 二叉树的遍历(4种)
*/
void PreOrderTraverse(BiTree T) { //DLR
    if (T) {
        std::cout << T->data << " ";
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void PreOrderTraverse_NonRecursive(BiTree T) {
    if (T) {
        std::stack<BiTree> S;
        S.push(T);
        while (!S.empty()) {
            BiTree p = S.top();
            S.pop();
            std::cout << p->data << " ";
            if (p->rchild) S.push(p->rchild); //先右后左，因为LILO
            if (p->lchild) S.push(p->lchild);
        }
    }
}

// 层次遍历
// 队列
void LevelOrderTraverse(BiTree T) {
    if (T) {
        std::queue<BiTree> Q;
        Q.push(T);
        while (!Q.empty()) {
            BiTree p = Q.front();
            Q.pop();
            std::cout << p->data << " ";
            if (p->lchild) Q.push(p->lchild);
            if (p->rchild) Q.push(p->rchild);
        }
    }
}

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node, *BSTree;

// 左子小于根，右子大于根

BSTree search(BSTree T, int key) {
    if (!T) return nullptr;
    if (T->data == key) return T;
    else if (T->data > key) return search(T->lchild, key);
    else return search(T->rchild, key);
}

BSTree insert(BSTree T, int key) {
    if (T == nullptr) {
        // If the tree is empty, create a new node
        T = (BSTree)malloc(sizeof(Node));
        T->data = key;
        T->lchild = T->rchild = nullptr;
    } else if (key < T->data) {
        // If the key is less than the current node's data, insert into the left subtree
        T->lchild = insert(T->lchild, key);
    } else if (key > T->data) {
        // If the key is greater than the current node's data, insert into the right subtree
        T->rchild = insert(T->rchild, key);
    }
    // If the key is equal to the current node's data, do nothing (assuming no duplicates)
    return T;
}

BSTree deleteNode(BSTree T, int key) {
    if (T == nullptr) {
        return T; // Key not found, return the tree as is
    }

    // Search for the node to be deleted
    if (key < T->data) {
        T->lchild = deleteNode(T->lchild, key);
    } else if (key > T->data) {
        T->rchild = deleteNode(T->rchild, key);
    } else {
        // Node with only one child or no child
        if (T->lchild == nullptr) {
            BSTree temp = T->rchild;
            free(T);
            return temp;
        } else if (T->rchild == nullptr) {
            BSTree temp = T->lchild;
            free(T);
            return temp;
        }

        // Node with two children: Get the in-order successor (smallest in the right subtree)
        // 将右子的最小节点替换当前节点，然后删除右子的最小节点
        BSTree temp = T->rchild;
        while (temp->lchild != nullptr) {
            temp = temp->lchild;
        }

        // Copy the in-order successor's content to this node
        T->data = temp->data;

        // Delete the in-order successor
        T->rchild = deleteNode(T->rchild, temp->data);
    }
    return T;
}
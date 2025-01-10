typedef struct DNode {
    int data;
    struct DNode *prior, *next;
} DNode, *DNodePtr;

void reverseDList(DNodePtr &L) {
    DNodePtr p = L->next, next_node = nullptr;
    L->next = nullptr;
    while (p != nullptr) {
        next_node = p->next;
        // 将各元素依次头插
        // 用四步将节点插入双向链表
        p->next = L->next;
        if (p->next != nullptr) {
            p->next->prior = p;
        }
        L->next = p;
        p->prior = L;
        // 将各元素依次头插
        p = next_node;
    }
}


typedef int datatype;
typedef struct node {
    datatype data;
    struct node *next;
} ListNode, *ListNodePtr;

// O(n^2)
void sortList(ListNodePtr &L) {
   ListNodePtr current = L->next->next; //第二个元素
   L->next->next = nullptr; // 断开链表
   while (current != nullptr) {
        ListNodePtr next_turn = current->next;
        ListNodePtr prev = L;
        while (prev->next != nullptr && prev->next->data < current->data) {
            prev = prev->next;
        } // 找到插入位置,prev是插入位置的前一个节点,找到 >= pivot的节点
        // 这就是把pivot插入到prev后面，经典链表插入方法
        // prev, current
        current->next = prev->next;
        prev->next = current;
        // 插入完成，current指向下一个节点
        current = next_turn;
    }
}

// O(n+m)
// with ordered list L1, L2, merge them into L1
void mergeList(ListNodePtr &L1, ListNodePtr &L2) {
    ListNodePtr p1 = L1->next;
    ListNodePtr p2 = L2->next;
    ListNodePtr pc = L1;
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data <= p2->data) {
            pc->next = p1;
            pc = pc->next; // ppt上写的是pc = p1;
            p1 = p1->next;
        } else {
            pc->next = p2;
            pc = pc->next;
            p2 = p2->next;
        }
    }
    /* ppt
    if (p1 == nullptr) p1 = p2;
    pc->next = p1;
    */
    if (p1 == nullptr) pc->next = p2;
    delete L2;
}



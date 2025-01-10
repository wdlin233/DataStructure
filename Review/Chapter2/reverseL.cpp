typedef int datatype;
typedef struct node {
    datatype data;
    struct node *next;
} ListNode, *ListNodePtr;

void reverseList(ListNodePtr &L) {
    ListNodePtr prev = nullptr;
    ListNodePtr curr = L->next;
    L->next = nullptr;
    while (curr != nullptr) {
        prev = curr;
        curr = curr->next;
        prev->next = L->next;
        L->next = prev;
    } // 将各元素依次头插
}

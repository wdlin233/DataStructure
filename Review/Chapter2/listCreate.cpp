/*
    malloc example:
    double * ptd;
    ptd = (double * ) malloc (30 * sizeof(double));
*/

typedef int datatype;
typedef struct node {
    datatype data;
    struct node *next;
} ListNode, *ListNodePtr;

// 头插法创建链表
void createListHead(ListNodePtr &L, datatype arr[], int n) {
    L = (ListNodePtr)malloc(sizeof(ListNode));
    L->next = NULL; // 头节点
    for (int i = 0; i < n; i++) {
        ListNodePtr p = (ListNodePtr)malloc(sizeof(ListNode));
        p->data = arr[i];
        p->next = L->next;
        L->next = p;
    }
}

// 尾插法创建链表
void createListTail(ListNodePtr &L, datatype arr[], int n) {
    L = (ListNodePtr)malloc(sizeof(ListNode));
    L->next = NULL; // 头节点
    ListNodePtr r = L; // 尾指针
    for (int i = 0; i < n; i++) {
        ListNodePtr p = (ListNodePtr)malloc(sizeof(ListNode));
        p->data = arr[i];
        p->next = NULL;
        r->next = p;
        r = p; // 更新尾指针
        // 因为只能从尾部插入，所以每次需要让指针顺延
    }
}

// 前插
// T(n) = O(n)
void insertList(ListNodePtr &L, datatype x, int i) {
    ListNodePtr p = L;
    for (int j = 0; j < i - 1; j++) {
        p = p->next;
    } // 找到第i个节点
    ListNodePtr s = (ListNodePtr)malloc(sizeof(ListNode));
    s->data = x;
    s->next = p->next;
    p->next = s;
}

void splitList(ListNodePtr &L, ListNodePtr &L1, ListNodePtr &L2) {
    ListNodePtr curr = L->next, next_node = nullptr;
    L1 = L;
    ListNodePtr r1 = L1; // L1尾指针
    L2 = (ListNodePtr)malloc(sizeof(ListNode));
    L2->next = nullptr;
    // 对L1尾插，L2头插
    while (curr != nullptr) {
        r1->next = curr;
        r1 = curr;
        //r1->next = nullptr; 之后置空，否则无法取了
        // 更新尾指针
        curr = curr->next;
        next_node = curr->next;
        // 创建临时节点
        curr->next = L2->next;
        L2->next = curr;
        // 头插
        curr = next_node;
    }
    r1->next = nullptr;
}


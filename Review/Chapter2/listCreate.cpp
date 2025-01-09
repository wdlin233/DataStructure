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

//前插

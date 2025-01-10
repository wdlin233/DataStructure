typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode, *StackNodePtr;


bool isEmpty(StackNodePtr S) {
    return S == nullptr;
}

void push(StackNodePtr &S, int e) {
    StackNodePtr p = (StackNodePtr)malloc(sizeof(StackNode));
    p->data = e;
    p->next = S;
    S = p;
}

int pop(StackNodePtr &S) {
    if (isEmpty(S)) {
        return -1;
    }
    int e = S->data;
    StackNodePtr p = S;
    S = S->next;
    free(p);
    return e;
}


int const MAXASIZE = 64;
typedef struct Stack {
    int data[MAXASIZE];
    int top;
} Stack, *StackPtr;

void initStack(StackPtr &S) {
    S->top = -1; // 置栈空
}

bool isEmpty(StackPtr S) {
    return S->top == -1;
}

void push(StackPtr &S, int e) {
    if (S->top == MAXASIZE - 1) {
        return;
    }
    S->data[++S->top] = e;
}

int pop(StackPtr &S) {
    if (isEmpty(S)) {
        return -1;
    }
    return S->data[S->top--];
}


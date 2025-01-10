int const MAXASIZE = 64;
typedef struct Stack {
    int data[MAXASIZE];
    int top;
} Stack, *StackPtr;

// From decimal to binary
void transform(int n) {
    StackPtr S = (StackPtr)malloc(sizeof(Stack));
    initStack(S);
    while (n != 0) {
        push(S, n % 2); //从低位到高位入栈
        n /= 2;
    }
    while (!isEmpty(S)) {
        std::cout << pop(S);
    }
}

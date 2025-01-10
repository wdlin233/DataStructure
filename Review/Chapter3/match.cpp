int const MAXASIZE = 64;
typedef struct Stack {
    int data[MAXASIZE];
    int top;
} Stack, *StackPtr;

bool isMatch(char *str) {
    StackPtr S = (StackPtr)malloc(sizeof(Stack));
    initStack(S);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            push(S, str[i]);
        }
        else if (str[i] == ')') {
            if (isEmpty(S)) {
                return false;
            }
            pop(S);
        }
    }
    return isEmpty(S);
}


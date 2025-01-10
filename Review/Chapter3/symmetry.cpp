int const MAXASIZE = 64;
typedef struct Stack {
    char data[MAXASIZE];
    int top;
} Stack, *StackPtr;

bool isSymmetry(char *str) {
    StackPtr S = (StackPtr)malloc(sizeof(Stack));
    initStack(S);
    for (int i = 0; str[i] != '\0'; i++) {
        push(S, str[i]);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != pop(S)) {
            return false;
        }
    }
    return true;
}

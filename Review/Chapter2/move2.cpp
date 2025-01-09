#define MAX_SIZE 1024
typedef struct {
    int data[MAX_SIZE];
    int length;
} SqList, *SqListPtr;

/*
    From x, unordered list
    <=x, x, >x
*/
void move1(SqList *&L) {
    int i = 0;
    int j = L->length - 1;
    int pivot = L->data[0]; // 以data[0]为基准
    while (i < j) {
        while (i < j && L->data[j] > pivot) j--; // 从右到左找到第一个 <= pivot的元素
        while (i < j && L->data[i] <= pivot) i++; // 从左到右找到第一个 > pivot的元素
        if (i < j) {
            swap(L->data[i], L->data[j]);
        }
        // it would be slower
    }
}

void move2(SqList *&L) {
    int i = 0;
    int j = L->length - 1;
    int temp = L->data[0]; // 以data[0]为临时值，可以写作pivot
    while (i < j) {
        while (j > i && L->data[j] > temp) j--; // 从右到左找到第一个 <= pivot的元素
        L->data[i] = L->data[j];
        while (i < j && L->data[i] <= temp) i++; // 从左到右找到第一个 > pivot的元素
        L->data[j] = L->data[i];
    }
    L->data[i] = temp;
}
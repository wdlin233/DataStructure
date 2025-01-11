typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode, *QueueNodePtr;

typedef struct Queue {
    QueueNodePtr front;
    QueueNodePtr rear;
} Queue, *QueuePtr;

void initQueue(QueuePtr &Q) {
    Q->front = Q->rear = (QueueNodePtr)malloc(sizeof(QueueNode));
    Q->front->next = nullptr;
}

bool isEmpty(QueuePtr Q) {
    return Q->front->next == nullptr;
}

void enQueue(QueuePtr &Q, int e) {
    QueueNodePtr p = (QueueNodePtr)malloc(sizeof(QueueNode));
    p->data = e;
    p->next = nullptr;
    if (Q->front->next == nullptr) {
        Q->front->next = p;
    } else {
        Q->rear->next = p;
    }
    Q->rear = p;
}

int deQueue(QueuePtr &Q) {
    if (isEmpty(Q)) {
        return -1;
    }
    QueueNodePtr p = Q->front->next;
    int e = p->data;
    Q->front->next = p->next;
    if (isEmpty(Q)) {
        Q->rear = Q->front;
    }
    free(p);
    return e;
}

/*
使用循环队列，不会出现假溢出
队空：count == 0 || front == rear
队满：count == maxSize || (rear + 1) % maxSize == front
进队：rear = (rear + 1) % maxSize
出队：front = (front + 1) % maxSize

count = (rear - front + maxSize) % maxSize
rear = (front + count) % maxSize
front = (rear - count + maxSize) % maxSize
*/

int const MAX_SIZE = 1024;

typedef struct {
    int data[MAX_SIZE];
    int front;
    int count;
} cQueue, *cQueuePtr;

void initQueue(cQueuePtr &Q) {
    Q->front = 0;
    Q->count = 0;
}

bool isEmpty(cQueuePtr Q) {
    return Q->count == 0;
}

bool isFull(cQueuePtr Q) {
    return Q->count == MAX_SIZE;
}

void enQueue(cQueuePtr &Q, int e) {
    if (isFull(Q)) {
        return;
    }
    int rear_tmp = (Q->front + Q->count) % MAX_SIZE;
    Q->data[rear_tmp] = e;
    Q->count++;
}

int deQueue(cQueuePtr &Q) {
    if (isEmpty(Q)) {
        return -1;
    }
    // 如果是先 +1 再取值，则在enQueue时多了 +1.
    int e = Q->data[Q->front]; //注意顺序
    Q->front = (Q->front + 1) % MAX_SIZE;
    Q->count--;
    return e;
}


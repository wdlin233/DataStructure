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





#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
#include "stack.h"

template <class T>
class Queue {
private:
    //TODO
public:
    Queue();
    Queue(Queue &other);
    ~Queue();
    Queue &operator=(Queue &other);
    int get_size() const;
    void push(T *t);
    void push(Node<T> *n);
    Node<T> *pop();
    void print();
};

#include "queue.cpp"
#endif

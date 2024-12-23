#include "queue.h"
#include <iostream>
template <class T>
Queue<T>::Queue() {
    // TODO
    cnt = 0;
    head = nullptr;
    tail = nullptr;
}

template <class T>
Queue<T>::Queue(Queue &other) {
    // TODO
    cnt = other.cnt;
    if (other.head == nullptr) {
        head = new Node<T>();
    } else {
        head = new Node<T>(*(other.head));
        copy(this->head, other.head);
        tail = head;
        while (tail->get_next() != nullptr) {
            tail = tail->get_next();
        }
    }
}

template <class T>
Queue<T>::~Queue() {
    // TODO
    remove(head);
}

template <class T>
Queue<T> &Queue<T>::operator=(Queue &other) {
    // TODO
    cnt = other.cnt;
    if (other.head == nullptr) {
        head = new Node<T>();
    } else {
        head = new Node<T>(*(other.head));
        copy(this->head, other.head);
        tail = head;
        while (tail->get_next() != nullptr) {
            tail = tail->get_next();
        }
    }
    return *this;
}

template <class T>
int Queue<T>::get_size() const {
    // TODO
    return cnt;
}

template <class T>
void Queue<T>::push(T *t) {
    // TODO
    if (t == nullptr) return;
    if (head == nullptr) {
        head = new Node<T>(t);
        tail = head;
    } else {
        Node<T> *tmp = new Node<T>(t);
        tail->set_next(tmp);
        tail = tmp;
    }
    cnt += 1;
}

template <class T>
void Queue<T>::push(Node<T> *n) {
    // TODO
    if (n == nullptr) return;
    if (head == nullptr) {
        head = new Node<T>(*n);
        tail = head;
    } else {
        Node<T> *tmp = new Node<T>(*n);
        tail->set_next(tmp);
        tail = tmp;
    }
    cnt += 1;
}

template <class T>
Node<T> *Queue<T>::pop() {
    // TODO
    if (cnt > 0) {
        Node<T> *tmp = head;
        head = head->get_next();
        cnt -= 1;
        return tmp;
    }
    return NULL;
}

template <class T>
void Queue<T>::print() {
    // TODO
    Node<T> *p = head;
    Stack<T> *s = new Stack<T>();
    while (p != nullptr) {
        s->push(p->ptr);
        p = p->get_next();
    }
    s->print();
    std::cout << "END"<< std::endl;
    return;
}

template <class T>
void Queue<T>::remove(Node<T> *n) {
    if (n == NULL) {
        return;
    }
    if (n->get_next() == NULL) {
        delete n;
        return;
    }
    Node<T> *tmp = n->get_next();
    delete n;
    remove(tmp);
    return;
}

template <class T>
void Queue<T>::copy(Node<T> *this_, Node<T> *other_) {
    if (other_->get_next() == NULL) {
        return;
    }
    this_->set_next(new Node<T>(*(other_->get_next())));
    copy(this_->get_next(), other_->get_next());
    return;
}
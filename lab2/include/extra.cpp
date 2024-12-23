#include <stack>
#include <queue>
int Compare_stack_queue(std::stack<int> *s, std::queue<int> *q);
void copy(std::stack<int> *s, std::queue<int> *q);
int compare(std::stack<int> *s, std::stack<int> *t);

void copy(std::stack<int> *s, std::queue<int> *q) {
    if (q->size() == 0) return;
    else {
        s->push(q->front());
        q->pop();
        copy(s, q);
    }
}

int compare(std::stack<int> *s, std::stack<int> *t) {
    if (s->size() == t->size() && t->size() == 0) return 1;
    else if (s->top() != t->top()) return 0;
    else {
        s->pop();
        t->pop();
        return compare(s, t);
    }
    //return compare(s, t);
}

int Compare_stack_queue(std::stack<int> *s, std::queue<int> *q) {
    // TODO
    if (q->size() != s->size()) return 0;
    std::stack<int> *tmp = new std::stack<int>();
    copy(tmp, q);
return compare(s, tmp);
    return 1;
}

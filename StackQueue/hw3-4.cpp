#include <iostream>
#include <algorithm>
#include <stack>
#include <deque> // rather than queue

char org[25];
std::stack<char> S;
std::deque<char> postfix;
std::stack<int> eval;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b; 
        case '*': return a * b;
        case '/': return a / b; 
    }
    return 0;
}

int main(void) {
    std::cin >> org;
    for (int i = 0; org[i] != '\0'; i++) {
        if ('0' <= org[i] && org[i] <= '9') {
            postfix.push_back(org[i]);
        }
        else if (org[i] == '(') {
            S.push('(');
        }
        else if (org[i] == ')') {
            while (S.top() != '(') {
                postfix.push_back(S.top());
                S.pop();
            }
            S.pop();
        }
        else {
            while (!S.empty() && precedence(org[i]) <= precedence(S.top())) {
                postfix.push_back(S.top());
                S.pop();
            }
            S.push(org[i]);
        }
    }
    while(!S.empty()) {
        postfix.push_back(S.top());
        S.pop();
    }

    //std::deque<char>::iterator el = postfix.begin();
    for (auto it = postfix.begin(); it != postfix.end(); ++it) {
        //std::cout << *it << " ";
        if ('0' <= *it && *it <= '9') {
            eval.push(*it - '0');
        }
        else {
            int tmp_1 = 0, tmp_2 = 0;
            tmp_1 = eval.top();
            eval.pop();
            tmp_2 = eval.top();
            eval.pop();
            eval.push(applyOp(tmp_2, tmp_1, *it)); // attention tmp2 op tmp1
            // because postfix => tmp2 tmp1 op
        } 
    }
    std::cout << eval.top();
    return 0;
}
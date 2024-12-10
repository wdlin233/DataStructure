#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

char str[30];
std::queue<char> Q;
std::stack<char> S;
int i = 0;
bool ok = true;

int main() {
    std::cin >> str;
    for (; str[i] != '@'; i++) {
        Q.push(*(str + i));
        S.push(*(str + i));
    }
    while (!Q.empty() && !S.empty()) {
        if (Q.front() != S.top()) {
            ok = false;
            break;
        }
        else {
            Q.pop();
            S.pop();
        }
    }
    if (ok == true) std::cout << "true";
    else std::cout << "false";
    return 0;
}
#include <iostream>
#include <stack>
#include <vector>
// THIS WORTH LEARNING.
// 即根据popSequence判断是否需要入栈，若栈顶元素与popSequence不符则说明需要入栈至当前元素的值，否则需要出栈；
// 若无法顺利出栈则说明不构成序列，返回NO.
// 模拟一个栈的入栈和出栈.
bool isValidStackSequence(int n, std::vector<int>& popSequence) {
    std::stack<int> s;
    int current_push = 1;

    for (int i = 0; i < n; ++i) {
        int target = popSequence[i];

        // Push all necessary elements to fulfill the next pop operation
        while (current_push <= n && (s.empty() || s.top() != target)) {
            s.push(current_push++);
        }

        // If the top element is the desired one, pop it
        if (!s.empty() && s.top() == target) {
            s.pop();
        } else {
            return false; // If we can't match the sequence, return false
        }
    }

    return true; // If we successfully pop the entire sequence, it's valid
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> popSequence(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> popSequence[i];
    }

    if (isValidStackSequence(n, popSequence)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}

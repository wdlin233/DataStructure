#include <iostream>
#include <vector>
#include <algorithm>

int N = 0, M = 0;

int main(void) {
    std::cin >> N >> M;
    // if (N == 10000 && M == 9999) {
    //     for (int i = 0; i < 9999; i++) std::cout << std::endl;
    //     for (int i = 10000; i > 0; i--) std::cout << i << ' ';
    //     std::cout << std::endl;
    // }
    std::vector<std::vector<int>> table(N);
    for (int i = 0; i < N; i++) {
        table[i].push_back(i+1);
    }
    int val1 = 0, val2 = 0;
    for (int i = 0; i < M; i++) {
        std::cin >> val1 >> val2;
        if (val1 == val2) continue;
        else {
            for (auto it = table[val2-1].begin(); it != table[val2-1].end(); it++) {
                table[val1-1].push_back(*it);
            }
            //table[val2-1].clear();
            // I don't know why, but .clear() will stop
            // maybe the capacity is limited
            std::vector<int> t;
			table[val2-1].swap(t);
        }
    }
    for (int i = 0; i < N; i++) {
        if (table[i].empty()) {
            std::cout << std::endl;
            continue;
        }
        else {
            for (auto it = table[i].begin(); it != table[i].end(); it++) {
                std::cout << *it << ' ';
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
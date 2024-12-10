#include <iostream>
#include <vector>
#include <algorithm>

int N = 0, M = 0;
int op = 0;

void swap(std::vector<std::vector<int>>& table, int x, int y, int z) {
    if (x == 0) {
        for (int i = 0; i < M; i++) {
            std::swap(table[y-1][i], table[z-1][i]);
        }
    }
    else if (x == 1) {
        for (int i = 0; i < N; i++) {
            std::swap(table[i][y-1], table[i][z-1]);
        }
    }
}

int main(void) {
    std::cin >> N >> M;
    std::vector<std::vector<int>> table(N, std::vector<int>(M)); // 大数组时的使用.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> table[i][j];
        }
    }
    std::cin >> op;
    int x = 0, y = 0, z = 0;
    for (int i = 0; i < op; i++) {
        std::cin >> x >> y >> z;
        swap(table, x, y, z);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << table[i][j];
            if (j != M-1) std::cout << ' ';
        }
        if (i != N-1) std::cout << std::endl;
    }
    return 0;
}
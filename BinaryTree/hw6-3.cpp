#include <iostream>
#include <cmath>
#include <vector>

int depth = 0;
int monkey_num = 0;
int val_fin = 0;

int traverse(std::vector<bool>& sw_opened, int root, int length) {
    if (sw_opened[root] == false && root * 2 <  length) {
        sw_opened[root] = true;
        return traverse(sw_opened, root*2, length);
    }
    else if (sw_opened[root] == true && root * 2 + 1 < length) {
        sw_opened[root] = false;
        return traverse(sw_opened, root * 2 + 1, length);
    }
    else
        return root;
}

int main(void) {
    while (std::cin >> depth >> monkey_num) {
        if (depth == 0 && monkey_num == 0) break;
        if (depth == 1 && monkey_num == 1) {
            std::cout << 1 << std::endl;
            continue;
        }
        std::vector<bool> sw_opened(int(pow(2, depth + 1)) + 5, false);
        for (int i = 1; i <= monkey_num; i++) {
            val_fin = traverse(sw_opened, 1, int(pow(2, depth)));
            if (i == monkey_num) std::cout << val_fin << std::endl;
        }
    }
    return 0;
}
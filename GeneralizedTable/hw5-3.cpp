#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int N = 0;
int person = 0;
int tmp = 0, k = 0;
int mentioned_max = 0, mentioned_size = 0;
int mentioned[101] = {0};
bool mentioned_flag[101][101] = {0};
std::vector<std::vector<int>> mention_list(101);


int main(void) {
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> person;
        std::cin >> k;
        for (int j = 0; j < k; j++) {
            std::cin >> tmp;
            mentioned[tmp]++;
            if (tmp > mentioned_size) mentioned_size = tmp;
            if (mentioned_flag[person][tmp] == false) {
                mention_list[tmp].push_back(person);
                mentioned_flag[person][tmp] = true;
            }
            else
                continue;
        }
    }
    for (int i = 0; i < mentioned_size; i++) {
        if (mentioned[i] > mentioned[mentioned_max]) mentioned_max = i;
    }
    std::cout << mentioned_max << std::endl;
    sort(mention_list[mentioned_max].begin(), mention_list[mentioned_max].end());
    for (int i = 0; i < mention_list[mentioned_max].size(); i++) {
        std::cout << mention_list[mentioned_max][i] << ' ';
    }
    return 0;
}
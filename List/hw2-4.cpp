#include <iostream>
#include <algorithm>
#include <queue>

// 求最长不重复子数组的长度
std::queue<int> Q;
int N = 0, length = 0;
int scene[100003] = {0}; // 1 * 10^5
bool scene_is_chosed[1000003] = {0}; // 1 * 10^6

int main(void){
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        std::cin >> tmp;
        scene[i] = tmp;
    }

    for (int i = 0; i < N; i++) {
        if (scene_is_chosed[ scene[i] ] == false) {
            scene_is_chosed[ scene[i] ] = true;
            Q.push( scene[i] );
        }
        else { //scene[i]已在队中：退队首元素直到 scene[i] 出现，再入队
            while(!Q.empty()) {
                if (Q.front() != scene[i]) {
                    scene_is_chosed[ Q.front() ] = false; // Q.front() 已不在队中
                    Q.pop();
                }
                else {
                    Q.pop();
                    Q.push( scene[i] );
                    break;
                }
            }
        }

        if (Q.size() > length) length = Q.size();
    }
    std::cout << length;
    return 0;
}
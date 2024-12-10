#include <iostream>
#include <algorithm>
#include <queue>

int type = -1;
long long number = 0;
//std::queue <std::pair<int, long long>> Q;
std::queue <long long> Q0;
std::queue <long long> Q1;
std::queue <long long> Q2;
int main(void) {
    while (std::cin >> type >> number) {
        //Q.push(std::make_pair(type, number));
        if (type == 0) Q0.push(number);
        else if (type == 1) Q1.push(number);
        else if (type == 2) Q2.push(number); 
    }
    for (int i = 0; i < 10; i++) {
        if (!Q0.empty()) {
            std::cout << Q0.front();
            Q0.pop();
        }
        else std::cout << 0;
        std::cout << " ";
        if (!Q1.empty()) {
            std::cout << Q1.front();
            Q1.pop();
        }
        else std::cout << 0;
        std::cout << " ";
        if (!Q2.empty()) {
            std::cout << Q2.front();
            Q2.pop();
        }
        else std::cout << 0;
        std::cout << std::endl;
    }
    return 0;
} 
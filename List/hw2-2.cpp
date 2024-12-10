#include <iostream>
#include <algorithm>
#include <list>

std::list<int> L;
int N = 0, M = 0; // from N move M. 
int main(void){
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        L.push_back(i);
    }

    for (int i = 0; i < M; i++) {
        std::list<int>::iterator it = L.begin();
        int temp = 0;
        std::cin >> temp;
        for (int L_index = 0; L_index < temp - 1; L_index++) { // pay attention to: temp - 1
            it++;
        }
        // std::advance(it, temp);
        L.erase(it);
    }
    std::list<int>::iterator it = L.begin();
    for (int i = 0; i < ((L.size() - 1)/2); i++) {
        it++;
    }
    std::cout << *it;
    return 0;
}
#include <iostream>
#include <algorithm>
#include <list>

std::list<int> LA, LB, LC;
int A_num, B_num;

int main(void){
    std::cin >> A_num;
    for (int i = 0; i < A_num; i++) {
        int tmp;
        std::cin >> tmp;
        LA.push_back(tmp);
    }
    
    std::cin >> B_num;
    for (int i = 0; i < B_num; i++) {
        int tmp;
        std::cin >> tmp;
        LB.push_back(tmp);
    }

    std::list<int>::iterator el_a = LA.begin();
    std::list<int>::iterator el_b = LB.begin();
    int el_a_index = 0, el_b_index = 0;
    while(el_a_index < LA.size() && el_b_index < LB.size()) {
        if (*el_a == *el_b) {
            LC.push_back(*el_a);
            el_a++;
            el_a_index++;
            el_b++;
            el_b_index++;
        }
        else if (*el_a > *el_b) {
            el_b++;
            el_b_index++;
        }
        else if (*el_b > *el_a) {
            el_a++;
            el_a_index++;
        }
    }

    
    std::cout << LC.size() << std::endl;
    //std::for_each(LC.begin(), LC.end(), [](const int n) { std::cout << n << ' '; });
    std::list<int>::iterator el_c = LC.begin();
    if(LC.size() != 0){
        for (int el_c_index = 0; el_c_index < LC.size() - 1; el_c_index++, el_c++) {
            std::cout << *el_c << ' ';
        }
        std::cout << *el_c;
    }
    return 0;
}
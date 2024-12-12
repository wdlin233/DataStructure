#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int num;
struct victim {
    string id;
    int age;
    int order;
};

// comparison function object  
// which returns ​true if the first argument is less than (i.e. is ordered before) the second.
bool cmp(victim p1, victim p2) {
    if (p1.age >= 60 || p2.age >= 60) // 不能用&&
        return p1.age > p2.age;
    else   
        return p1.order < p2.order;
}

// 题解：
// bool cmp(victim p1, victim p2) {
//     if (p1.age >= 60 && p2.age >= 60)  // 可以||
//         return p1.age > p2.age;
//     else   
//         return p1.age >= 60;
// }

// wrong answer
// bool cmp(victim p1, victim p2) {
//     if (p1.age >= 60 || p2.age >= 60)  
//         return p1.age > p2.age; // 这不能保证60岁以上在前
// }

int main(void) {
    cin >> num;
    vector<victim> vec;
    for (int i = 0; i < num; i++) {
        victim tmp;
        cin >> tmp.id >> tmp.age;
        tmp.order = i;
        vec.push_back(tmp);
    }
    // stable_sort 保证了相同的元素不会被交换位置
    stable_sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < num; i++) {
        cout << vec[i].id << endl;
    }
    return 0;
}
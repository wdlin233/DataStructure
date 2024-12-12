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

bool cmp(victim p1, victim p2) {
    // if (p1.age > p2.age && p1.age >= 60 && p2.age >= 60)
    //     return true;
    // else 
    //     return p1.order < p2.order;
    if (p1.age >= 60 || p2.age >= 60)
        return p1.age > p2.age;
    else   
        return p1.order < p2.order;
    //return (p1.age > p2.age && p1.age >= 60 && p2.age >= 60) || (p1.order < p2.order);
}

int main(void) {
    cin >> num;
    vector<victim> vec;
    for (int i = 0; i < num; i++) {
        victim tmp;
        cin >> tmp.id >> tmp.age;
        tmp.order = i;
        vec.push_back(tmp);
    }
    sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < num; i++) {
        cout << vec[i].id << endl;
    }
    return 0;
}
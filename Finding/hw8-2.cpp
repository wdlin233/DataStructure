#include<iostream>
#include<vector>
using namespace std;
int N, target;
vector<int> vec;
int main(void) {
    cin >> N;
    int temp;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        vec.push_back(temp);
    }
    cin >> target;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; i < j && j < N; j++)
            if (vec[i] + vec[j] == target) cout << i + 1 << ' ' << j + 1 << endl;
    }
    return 0;
}
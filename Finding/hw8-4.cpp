#include<iostream>
#include<set>
using namespace std;
int M, N;
set<int> S;
// or use map<int, int>

int main(void) {
    cin >> M >> N;
    int temp;
    for (int i = 0; i < M; i++) {
        cin >> temp;
        S.insert(temp);
    }
    for (int i = 0; i < N; i++) {
        cin >> temp;
        auto search = S.find(temp);
        if (search != S.end()) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

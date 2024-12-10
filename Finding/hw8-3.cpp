#include<iostream>
#include<vector>
using namespace std;
int N;
int vec[1000005];
int main(void) {
    cin >> N;
    int temp;
    for (int i = 0; i < N; i++) {
        cin >> temp;
        if (temp > 0) vec[temp] = 1;
    }
    for (int i = 1; i <= 1000005; i++) {
        if (vec[i] == 0) {
            cout << i;
            break;
        }
    }
    return 0;
}

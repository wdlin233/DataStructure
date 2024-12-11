#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int N, M;
vector<string> vec;

int antiNum(string data, int length) {
    int result = 0;
    for(int i = 0; i < length; i++)
    {
        for(int j = i + 1; j < length; j++)
        {
            if(data[i] > data[j])
            {
                result++;
            }
        }
    }
    return result;
}

// compare string's antiNum number to sort
bool cmp(string a, string b) {
    return antiNum(a, a.length()) <= antiNum(b, b.length());
}

int main(void) {
    cin >> N >> M;
    string str;
    for (int i = 0; i < M; i++) {
        cin >> str;
        vec.push_back(str);
    }
    sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < M; i++) {
        cout << vec[i] << endl;
    }
    return 0;
}
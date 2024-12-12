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
    return antiNum(a, a.length()) < antiNum(b, b.length());
}

int main(void) {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        string str;
        cin >> str;
        vec.push_back(str);
    }
    // 因为题目要求 逆序对数相同的字符串按照输入顺序输出
    stable_sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < M; i++) {
        cout << vec[i] << endl;
    }
    return 0;
}
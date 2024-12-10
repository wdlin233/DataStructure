#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <set>

using namespace std;
int N;
//vector<string> vec;
set<string> vec;

int main(void) {
    std::cin >> N;
    for(int i = 0;i < N; i++) {
        string chs;
        cin >> chs;
        //cout << chs << endl;
        transform(chs.begin(), chs.end(), chs.begin(), ::tolower);
        // or you can use "for" loop to replace it.
        //bool flag = false;
        // for (int j = 0; j < vec.size(); j++){
        //     if (chs == vec[j]) flag = true; 
        // }
        auto search = vec.find(chs);
        if (search != vec.end())
            std::cout << "Yes" << endl;
        else {
            std::cout << "No" << endl;
            vec.insert(chs);
        }
        // if(flag)
        //     cout << "Yes" << endl;
        // else{
        //     vec.push_back(chs);
        //     cout << "No" << endl;
        // }
    }

    return 0;
}
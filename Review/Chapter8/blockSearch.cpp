#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 分块查找函数
int blockSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    int blockSize = sqrt(n); // 块大小
    int numBlocks = ceil((double)n / blockSize); // 块数量

    // 创建块的最大值数组
    // 找到对应Block中最大的值，用于之后确定在哪个Block中查找
    vector<int> blockMax(numBlocks, INT_MIN);
    for (int i = 0; i < n; ++i) {
        int blockIndex = i / blockSize;
        blockMax[blockIndex] = max(blockMax[blockIndex], arr[i]);
    }

    // 在块之间查找目标元素可能所在的块
    int blockIndex = -1;
    for (int i = 0; i < numBlocks; ++i) {
        if (target <= blockMax[i]) {
            blockIndex = i;
            break;
        }
    }

    // 如果没有找到合适的块，返回 -1
    if (blockIndex == -1) {
        return -1;
    }

    // 在找到的块内进行顺序查找
    // yzdmuabi
    int start = blockIndex * blockSize;
    int end = min(start + blockSize, n);
    for (int i = start; i < end; ++i) {
        if (arr[i] == target) {
            return i; // 找到目标元素，返回索引
        }
    }

    return -1; // 未找到目标元素，返回 -1
}

int main() {
    // 第i块均小于i+1块，块内无序
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int target = 7;
    int result = blockSearch(arr, target);

    if (result != -1) {
        cout << "Element found at index " << result << endl;
    } else {
        cout << "Element not found in the array" << endl;
    }

    return 0;
}
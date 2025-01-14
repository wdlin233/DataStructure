/*
内排序：
(1) 插入排序
- 直接插入
- 折半插入
- 链表插入
- 希尔排序
(2) 交换排序
- 冒泡排序
- 快速排序
(3) 选择排序
- 直接选择
- 堆选择
(4) 归并排序
(5) 基数排序
*/
#include <iostream>
#include <vector>

// 插入排序函数
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        // 每次都前[0, i]有序
        int key = arr[i]; // 当前需要插入的元素
        int j = i - 1;

        // 将比key大的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // 插入key到正确位置
    }
}

// 希尔排序函数
void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    // 初始间隔（gap）为数组长度的一半，逐步缩小间隔
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 对一个gap内的元素，进行间隔的插入排序
        // 确实如此，它略过了第一个gap，直接从第二个gap开始
        for (int i = gap; i < n; i++) {
            int temp = arr[i]; 
            int j;
            
            // 将比temp大的元素向后移动
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp; 
        }
    }
}

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

// 冒泡排序函数
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool flag = false; // 用于标记是否发生交换
        // 使最后一个元素开始往前归位，不仅仅是有序
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        if (!flag) break; // 如果没有发生交换，说明已经有序，一个优化
    }
}

// 快速排序函数
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int i = low, j = high;
    int pivot = arr[low]; // 选取第一个元素作为基准
    while (i < j) {
        // 从右向左找第一个小于pivot的元素
        while (i < j && arr[j] >= pivot) j--;
        if (i < j) arr[i++] = arr[j]; // 将pivot所在位置，以arr[j]填充
        // 从左向右找第一个大于pivot的元素
        while (i < j && arr[i] < pivot) i++;
        if (i < j) arr[j--] = arr[i]; // 将j所在位置，以arr[i]填充
    }
    arr[i] = pivot; // 将i所在位置以pivot填充
    quickSort(arr, low, i - 1); 
    quickSort(arr, i + 1, high); 
}

// 简单选择排序
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        // 选择最小的元素的下标，数值可能不唯一
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 和第i个元素交换
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

// 堆排序
// 对完全二叉树，大根堆
void heapify(std::vector<int>& arr, int n, int i) {
    int largest_index = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    // 如果左子节点大于根节点
    if (l < n && arr[l] > arr[largest_index]) {
        largest_index = l;
    }
    // 如果右子节点大于根节点
    if (r < n && arr[r] > arr[largest_index]) {
        largest_index = r;
    }
    // 如果最大值不是根节点
    if (largest_index != i) {
        std::swap(arr[i], arr[largest_index]);
        // 递归调整其他不满足堆的子树
        heapify(arr, n, largest_index);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // 构建大根堆，从最后一个非叶子节点开始
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // 为实现升序排列，将堆顶元素与最后一个元素交换
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        // 重新构建大根堆
        heapify(arr, i, 0); // i(n)为堆的大小，故不会调整刚刚被归位的元素
    }
    // Q&A:大根堆只能保证堆顶的最大，不能保证下列各数都保持降序（按索引）
    // 所以无论是大根堆升序还是小根堆降序都需要再最后与堆顶交换
}

// 归并排序
// 将两个有序数组合并为一个，称归并merge
void merge(std::vector<int>& arr, int left, int mid, int right) {
    // 计算左右两个子数组的大小
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // 创建临时数组来存储左右子数组
    std::vector<int> leftArray(leftSize);
    std::vector<int> rightArray(rightSize);

    // 将数据复制到临时数组中
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArray[j] = arr[mid + 1 + j];
    }

    // 合并两个有序数组
    int i = 0; // 左子数组的索引
    int j = 0; // 右子数组的索引
    int k = left; // 合并后数组的索引

    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // 如果左子数组还有剩余元素，直接复制到合并后的数组中
    while (i < leftSize) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // 如果右子数组还有剩余元素，直接复制到合并后的数组中
    while (j < rightSize) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    // 递归排序左右两个子数组
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    // 合并两个有序数组
    merge(arr, left, mid, right);
}

// 基数排序
// 非比较排序
// 从最低位开始 LSD

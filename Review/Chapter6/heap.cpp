/*
    满足父节点大于子节点则称大根堆，父节点小于子节点则称小根堆
    堆的实现一般是使用数组，逻辑上是一个完全二叉树
    堆可用于实现优先队列，例如OS的进程调度
*/

int const MAX_SIZE = 1024;
typedef struct {
    int arr[MAX_SIZE];
    int size;
} MaxHeap;

void init(MaxHeap &heap) {
    heap.size = 0;
}

// O(logn)
void insert(MaxHeap &heap, int val) {
    if (heap.size >= MAX_SIZE) return;
    heap.size++;
    heap.arr[heap.size] = val;
    int i = heap.size;
    while (i / 2 > 0 && heap.arr[i] > heap.arr[i / 2]) { // 如果子节点大于父节点，则交换
        std::swap(heap.arr[i], heap.arr[i / 2]);
        i = i / 2;
    }
}

int remove(MaxHeap &heap) {
    if (heap.size == 0) return -1; // 堆为空
    int res = heap.arr[1];
    heap.arr[1] = heap.arr[heap.size]; // 用最后一个节点填补堆顶
    heap.size--;
    // Adjust
    int i = 1;
    while (i * 2 <= heap.size) {
        int t = i * 2;
        if (t + 1 <= heap.size && heap.arr[t + 1] > heap.arr[t]) t++; // 找到左右子节点中较大的
        if (heap.arr[t] <= heap.arr[i]) break;
        std::swap(heap.arr[t], heap.arr[i]);
        i = t;
    }
    return res;
}

void build(MaxHeap &heap, int arr[], int n) { // O(n), 乱序建堆
    for (int i = 0; i < n; i++) {
        heap.arr[i + 1] = arr[i];
    }
    heap.size = n;
    for (int i = n / 2; i >= 1; i--) { // 对各内点进行下沉操作
        // 如果使用up()，T(n)=O(nlogn)
        // 使用down()，T(n)=O(n)
        down(heap, i);
    }
}

void up(MaxHeap &h, int x) {
  while (x > 1 && h[x] > h[x / 2]) {
    std::swap(h[x], h[x / 2]);
    x /= 2;
  }
}

void down(MaxHeap &h, int x) { // 下沉
  while (x * 2 <= h.size) {
    int t = x * 2;
    if (t + 1 <= h.size && h[t + 1] > h[t]) t++; // 找到左右子节点中较大的
    if (h[t] <= h[x]) break;
    std::swap(h[x], h[t]);
    x = t;
  }
}
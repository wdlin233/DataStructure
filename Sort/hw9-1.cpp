#include <iostream>
#include <vector>
using namespace std;
int num;
int vec[100005];

template <typename T>
int Paritition(T A[], int low, int high) {
  int pivot = A[low];
  while (low < high) {
    while (low < high && pivot <= A[high]) --high;
    A[low] = A[high];
    while (low < high && A[low] <= pivot) ++low;
    A[high] = A[low];
  }
  A[low] = pivot;
  return low;
}
template <typename T>
void QuickSort(T A[], int low, int high) {
  if (low < high) {
    int pivot = Paritition(A, low, high);
    QuickSort(A, low, pivot - 1);
    QuickSort(A, pivot + 1, high);
  }
}
template <typename T>
void QuickSort(T A[], int len) {
  QuickSort(A, 0, len - 1);
}

int main(void) {
    cin >> num;
    int temp = 0, div = 0;
    for (int i = 0; i < num; i++) {
        cin >> vec[i];
    }
    QuickSort(vec, num);
    if (num % 2 == 0) 
        div = num / 2;
    else
        div = num / 2 + 1; // modify here 
    cout << vec[num - div] << ' ' << div;
    return 0;
}
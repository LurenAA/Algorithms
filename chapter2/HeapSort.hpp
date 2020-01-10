#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;
/**
 * 堆排序
 **/
template<typename T>
class HeapSort {
  public:
    static void sort(vector<T>&);
  private:
    static void sink(vector<T>& a, int k, int N);
};

template<typename T>
void HeapSort<T>::sort(vector<T>& a) {
  int N = a.size() - 1;
  for(int i = N / 2; i >= 1; --i)
    sink(a, i, N);
  while(N > 1) {
    swap(a[1], a[N--]);
    sink(a, 1, N);
  }
}

template<typename T>
void HeapSort<T>::sink(vector<T>& a, int k, int N) {
  int j;
  while(k <= N / 2) {
    j = 2 * k;
    if(j < N && a[j] < a[j + 1]) ++j;
    if(a[k] >= a[j]) break;
    swap(a[k], a[j]);
    k = j;
  }
}
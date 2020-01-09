#ifndef MERGE_H_
#define MERGE_H_
#include <vector>
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;
/**
 * 自顶向下归并排序
 **/ 

class Merge{
  public:
  static void sort(vector<int>& );
  private:
  static int* aux;
  static void sort(vector<int>&, int lo,int ho);
  static void merge(vector<int>&, int lo,int mid, int ho);
};

void Merge::sort(vector<int>& a){
  aux = new int[a.size()]();
  sort(a, 0, a.size() - 1);
}

void Merge::sort(vector<int>& a, int lo, int ho)
{
  if(lo >= ho) return ;
  int mid = lo + (ho - lo) / 2;
  sort(a, lo, mid);
  sort(a, mid + 1, ho);
  merge(a, lo, mid, ho);
}

void Merge::merge(vector<int>& a, int lo,int mid, int ho) {
  int i = lo, j = mid + 1,
    ao = lo;
  for(int n = lo; n <= ho; ++n) {
    aux[n] = a[n];
  }
  while(ao <= ho) {
    if(i > mid) a[ao++] = aux[j++];
    else if (j > ho) a[ao++] = aux[i++];
    else if (aux[i] > aux[j]) a[ao++] = aux[j++];
    else a[ao++] = aux[i++];
  }
  //调试代码
  // for(int i = 0; i < 10; i ++) {
  //   cout << a[i] << " ";
  // }
  // cout << endl;
}

#endif //asd
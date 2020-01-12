#pragma once
#include <vector>
#include <algorithm>
using namespace std;
/**
 * 自底向上归并排序
 **/ 
class Merge2 {
  public: 
    static void sort(vector<int> &);
  private:
    static int* aux;
    static void merge(vector<int>& , int,int,int);
};

void Merge2::sort(vector<int> &a) {
  aux = new int[a.size()]();
  for(size_t sz = 1; sz < a.size(); sz += sz) 
    for(size_t i = 0; i < a.size() - sz ; i += 2 * sz) {
      merge(a, i, i + sz - 1, min(i + 2 *sz - 1, a.size() - 1));
    }
}

void Merge2::merge(vector<int>& a, int lo,int mid,int ho) {
  int i = lo
  , j = mid + 1
  , ao = lo;
  for(int k = lo; k <= ho ; ++k) 
    aux[k] = a[k];
  while(ao <= ho) {
    if(i > mid) a[ao++] = aux[j++];
    else if (j > ho) a[ao++] = aux[i++];
    else if (aux[i] > aux[j]) a[ao++] = aux[j++];
    else a[ao++] = aux[i++];
  }
}
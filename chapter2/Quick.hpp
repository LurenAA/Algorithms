#pragma once
#include <vector>
#include <algorithm>
#include  <functional>
#include "Insertion.hpp"
using namespace std;

class Quick {
  public:
    static void sort(vector<int>& a);
  private:
    static void sort(vector<int>& a, int i, int j);
    static int partition(vector<int>& a, int i, int j);
};

void Quick::sort(vector<int>& a) {
  sort(a, 0, a.size() - 1);
}

// void Quick::sort(vector<int>& a, int i, int j) {
//   /**
//    * 原版
//    **/ 
//   // if(i >= j) return ;
//   /**
//    * 改进1：小尺度选插入排序
//    **/ 
//   if(i + 10 >= j) {
//     Insertion(a.begin() + i, a.begin() + j + 1);
//     return;
//   }
//   int mid = partition(a, i ,j);
//   sort(a, i, mid - 1);
//   sort(a, mid+1, j);
// }

void Quick::sort(vector<int>& a, int i, int j) {
  if(i >= j) return ;
  int lt = i, gt = j, mid = lt + 1;
  while(gt >= mid) {
    if(a[mid] > a[lt]) swap(a[mid], a[gt--]);
    else if (a[mid] < a[lt]) swap(a[mid++], a[lt++]);
    else mid++;
  } 
  sort(a, i, lt - 1);
  sort(a, gt + 1, j);
}

int Quick::partition(vector<int>& a, int i, int j){
  int lo = i, ho = j + 1;
  /**
   * 改进2：取中位数
   **/ 
  int total = 0
    , n  = 0;
  for(int k = i; k <= j; k += 3) {
    total += a[k];
    ++n;
  }
  int tarl = total / n, 
    tar = a[tarl];
  /**
   * 原版
   **/ 
  //  int tarl = i,
  //   tar = a[tarl];
  while(lo <= ho) {
    while(a[--ho] >= tar) if(ho == i) break;
    while(a[++lo] <= tar) if(lo == j) break;
    if(lo >= ho) break;
    swap(a[lo], a[ho]);
  }
  swap(a[tarl], a[ho]);
  return ho;
}
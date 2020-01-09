#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;
/**
 * 希尔排序
 **/ 

template<typename T>
void Shell(vector<T>& v) {
  int len = v.size(), h = 1;
  while(h < len / 3) h = 3*h + 1;
  while(h) {
    //插入排序
    for (int i = 1; i < len; i+= h) {
      for(int j = i; j > 0 && v[j] < v[j - h]; j -= h)
        swap(v[j], v[j -h]);
    }
    h = h / 3;
  }
} 
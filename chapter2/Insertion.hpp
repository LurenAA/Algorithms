#ifndef __INSERT__H
#define __INSERT__H

#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 插入排序
 **/ 
template<typename iterator>
void Insertion(iterator b, iterator e) {
  int len = distance(b , e);
  for(int i = 1; i < len; ++i) {
    for(int j = i; j > 0 && *(b + j) < *(b + j - 1); --j)
      swap(*(b + j - 1), *(b + j));
  }
}

#endif
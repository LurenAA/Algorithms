#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;
/**
 * 选择排序
 **/ 
template<typename T>
void Selection(vector<T>& a)
{
  for(size_t i = 0; i < a.size(); ++i) {
    auto max_one = min_element(a.begin() + i, a.end());
    swap(*(a.begin() + i), *max_one);
  }
}


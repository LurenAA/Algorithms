#include "Common.hpp"
#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
using namespace std;

Common* Common::getInstance() {
  static Common single;
  return &single;
}

std::vector<int>
Common::getRandomVector(int length, bool isSort) const{
  static default_random_engine e;
  static uniform_int_distribution<> u(1, 100);
  e.seed(time(NULL));
  vector<int> res;
  for(int i = 0; i < length; ++i) {
    res.push_back(u(e));
  }
  if(isSort)
    sort(res.begin(), res.end());
  return res;
}
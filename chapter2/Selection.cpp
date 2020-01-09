#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void Selection(vector<T>& a)
{
  for(size_t i = 0; i < a.size(); ++i) {
    auto max_one = min_element(a.begin() + i, a.end());
    swap(*(a.begin() + i), *max_one);
  }
}

int main(int argc, char** argv) {
  Common* c = Common::getInstance();
  vector<int> vec1 = c->getRandomVector(10);
  Selection(vec1);
  c->show(vec1.begin(), vec1.end());
  return 1;
}
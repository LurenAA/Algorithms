#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
using namespace std;

template<typename iterator>
void Insertion(iterator b, iterator e) {
  int len = distance(b , e);
  for(int i = 1; i < len; ++i) {
    for(int j = i; j > 0 && *(b + j) < *(b + j - 1); --j)
      swap(*(b + j - 1), *(b + j));
  }
}

int main(int argc, char** argv) {
  Common* c = Common::getInstance();
  vector<int> vec1 = c->getRandomVector(10);
  Insertion(vec1.begin(), vec1.end());
  c->show(vec1.begin(), vec1.end());
  return 0;
}

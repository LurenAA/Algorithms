#include "Merge.hpp"
#include "Merge2.hpp"
#include "Quick.hpp"
#include "HeapSort.hpp"
int *Merge::aux = nullptr;
int *Merge2::aux = nullptr;

/**
 * 测试各种排序算法
 **/ 
int main(int argc, char** argv) {
  Common* c = Common::getInstance();
  vector<int> vec1 = c->getRandomVector(6);
  vec1.insert(vec1.begin(), 0);
  HeapSort<int>::sort(vec1);
  c->show(vec1.begin(), vec1.end());
  return 1;
}
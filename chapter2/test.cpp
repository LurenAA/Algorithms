#include "Merge.hpp"
#include "Merge2.hpp"
int *Merge::aux = nullptr;
int *Merge2::aux = nullptr;

int main(int argc, char** argv) {
  Common* c = Common::getInstance();
  vector<int> vec1 = c->getRandomVector(10);
  Merge2::sort(vec1);
  c->show(vec1.begin(), vec1.end());
  return 1;
}
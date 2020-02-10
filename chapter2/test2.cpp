#include "IndexMinPQ.hpp"

/**
 * 测试IndexMinPQ
 **/ 

int main() 
{
  IndexMinPQ<int> pq(7);
  vector<int> v = Common::getInstance()->getRandomVector(7);
  for(size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
    pq.insert(i + 1, v[i]);
  }
  cout << endl;
  pq.show();
  for(size_t i = 0; i < v.size(); ++i) {
    cout << pq.delMin() << " ";
    // pq.show();
  }
  cout << endl;
}
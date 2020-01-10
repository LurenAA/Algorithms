#include <vector>
#include <algorithm>
#include  <functional>
#include <iostream>
#include "Common.hpp"
#include <limits>
using namespace std;

/**
 * 索引最小优先队列
 **/ 
template<typename T>
class IndexMinPQ {
  public:
    IndexMinPQ(int max);
    void show() const;
    int size() const {return N;}
    int capacity() const {return _capacity;}
    void insert(int k, T item);
    void change(int k, T item);
    bool contain(int k) const {return qp[k] != -1;};
    int delMin();
  private:
    void sink(int i);
    void swim(int i);
    T* element; //元素
    int* pq; //二叉堆
    int *qp; //index
    int N;
    int _capacity;
};

template<typename T>
IndexMinPQ<T>::IndexMinPQ(int max) :
  element(new T[max + 1]), pq(new int[max + 1])
  , qp(new int[max + 1]), N(0), _capacity(max) 
{
  for(int i = 0; i < max + 1; ++i)
    qp[i] = -1;
}

template<typename T>
void IndexMinPQ<T>::sink(int n){
  while(n < N) {
    int m = n * 2;
    if(element[pq[m]] > element[pq[m + 1]]) ++m;
    if(element[pq[m]] < element[pq[n]]) break;
    swap(pq[m], pq[n]);
    swap(qp[pq[m]], qp[pq[n]]);
    n = m;
  }
}

template<typename T>
void IndexMinPQ<T>::swim(int n) {
  while(n > 1) {
    int m = n / 2;
    if(element[pq[m]] <= element[pq[n]]) break;
    swap(pq[m], pq[n]);
    swap(qp[pq[m]], qp[pq[n]]);
    n = m; 
  }
}


template<typename T>
void IndexMinPQ<T>::insert(int k, T item) {
  // cout << "insert " << k << " " << item << endl;
  if(capacity() == size()){
    cout << "out of size" << endl;
    return ;
  }
  pq[++N] = k;
  element[k] = item;
  qp[k] = N;
  swim(N);
  // show();
}

template<typename T>
void IndexMinPQ<T>::show() const
{
  cout << "pq: ";
  for(int i = 1; i <= capacity(); ++i) 
    cout << pq[i] << " ";
  cout << endl;
  cout << "qp: ";
  for(int i = 1; i <= capacity(); ++i) 
    cout << qp[i] << " ";
  cout << endl;
  cout << "element: ";
  for(int i = 1; i <= capacity(); ++i) 
    cout << element[i] << " ";
  cout << endl;
}

template<typename T>
void IndexMinPQ<T>::change(int k, T item) {
  if(!contain(k)) {
    cout << "change not contain" << endl;
    return ;   
  }
  T old_one = element[k];
  element[k] = item;
  if(item > old_one) 
    sink(qp[k]);
  else if(item < old_one)
    swim(qp[k]);
}

template<typename T>
int IndexMinPQ<T>::delMin() {
  int max = pq[1];
  swap(pq[1], pq[N]);
  swap(qp[pq[1]], qp[pq[N]]);
  --N;
  show();
  sink(1);
  show();
  qp[max] = -1;
  element[max] = -1;
  pq[N + 1] = -1;
  return max;
}

int main(int argc, char** argv) {
  IndexMinPQ<int> pq(6);
  vector<int> v = Common::getInstance()->getRandomVector(6);
  for(size_t i = 0; i < v.size(); ++i) {
    pq.insert(i + 1, v[i]);
  }
  pq.show();
  pq.delMin();
  pq.show();
  return 0;
}
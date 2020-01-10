#include <vector>
#include <algorithm>
#include  <functional>
#include <iostream>
#include "Common.hpp"
#include <limits>
using namespace std;

/**
 * 优先队列
 * 二叉堆实现
 **/ 
template<typename T>
class MaxPQ {
  private:
    pair<int, T>* arr;
    int N;
    int _capacity;
    void swim(int i);
    void sink(int i);
  public:
    void show() const ;
    explicit MaxPQ(int max);
    ~MaxPQ() {delete [] arr;}
    void insert(pair<int, T>);
    pair<int, T> delMax();
    bool isEmpty() const { return N == 0;}
    int size() const {return N;} 
    int capacity() const {return _capacity;}
};

template<typename T>
MaxPQ<T>::MaxPQ(int max) :
  arr(new pair<int, T>[max + 1]()), N(0), _capacity(max + 1)
{
  arr[0] = pair<int, T>(INT8_MIN, T());
}

template<typename T>
void MaxPQ<T>::insert(pair<int, T> x) {
  if(capacity() == size()) 
    return ;
  arr[++N] = x;
  swim(N);
}

template<typename T>
pair<int, T> MaxPQ<T>::delMax() {
  pair<int ,T> res;
  if(isEmpty())
    return res;
  swap(arr[N--], arr[1]);
  res =  arr[N + 1];
  arr[N + 1] = pair<int ,T>();
  sink(1);
  return res;
}

template<typename T>
void MaxPQ<T>::show() const {
  cout << "N: " << size() << " arr: ";
  for(int i = 1; i <= N; ++i)
    cout << arr[i].first << " ";
  cout << endl;
}

template<typename T>
void MaxPQ<T>::swim(int i) {
  while(i > 1) {
    if(arr[i].first > arr[i / 2].first) swap(arr[i], arr[i / 2]);
    i /= 2;
  }
}

template<typename T>
void MaxPQ<T>::sink(int i) {
  int k;
  while(i < N) {
    k = 2 * i;
    if(arr[k].first < arr[k + 1].first) ++k;
    if(arr[k].first <= arr[i].first) break;
    swap(arr[k], arr[i]);
    i = k;
  }
}

int main(int argc, char** argv) {
  MaxPQ<int> pq(20);
  vector<int> v = Common::getInstance()->getRandomVector(12);
  for(auto x: v) {
    pq.insert({x, x});
    // pq.show();
  }
  while(pq.size()) {
    pq.show();
    pq.delMax();
  }
}
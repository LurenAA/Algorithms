#include <vector>
#include <algorithm>
#include  <functional>
#include <iostream>
#include "Common.hpp"
using namespace std;

/**
 * 优先队列
 * 2.4.3 无序数组实现
 **/ 
template<typename T>
class UnOrderArrayMaxPQ {
  private:
    pair<int, T>* arr;
    int N;
    int _capacity;
  public:
    void show() const ;
    explicit UnOrderArrayMaxPQ(int max);
    ~UnOrderArrayMaxPQ() {delete [] arr;}
    explicit UnOrderArrayMaxPQ(std::initializer_list<pair<int, T>>);
    void insert(pair<int, T>);
    pair<int, T> delMax();
    bool isEmpty() const { return N == 0;}
    int size() const {return N;} 
    int capacity() const {return _capacity;}
};

template<typename T>
UnOrderArrayMaxPQ<T>::UnOrderArrayMaxPQ(int max) :
  arr(new pair<int, T>[max]()), N(0), _capacity(max)
{
}

template<typename T>
UnOrderArrayMaxPQ<T>::UnOrderArrayMaxPQ(std::initializer_list<pair<int, T>> l) 
  : arr(new pair<int, T>[l.size()]()), N(l.size()), _capacity(l.size())
{
  copy(l.begin(), l.end(), arr);
}

template<typename T>
void UnOrderArrayMaxPQ<T>::insert(pair<int, T> x) {
  if(capacity() == size()) 
    return ;
  arr[N++] = x;
}

template<typename T>
pair<int, T> UnOrderArrayMaxPQ<T>::delMax() {
  if(isEmpty())
    return pair<int, T>();
  int max_one = 0;
  for(int i = 0; i < N; ++i) 
    if(arr[max_one].first < arr[i].first) {
      max_one = i;
    }
  swap(arr[max_one], arr[--N]);
  pair<int,T> res = arr[N];
  arr[N] = pair<int,T>();
  return res;
}

template<typename T>
void UnOrderArrayMaxPQ<T>::show() const {
  cout << "N: " << size() << " arr: ";
  for(int i = 0; i < N; ++i)
    cout << arr[i].first << " ";
  cout << endl;
}

int main(int argc, char** argv) {
  UnOrderArrayMaxPQ<int> pq(20);
  vector<int> v = Common::getInstance()->getRandomVector(12);
  for(auto x: v) {
    pq.insert({x, x});
  }
  while(pq.size()) {
    pq.show();
    pq.delMax();
  }
}
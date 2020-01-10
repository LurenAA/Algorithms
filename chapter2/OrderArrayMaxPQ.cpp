#include <vector>
#include <algorithm>
#include  <functional>
#include <iostream>
#include "Common.hpp"
using namespace std;

/**
 * 优先队列
 * 2.4.3 有序数组实现
 * 这里pair的int值代表的是T这个值的权重
 **/ 
template<typename T>
class OrderArrayMaxPQ {
  private:
    pair<int, T>* arr;
    int N;
    int _capacity;
  public:
    void show() const ;
    explicit OrderArrayMaxPQ(int max);
    ~OrderArrayMaxPQ() {delete [] arr;}
    // explicit OrderArrayMaxPQ(std::initializer_list<pair<int, T>>);
    void insert(pair<int, T>);
    pair<int, T> delMax();
    bool isEmpty() const { return N == 0;}
    int size() const {return N;} 
    int capacity() const {return _capacity;}
};

template<typename T>
OrderArrayMaxPQ<T>::OrderArrayMaxPQ(int max) :
  arr(new pair<int, T>[max]()), N(0), _capacity(max)
{
}

// template<typename T>
// OrderArrayMaxPQ<T>::OrderArrayMaxPQ(std::initializer_list<pair<int, T>> l) 
//   : arr(new pair<int, T>[l.size()]()), N(l.size()), _capacity(l.size())
// {
//   copy(l.begin(), l.end(), arr);
// }

template<typename T>
void OrderArrayMaxPQ<T>::insert(pair<int, T> x) {
  if(capacity() == size()) 
    return ;
  arr[N++] = x;
  for(int i = N - 1; i > 0 && arr[i] < arr[i - 1]; --i)
    swap(arr[i], arr[i - 1]); 
}

template<typename T>
pair<int, T> OrderArrayMaxPQ<T>::delMax() {
  pair<int ,T> res;
  if(isEmpty())
    return res;
  res = arr[N - 1];
  arr[--N] = pair<int , T>();
  return res;
}

template<typename T>
void OrderArrayMaxPQ<T>::show() const {
  cout << "N: " << size() << " arr: ";
  for(int i = 0; i < N; ++i)
    cout << arr[i].first << " ";
  cout << endl;
}

int main(int argc, char** argv) {
  OrderArrayMaxPQ<int> pq(20);
  vector<int> v = Common::getInstance()->getRandomVector(12);
  for(auto x: v) {
    pq.insert({x, x});
  }
  while(pq.size()) {
    pq.show();
    pq.delMax();
  }
}
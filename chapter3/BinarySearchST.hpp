#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>
using namespace std;

/**
 * 数组实现
 **/
template<typename S, typename T>
class BinarySearchST {
  public:
    BinarySearchST(int size = 10000);
    ~BinarySearchST();
    void put(const S&, const T&);
    const T get(const S&);
    bool contain(const S& key) const;
    const vector<S> keys() const;
    void show() const;
  private:
    const int rank(const S&) const;
    S* _keys;
    T* vals;
    int _capacity;
    int n;
};

template<typename S, typename T>
BinarySearchST<S,T>::BinarySearchST(int size) 
  : _keys(new S[size]),
  vals(new T[size]),
  _capacity(size),
  n(0)
{
}

template<typename S, typename T>
BinarySearchST<S,T>::~BinarySearchST(){
  delete []_keys;
  delete []vals;
}

template<typename S, typename T>
const int BinarySearchST<S,T>::rank(const S& key) const{
  if(n == 0) 
    return 0;
  int lo = 0,
    hi = n - 1,
    mid;
  while(lo < hi) {
    mid = lo + (hi - lo) / 2;
    if(_keys[mid] < key) 
      lo = mid + 1;
    else 
      hi = mid;
  }
  if(_keys[lo] < key)
    return lo + 1;
  else 
    return lo;
}

template<typename S, typename T>
void BinarySearchST<S,T>::put(const S& key, const T& val)
{
  int pos = rank(key);
  if(pos < n && _keys[pos] == key) { 
    vals[pos] = val;
    return ;
  } 
  //暂时不考虑超出容量的情况
  for(int i = n; i > pos; --i) {
    _keys[i] = _keys[i - 1];
    vals[i] = vals[i - 1];
  }
  _keys[pos] = key;
  vals[pos] = val;
  ++n;
}

template<typename S, typename T>
const T BinarySearchST<S,T>::get(const S& key) {
  int pos = rank(key);
  if(pos < n && _keys[pos] == key) { 
    return vals[pos];
  }
  return T();
}

template<typename S, typename T>
bool BinarySearchST<S,T>::contain(const S& key) const {
  if(!n) 
    return false;
  int pos = rank(key);
  return _keys[pos] == key;
}

template<typename S, typename T>
const vector<S> BinarySearchST<S,T>::keys() const {
  return vector<S>(_keys, _keys + n);
}

template<typename S, typename T>
void BinarySearchST<S,T>::show() const {
  for(int i = 0; i < n; ++i) {
    cout << _keys[i] << " " << vals[i] << endl;
  }
}
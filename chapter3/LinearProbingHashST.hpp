#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

/**
 * 线性探测法的散列表
 **/ 

template<typename Value>
class LinearProbingHashST{
  public:
    LinearProbingHashST(int M);
    int size() const {return N;}
    void put(int key, Value val);
    Value get(int key);
    void delet(int key);
    bool contain(int key) const;
  private:
    int M; //长度
    int N; //键值对数量
    int* keys;
    Value* vals;

    void resize(int sz);
    int hash(int key) const;
};

template<typename Value>
int LinearProbingHashST<Value>::hash(int key) const
{
  return (key & 0x7fffffff) % M;
}

template<typename Value>
LinearProbingHashST<Value>::LinearProbingHashST(int M)
 :M(M), N(0)
{
  keys = new int [M]();
  vals = new Value [M]();
  for(int i  = 0; i < M; ++i)
    keys[i] = -1;
}

template<typename Value>
void 
LinearProbingHashST<Value>::put(int key, Value val)
{
  if(N > M / 2) {
    resize(2 * M);
  }
  int i;
  for(i = hash(key); keys[i] != -1; i = (i + 1) % M) {
    if(keys[i] == key) 
    {
      vals[i] = val;
      return ;
    }
  }
  keys[i] = key;
  vals[i] = val;
  N++;
}

template<typename Value>
void 
LinearProbingHashST<Value>::resize(int sz)
{
  int * keys1 = keys;
  Value* vals1 = vals;
  int M1 = M;
  keys = new int [sz]();
  vals = new Value [sz] ();
  for(int i = 0; i < sz; ++i) {
    keys[i] = -1;
  }
  N = 0;
  M = sz;
  for(int i = 0; i < M1; ++i) {
    if(keys1[i] != -1) {
      put(keys1[i], vals1[i]);
    }
  }
  delete [] keys1;
  delete [] vals1;
}

template<typename Value>
Value 
LinearProbingHashST<Value>::get(int key)
{
  int i = hash(key);
  for(; keys[i] != -1; i = (i + 1) % M) {
    if(keys[i] == key) {
      return vals[i];
    }
  }
  return Value();
}

template<typename Value>
void 
LinearProbingHashST<Value>::delet(int key)
{
  if(!contain(key))
    return ;
  int i = hash(key);
  for(; keys[i] != -1; i = (i + 1) % M)
    if(keys[i] == key)
      break;
  keys[i] = -1;
  vals[i] = Value();
  i = (i + 1) % M;
  int k;
  Value v;
  while(keys[i] != -1) {
    k = keys[i];
    v = vals[i];
    N--;
    keys[i] = -1;
    vals[i] = Value();
    put(k, v);
    i = (i + 1) % M; 
  }
  N--;
  if(N > 0 && N == M/8)
    resize(M / 2);
}

template<typename Value>
bool 
LinearProbingHashST<Value>::contain(int key) const
{
  int i = hash(key);
  for(; keys[i] != -1; i = (i + 1) % M) {
    if(keys[i] == key)
      return true;
  }
  return false;
}
#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include "BinarySearchST.hpp"
using namespace std;

/**
 * 拉链法散列表
 * 因为没有Java的hasCode方法，
 * 所以这里的代码直接使用int类型
 **/ 

template<typename Value>
class SeparateChainingHashST
{
  public:
    SeparateChainingHashST(int M);
    ~SeparateChainingHashST();
    Value get(int key);
    void put(int key, Value val);
    int size() const {return this->N;}
  private:
    int N; //键值对总数
    int M; //散列表的大小
    BinarySearchST<int, Value> *st;

    int hash(int key) const;
};

template<typename Value>
SeparateChainingHashST<Value>::SeparateChainingHashST(int M)
  : N(0), M(M)
{
  st = new BinarySearchST<int, Value>[M]();
}

template<typename Value>
SeparateChainingHashST<Value>::~SeparateChainingHashST()
{
  delete [] st;
}

template<typename Value>
int SeparateChainingHashST<Value>::hash(int key) const
{
  return (key & 0x7fffffff) % M;
}

template<typename Value>
Value SeparateChainingHashST<Value>::get(int key)
{
  return st[hash(key)].get(key);
}

template<typename Value>
void SeparateChainingHashST<Value>::put(int key, Value val)
{
  st[hash(key)].put(key, val);
  N++;
}
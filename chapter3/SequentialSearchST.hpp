#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

/**
 * 链表实现
 **/

template<typename S, typename T>
class SequentialSearchST {
  public:
    struct Node {
      Node(const S& key, const T& val, shared_ptr<Node> next = nullptr)
      :key(key), val(val), next(next) {}
      
      const S key;
      T val;
      shared_ptr<Node> next;
    };
    
    void show() const; 
    void put(S key, T val);
    const T get(const S& key) const;
    bool contain(const S& key) const;
    const vector<S> keys() const;
  private:
    shared_ptr<Node> head;
};

template<typename S, typename T>
const T SequentialSearchST<S,T>::get(const S& key) const {
  shared_ptr<Node> sk(head);
  while(sk && sk->key != key) {
    sk = sk->next;
  }
  if(!sk) 
    return T();
  return sk->val;
}

template<typename S, typename T>
void SequentialSearchST<S,T>::put(S key, T val) {
  shared_ptr<Node> sk(head);
  while(sk && sk->key != key) {
    sk = sk->next;
  }
  if(sk) 
    sk->val = val;
  else {
    shared_ptr<Node> newOne(make_shared<Node>(key, val, head));
    head = newOne;
  }
}

template<typename S, typename T>
void SequentialSearchST<S,T>::show() const {  
  shared_ptr<Node> sk(head);
  while(sk) {
    cout << sk->key << " " << sk->val << endl;
    sk = sk->next;
  }
}

template<typename S, typename T>
bool SequentialSearchST<S,T>::contain(const S& key) const {
  shared_ptr<Node> sk(head);
  while(sk && sk->key != key) {
    sk = sk->next;
  }
  if(!sk) 
    return false;
  return true;
}

template<typename S, typename T>
const vector<S> SequentialSearchST<S,T>::keys() const {
  vector<S> res;
  shared_ptr<Node> sk(head);
  while(sk) {
    res.push_back(sk->key);
    sk = sk->next;
  }
  return res;
}
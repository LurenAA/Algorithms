/*
 * @Author: xiao gongbai 
 * @Date: 2020-01-14 17:31:12 
 * @Last Modified by: xiao gongbai
 * @Last Modified time: 2020-01-15 03:03:40
 */
#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>
using namespace std;

/**
 * 二叉查找树的实现
 **/
template<typename S, typename T>
class BST{
  public:
    struct Node {
      const S key;
      T val;
      shared_ptr<Node> left, right;
      int N;
      explicit Node(const S&key, const T& val, int N) :
        key(key), val(val), left(), right(), N(N) {}
      int compareTo(const S&) const;
      static int Nsize(shared_ptr<Node> x);  
    };
    
    S min() const;
    S max() const;
    bool contain(const S&) const;
    T get(const S&) const;
    #ifdef DEBUG
    shared_ptr<Node> get(const S&, int) const; //测试用
    #endif
    void put(const S& key, const T& val);
    int size() const {return root ? root->N : 0;}
    vector<S> keys(const S& min , const S& max) const;
    vector<S> keys() const;
    S floor(const S& key) const;
    S ceiling(const S&key) const;
    // const S select(int x) const;
    // const int rank(const T&) const;
    // void deleteMin();
    // void delet(const T& key);
  private:
    // shared_ptr<Node> delet(shared_ptr<Node> nd, const T& key);
    // shared_ptr<Node> deleteMin(shared_ptr<Node>);
    // const int _rank(shared_ptr<Node> nd, const T& key) const;
    // shared_ptr<Node> _select(shared_ptr<Node> nd, int x) const;
    shared_ptr<Node> floor(shared_ptr<Node> x, const S& key) const;
    shared_ptr<Node> ceiling(shared_ptr<Node> x, const S&key) const;
    shared_ptr<Node> min(shared_ptr<Node> x) const;
    shared_ptr<Node> max(shared_ptr<Node> x) const;
    shared_ptr<Node> put(shared_ptr<Node> x, const S& key, const T& val);
    shared_ptr<Node> get(shared_ptr<Node> x,const S&) const;
    void keys(vector<S>&, shared_ptr<Node> x,const S& min, const S& max) const;
    shared_ptr<Node> root;
};

template<typename S, typename T>
void BST<S,T>::put(const S& key, const T& val)
{
  root = put(root, key, val);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::put(shared_ptr<Node> h, const S& key, const T& val)
{
  if(!h)
    return make_shared<Node>(key, val, 1);
  int cmp = h->compareTo(key);
  if(cmp > 0) {
    h->left = put(h->left, key, val);
  } else if (cmp < 0) {
    h->right = put(h->right, key, val);
  } else {
    h->val = val;
  }
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return h;
}

template<typename S, typename T>
int 
/**
 * BST<S,T>::Node::compareTo 
 * 
 * @param  {S} key : 
 * @return {int} >key 1，
 *               <key -1
 *               =key 0
 */
BST<S,T>::Node::compareTo(const S& key) const 
{
  if(this->key > key)
    return 1;
  else if (this->key < key)
    return -1;
  return 0;
}

template<typename S, typename T>
int 
BST<S,T>::Node::Nsize(shared_ptr<Node> h) 
{
  if(!h)
    return 0;
  return h->N;
}

template<typename S, typename T>
T BST<S,T>::get(const S& key) const
{
  auto h = get(root, key);
  if(!h)
    return T();
  return h->val;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node>
BST<S,T>::get(shared_ptr<Node> h,const S& key) const
{
  if(!h)
    return nullptr;
  int cmp = h->compareTo(key);
  if(cmp > 0) {
    return get(h->left, key);
  } else if (cmp < 0) {
    return get(h->right, key);
  } else {
    return h;
  }
}

template<typename S, typename T>
vector<S> BST<S,T>::keys(const S& min, const S& max) const
{
  vector<S> vec;
  keys(vec, root, min, max);
  return vec;
}

template<typename S, typename T>
void 
BST<S,T>::keys(vector<S>& vec, shared_ptr<Node> h, const S& min, const S& max) const
{
  if(!h)  
    return ;
  int cmp1 = h->compareTo(min),
    cmp2 = h->compareTo(max);
  if(cmp1 >= 0 && cmp2 <= 0) 
    vec.push_back(h->key);
  if(cmp1 >= 0)
    keys(vec, h->left, min, max);
  if(cmp2 <= 0)
    keys(vec, h->right, min, max);  
}

template<typename S, typename T>
S BST<S,T>::min() const
{
  if(!root)
    return S();
  auto h = min(root);
  return h->key;
}

template<typename S, typename T>
S BST<S,T>::max() const 
{
  if(!root)
    return S();
  auto h = max(root);
  return h->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::min(shared_ptr<Node> h) const
{
  if(!h->left)
    return h;
  return min(h->left);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::max(shared_ptr<Node> h) const
{
  if(!h->right)
    return h;
  return max(h->right);
}

template<typename S, typename T>
vector<S> BST<S,T>::keys() const
{
  return keys(min(), max());
}

#ifdef DEBUG
template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::get(const S& key, int) const
{
  auto h = get(root, key);
  return h;
}
#endif

template<typename S, typename T>
bool BST<S,T>::contain(const S& key) const
{
  return get(root, key) != nullptr;
}

template<typename S, typename T>
S BST<S,T>::floor(const S& key) const
{
  if(!root)
    return S();
  auto h = floor(root, key);
  if(!h)
    return S();
  return h->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::floor(shared_ptr<Node> h, const S& key) const
{
  if(!h)
    return nullptr;
  int cmp = h->compareTo(key);
  shared_ptr<Node> n;
  if(cmp < 0) {
    n = floor(h->right, key);
    return n ? n : h;
  } else if (cmp > 0) {
    return floor(h->left, key);
  } else {
    return h;
  }
}

template<typename S, typename T>
S BST<S,T>::ceiling(const S&key) const
{
  if(!root)
    return S();
  auto h = ceiling(root, key);
  if(!h)
    return S();
  return h->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::ceiling(shared_ptr<Node> h, const S&key) const
{
  // if(!h)
  //   return nullptr;
  // int cmp = h->compareTo(key);
  // if(cmp < 0) {
  //   auto n = ceiling(h->right, key);
  //   return n ? n : h;
  // } else if(cmp > 0) {
  //   return ceiling(h->left, key);
  // } else {
  //   return h;
  // }
}
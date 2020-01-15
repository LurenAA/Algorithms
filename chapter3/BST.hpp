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
    const S select(int x) const;
    int rank(const T&) const;
    void deleteMin();
    void deleteMax();
    void delet(const T& key);
  private:
    shared_ptr<Node> delet(shared_ptr<Node> nd, const T& key);
    shared_ptr<Node> deleteMax(shared_ptr<Node>);
    shared_ptr<Node> deleteMin(shared_ptr<Node>);
    int rank(shared_ptr<Node> h, const T& key) const;
    shared_ptr<Node> select(shared_ptr<Node> h, int x) const;
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
  if(!h)
    return nullptr;
  int cmp = h->compareTo(key);
  if(cmp < 0)
    return ceiling(h->right, key);
  else if (!cmp) 
    return h;
  auto n = ceiling(h->left, key);
  if(!n)
    return h;
  return n;
}

template<typename S, typename T>
const S BST<S,T>::select(int x) const
{
  if(x < 0 || x >= size())
    return S();
  auto h = select(root, x);
  return h->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::select(shared_ptr<Node> h, int x) const
{
  int rank = Node::Nsize(h->left);
  if(rank > x) {
    return select(h->left, x);
  } else if(rank < x) {
    return select(h->right, x - rank - 1);
  } else {
    return h;
  }
}

template<typename S, typename T>
int 
BST<S,T>::rank(shared_ptr<Node> h, const T& key) const
{
  if(!h)
    return 0;
  int cmp = h->compareTo(key);
  if(cmp > 0) 
  {
    return rank(h->left, key);
  } 
  else if (cmp < 0) 
  {
    return Node::Nsize(h->left) + rank(h->right, key) + 1;
  } 
  else
  {
    return Node::Nsize(h->left);
  } 
}

template<typename S, typename T>
int 
BST<S,T>::rank(const T& key) const
{
  return rank(root, key);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::deleteMin(shared_ptr<Node> h)
{
  if(!h->left)
    return h->right;
  h->left = deleteMin(h->left);
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return h;
}

template<typename S, typename T>
void 
BST<S,T>::deleteMin()
{
  if(!size())
    return ;
  root = deleteMin(root);
}

template<typename S, typename T>
void BST<S,T>::deleteMax()
{
  if(!size())
    return ;
  root = deleteMax(root);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::deleteMax(shared_ptr<Node> h)
{
  if(!h->right)
    return h->left;
  h->right = deleteMax(h->right);
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return h;
}

template<typename S, typename T>
void BST<S,T>::delet(const T& key)
{
  if(!size())
    return ;
  root = delet(root, key);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::delet(shared_ptr<Node> h, const T& key)
{
  if(!h)
    return nullptr;
  int cmp = h->compareTo(key);
  if(cmp < 0) {
    h->right = delet(h->right, key);
  } else if (cmp > 0) {
    h->left = delet(h->left, key);
  } else {
    if(!h->right) return h->left;
    if(!h->left) return h->right;
    auto min_r = min(h->right);
    h->right = deleteMin(h->right);
    min_r->left = h->left;
    min_r->right = h->right;
    h = min_r;
  }
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return h;
}

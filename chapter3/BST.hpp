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
      Node(const S&key, const T& val, int N) :
        key(key), val(val), left(), right(), N(N) {}
      int compareTo(shared_ptr<Node> node) const;
      int compareTo(const S&) const;
      static int Nsize(shared_ptr<Node> x);  
    };
    
    const S min() const;
    const S max() const;
    bool contain(const S&) const;
    const T get(const S&) const;
    void put(const S& key, const T& val);
    void show() const; //调试
    const vector<S> keys() const;
    const S floor(const S& key) const;
    const S ceiling(const S&key) const;
    const S select(int x) const;
    const int rank(const T&) const;
    void deleteMin();
    void delet(const T& key);
  private:
    shared_ptr<Node> delet(shared_ptr<Node> nd, const T& key);
    shared_ptr<Node> deleteMin(shared_ptr<Node>);
    const int _rank(shared_ptr<Node> nd, const T& key) const;
    shared_ptr<Node> _select(shared_ptr<Node> nd, int x) const;
    shared_ptr<Node> _floor(shared_ptr<Node> x, const S& key) const;
    shared_ptr<Node> _ceiling(shared_ptr<Node> x, const S&key) const;
    shared_ptr<Node> _min(shared_ptr<Node> x) const;
    shared_ptr<Node> _max(shared_ptr<Node> x) const;
    shared_ptr<Node> _put(shared_ptr<Node> x, const S& key, const T& val);
    const T _get(shared_ptr<Node> x,const S&) const;
    void _show(shared_ptr<Node> x) const;
    void _keys(vector<S>&, shared_ptr<Node> x) const;
    shared_ptr<Node> head;
};

template<typename S, typename T>
void BST<S,T>::put(const S& key, const T& val) {
  head = _put(head, key, val);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::_put(shared_ptr<Node> x, const S& key, const T& val) 
{
  if(!x) 
    return make_shared<Node>(key, val, 1);
  int cmp = x->compareTo(key);
  if(cmp > 0) x->left = _put(x->left, key, val); 
  else if(cmp < 0) x->right = _put(x->right, key, val);
  else x->val = val;
  x->N = Node::Nsize(x->left) + Node::Nsize(x->right) + 1;
  return x;
}

/**
 * > 1
 * = 0
 * < -1
 **/ 
template<typename S, typename T>
int BST<S,T>::Node::compareTo(shared_ptr<Node> node) const {
  return compareTo(node->key);
}

template<typename S, typename T>
int BST<S,T>::Node::compareTo(const S& key2) const {
  return key > key2 ? 1 : key < key2 ? -1 : 0;
}

template<typename S, typename T>
int BST<S,T>::Node::Nsize(shared_ptr<Node> x) {
  if(!x) 
    return 0;
  else 
    return x->N;
}

template<typename S, typename T>
const T BST<S,T>::get(const S& key) const {
  return _get(head, key);
}

template<typename S, typename T>
const T BST<S,T>::_get(shared_ptr<Node> x,const S& key) const {
  if(!x) 
    return T();
  int cmp = x->compareTo(key);
  if(cmp > 0) return _get(x->right, key);
  else if(cmp < 0) return _get(x->left, key);
  else return x->val;
}

template<typename S, typename T>
bool BST<S,T>::contain(const S& key) const {
  return get(key) != T();
}

template<typename S, typename T>
void BST<S,T>::show() const {
  _show(head);
}

template<typename S, typename T>
void BST<S,T>::_show(shared_ptr<Node> x) const {
  if(!x) 
    return ;
  if(x->left) 
    _show(x->left);
  cout << x->key << " " << x->val << endl;
  if(x->right)
    _show(x->right);
}

template<typename S, typename T>
const vector<S> BST<S,T>::keys() const {
  vector<S> res;
  _keys(res, head);
  return res;
}

template<typename S, typename T>
void BST<S,T>::_keys(vector<S>& res, shared_ptr<Node> x) const {
  if(!x) 
    return ;
  res.push_back(x->key);
  _keys(res,x->left);
  _keys(res, x->right);
}

template<typename S, typename T>
const S BST<S,T>::min() const {
  if(!head) 
    return S();
  return _min(head)->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::_min(shared_ptr<Node> x) const 
{
  if(!x || !x->left)
    return x;
  else
    return _min(x->left);
}

template<typename S, typename T>
const S BST<S,T>::max() const {
  if(!head) 
    return S();
  return _max(head)->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::_max(shared_ptr<Node> x) const 
{
  if(!x || !x->right)
    return x;
  else
    return _max(x->right);
}

template<typename S, typename T>
const S BST<S,T>::floor(const S& key) const {
  shared_ptr<Node> nd = _floor(head, key);
  if(!nd) return S();
  return nd->key;
}

template<typename S, typename T>
const S BST<S,T>::ceiling(const S&key) const {
  shared_ptr<Node> nd = _ceiling(head, key);
  if(!nd) return S();
  return nd->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::_floor(shared_ptr<Node> x, const S& key) const 
{
  if(!x) return x;
  int cmp = x->compareTo(key);
  if(cmp == 0) return x;
  else if (cmp > 0) return _floor(x->left, key);
  shared_ptr<Node> y = _floor(x->right, key);
  if(!y) return x;
  return y;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::_ceiling(shared_ptr<Node> x, const S&key) const 
{
  if(!x) return x;
  int cmp = x->compareTo(key);
  if(!cmp) return x;
  else if(cmp < 0) return _ceiling(x->right, key);
  shared_ptr<Node> y = _ceiling(x->left, key);
  if(!y) return x;
  return y;
}

template<typename S, typename T>
const S BST<S,T>::select(int x) const {
  if(x < 0 || x >= head->N)
    return S();
  auto nd =  _select(head, x);
  if(!nd) 
    return S();
  return nd->key;
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::_select(shared_ptr<Node> nd, int x) const 
{
  if(!nd) 
    return nd;
  int nd_rank = Node::Nsize(nd->left);
  if(nd_rank > x) 
    return _select(nd->left, x);
  else if (nd_rank < x)
    return _select(nd->right, x - nd_rank - 1);
  return nd;
}

template<typename S, typename T>
const int BST<S,T>::rank(const T& key) const {
  int rk = _rank(head, key);
  // if(select(rk) != key)
  //   return -1;
  return rk;
}

template<typename S, typename T>
const int BST<S,T>::_rank(shared_ptr<Node> nd, const T& key) const 
{
  if(!nd) return 0;
  int nd_rank = Node::Nsize(nd->left);
  if(nd->key < key) 
    return nd_rank + 1 + _rank(nd->right, key);
  else if(nd->key > key) 
    return _rank(nd->left, key);
  return nd_rank;
}

/**
 * 这个函数只能删除根节点左边的
 **/ 
template<typename S, typename T>
void BST<S,T>::deleteMin() {
  deleteMin(head);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::deleteMin(shared_ptr<Node> x) 
{
  if(!x->left)
    return x->right;
  x->left = deleteMin(x->left);
  x->N = Node::Nsize(x->left) + Node::Nsize(x->right) + 1;
  return x;
}

template<typename S, typename T>
void BST<S,T>::delet(const T& key) {
  head = delet(head, key);
}

template<typename S, typename T>
shared_ptr<typename BST<S,T>::Node> 
BST<S,T>::delet(shared_ptr<Node> nd, const T& key)
{
  if(!nd) {
    return nd;
  }
  int cmp = nd->compareTo(key);
  if(cmp < 0) 
  {
    nd->right = delet(nd->right, key);
  } else if(cmp > 0) {
    nd ->left = delet(nd->left, key);
  } else {
    if(!nd->left) return nd->right;
    if(!nd->right) return nd->left;
    auto minO = _min(nd->right);
    minO->right = deleteMin(nd->right);
    minO->left = nd->left;
    nd = minO;
  }
  nd->N = Node::Nsize(nd->left) + Node::Nsize(nd->right) + 1;
  return nd;
}
/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-21 20:48:35 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-21 22:06:17
 */
#pragma once
#include <iostream>
#include "Common.hpp"
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>
#include <cassert>
using namespace std;

/**
 * avl树
 **/ 

template<typename Key, typename Val>
class AvlTree {
  public:
    struct Node {
      Val val;
      Key key;
      int height;
      shared_ptr<Node> left, right;
      Node(Val val, Key key, int height = 1) 
        :val(val), key(key), height(height) {}
      int compareTo(Key key);
      static int Height(shared_ptr<Node> h);
      static int BalanceFactor(shared_ptr<Node> h1, shared_ptr<Node> h2);
    };
    shared_ptr<Node> rotateRight(shared_ptr<Node> h);
    shared_ptr<Node> rotateLeft(shared_ptr<Node> h);
    int getBalanceFactor(shared_ptr<Node> h) const;
    shared_ptr<Node> get(Key key);
    void put(Key key, Val val);
    bool isBalanced(shared_ptr<Node> h) const;
    bool isBalanced() const {return isBalanced(root);}
    Key min() const;
    void deleteMin();
    void delet(Key key);
  private:
    shared_ptr<Node> root;

    shared_ptr<Node> delet(shared_ptr<Node> h, Key key);
    shared_ptr<Node> min(shared_ptr<Node> h) const;
    shared_ptr<Node> deleteMin(shared_ptr<Node> h);
    shared_ptr<Node> get(shared_ptr<Node> h, Key key);
    shared_ptr<Node> put(shared_ptr<Node> h, Key key, Val val);
    shared_ptr<Node> balance(shared_ptr<Node> h);
};  

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::rotateRight(shared_ptr<Node> h)
{
  auto lh = h->left;
  assert(lh != nullptr);
  h->left = lh->right;
  lh->right = h;

  h->height = max(Node::Height(h->left), Node::Height(h->right)) + 1;
  lh->height = max(Node::Height(lh->left), Node::Height(lh->right)) + 1;
  
  return lh;
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::rotateLeft(shared_ptr<Node> h) 
{
  auto rh = h->right;
  assert(rh != nullptr);
  h->right = rh->left;
  rh->left = h;
  //这个顺序不能改变，必须从下到上
  h->height = max(Node::Height(h->left), Node::Height(h->right)) + 1;
  rh->height = max(Node::Height(rh->left), Node::Height(rh->right)) + 1;
  
  return rh;
}

template<typename Key, typename Val>
int 
AvlTree<Key, Val>::Node::Height(shared_ptr<Node> h)
{
  if(!h)
    return 0;
  return h->height;
}

template<typename Key, typename Val>
int 
AvlTree<Key, Val>::Node::BalanceFactor(shared_ptr<Node> h1, shared_ptr<Node> h2)
{
  return Height(h1) - Height(h2);
}

template<typename Key, typename Val>
void 
AvlTree<Key, Val>::put(Key key, Val val)
{
  root = put(root, key, val);
}

template<typename Key, typename Val>
int 
AvlTree<Key, Val>::Node::compareTo(Key key)
{
  if(this->key > key)
    return 1;
  else if (this->key < key) 
    return -1;
  return 0;
}

template<typename Key, typename Val>
int 
AvlTree<Key, Val>::getBalanceFactor(shared_ptr<Node> h) const
{
  if(!h)
    return 0;
  return Node::BalanceFactor(h->left, h->right);
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::put(shared_ptr<Node> h, Key key, Val val)
{
  if(!h)
    return make_shared<Node>(key, val, 1);
  int cmp = h->compareTo(key);
  if(cmp > 0) {
    h->left = put(h->left, key, val);
  } else if(cmp < 0) {
    h->right = put(h->right, key, val);
  } else {
    h->val = val;
  }
  h->height = 1 + max(Node::Height(h->left), Node::Height(h->right));
  
  return balance(h);
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::balance(shared_ptr<Node> h)
{
  int fc = getBalanceFactor(h);
  if(fc >= 2) {
    /**LL
      * 左旋转
      *        x                     y
      *       / \                   / \
      *      y  T1                T3   x
      *     / \         ==>      /    / \
      *    T3  T2               T4   T2 T1
      *   /
      *  T4
      */
     if(fc > 1 && getBalanceFactor(h->left) >= 0) {
       h = rotateRight(h);
     }
     /**LR
      * 左右旋转
      *      x                     x              T2
      *     / \                   / \            / \
      *    y  T1                T2  T1          y   x
      *   / \          ==>     /         ==>   / \   \
      *  T3  T2               y              T3  T4  T1
      *     /                / \
      *    T4               T3 T4
      */
     else if(fc > 1 && getBalanceFactor(h->left) < 0 ) {
       h->left = rotateLeft(h->left);
       h = rotateRight(h);
     }
  } else if (fc <= -2) {
    /**RR
      * 右旋转
      *        x                     y
      *       / \                   / \
      *      T1  y                 x   T3
      *         / \       ==>     / \   \
      *        T2 T3             T1 T2  T4
      *            \
      *            T4
      */
     if(fc < -1 && getBalanceFactor(h->right) <= 0) {
       h = rotateLeft(h);
     }
     /**RL
      * 右左旋转
      *        x                     x                     T2
      *       / \                   / \                   / \
      *      T1  y                 T1 T2                 x   y
      *         / \       ==>          \      ==>       /   / \
      *        T2 T3                    y              T1  T4 T3
      *         \                      / \
      *         T4                    T4 T3
      */
     else if (fc < -1 && getBalanceFactor(h->right) > 0) {
       h->right = rotateRight(h->right);
       h = rotateLeft(h);
     }
  }
  h->height = max(Node::Height(h->left), Node::Height(h->right)) + 1;
  return h;
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::get(Key key)
{
  return get(root, key);
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::get(shared_ptr<Node> h, Key key)
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

template<typename Key, typename Val>
bool 
AvlTree<Key, Val>::isBalanced(shared_ptr<Node> h ) const
{
  if(!h)
    return true;
  return abs(getBalanceFactor(h)) <= 1 && isBalanced(h->left) && isBalanced(h->right);
}

template<typename Key, typename Val>
Key AvlTree<Key, Val>::min() const
{
  return min(root)->key;
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::min(shared_ptr<Node> h) const
{
  if(!h->left) 
    return h;
  return min(h->left);
}

template<typename Key, typename Val>
void AvlTree<Key, Val>::deleteMin()
{
  if(!root) 
    return ;
  root = deleteMin(root);
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::deleteMin(shared_ptr<Node> h)
{
  if(!h->left)
    return h->right;
  h->left = deleteMin(h->left);
  return balance(h);
}

template<typename Key, typename Val>
void AvlTree<Key, Val>::delet(Key key)
{
  if(!root)
    return ;
  root = delet(root, key);
}

template<typename Key, typename Val>
shared_ptr<typename AvlTree<Key, Val>::Node> 
AvlTree<Key, Val>::delet(shared_ptr<Node> h, Key key)
{
  if(!h)
    return nullptr;
  int cmp = h->compareTo(key);
  if(cmp > 0) {
    h->left = delet(h->left, key);
  } else if(cmp < 0) {
    h->right = delet(h->right, key);
  } else {
    if(!h->left) 
      return h->right;
    else if(!h->right)
      return h->left;
    auto rm = min(h->right);
    rm->right = deleteMin(h->right);
    rm->left = h->left;
  }
  return balance(h);
}
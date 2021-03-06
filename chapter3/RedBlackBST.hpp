/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-19 10:21:20 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-21 20:56:32
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
 * 红黑树
 **/
enum class Color{
  Red ,
  Black 
};
template<typename Key, typename Val>
class RedBlackBST{
  public:
    struct Node{
      Key key;
      Val val;
      shared_ptr<Node> left,right;
      int N;
      Color color;
      Node(const Key& key, const Val& val, int N, Color color)
        :key(key), val(val), left(), right(), N(N), color(color) {}
      static int Nsize(shared_ptr<Node> x);  
      int compareTo(const Key& key) const;
    };
    void put(const Key& key, const Val& val);
    shared_ptr<Node> get(const Key& key) const;
    void deleteMin();
    void deleteMax();
    void delet(const Key&);
    Key min() const;
    Key max() const;
    vector<Key> keys(const Key& m, const Key& e) const;
    vector<Key> keys() const;

    const int size() const {return root ? root->N : 0;}
  private:
    
    shared_ptr<Node> root;

    void keys(shared_ptr<Node> h, vector<Key>& res, const Key& m, const Key& e) const;
    shared_ptr<Node> max(shared_ptr<Node> h) const;
    shared_ptr<Node> min(shared_ptr<Node>) const;
    shared_ptr<Node> get(shared_ptr<Node> h,const Key& key) const;
    shared_ptr<Node> delet(shared_ptr<Node>, const Key&);
    shared_ptr<Node> balance(shared_ptr<Node>);
    shared_ptr<Node> removeRedLeft(shared_ptr<Node>);
    shared_ptr<Node> removeRedRight(shared_ptr<Node>);
    shared_ptr<Node> deleteMax(shared_ptr<Node>);
    shared_ptr<Node> deleteMin(shared_ptr<Node>);
    shared_ptr<Node> put(shared_ptr<Node> h, const Key& key, const Val& val);
    void flipColor(shared_ptr<Node> h);
    shared_ptr<Node> rotateLeft(shared_ptr<Node> node);
    shared_ptr<Node> rotateRight(shared_ptr<Node> h);
    bool isRed(shared_ptr<Node> node)  const;  
};

template<typename Key, typename Val>
int 
RedBlackBST<Key,Val>::Node::Nsize(shared_ptr<Node> x)
{
  return x ? x->N : 0;  
}

template<typename Key, typename Val>
int 
RedBlackBST<Key,Val>::Node::compareTo(const Key& key) const
{
  if(key > this->key) {
    return -1;
  }  else if(key < this->key) {
    return 1;
  }
  return 0;
}


template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::rotateLeft(shared_ptr<Node> h)
{
  if(!h) 
    return nullptr;
  auto rh = h->right;
  if(!rh)
    return h;
  h->right = rh->left;
  rh->left = h;
  rh->N = h->N;
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  swap(h->color, rh->color);
  return rh;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::rotateRight(shared_ptr<Node> h)
{
  if(!h) {
    return nullptr;
  }
  auto lh = h->left;
  if(!lh)
    return h;
  h->left = lh->right;;
  lh->right = h;
  lh->N = h->N;
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  swap(h->color, lh->color);
  return lh;
}

template<typename Key, typename Val>
bool 
RedBlackBST<Key,Val>::isRed(shared_ptr<Node> h)  const
{
  if(!h || h->color == Color::Black)
    return false;
  return true;
}

template<typename Key, typename Val>
void 
RedBlackBST<Key,Val>::put(const Key& key, const Val& val)
{
  root = put(root, key, val);
  root->color = Color::Black;
}


template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::put(shared_ptr<Node> h, const Key& key, const Val& val)
{
  if(!h)
    return make_shared<Node>(key, val, 1, Color::Red);
  int cmp = h->compareTo(key);
  if(cmp < 0) {
    h->right = put(h->right, key, val);
  } else if (cmp > 0) {
    h->left = put(h->left, key, val);
  } else {
    h->val =val;
  }
  if(!isRed(h->left) && isRed(h->right))
    h = rotateLeft(h);
  if(isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if(isRed(h->left) && isRed(h->right)) {
    flipColor(h);
  }
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return h;
}

template<typename Key, typename Val>
void 
RedBlackBST<Key,Val>::flipColor(shared_ptr<Node> h)
{
  h->color = h->color == Color::Black ? Color::Red : Color::Black;
  h->right->color = h->right->color == Color::Black ? Color::Red : Color::Black;
  h->left->color = h->left->color == Color::Black ? Color::Red : Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::get(const Key& key) const
{
  return get(root, key);
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::get(shared_ptr<Node> h,const Key& key) const
{
  if(!h)
    return nullptr;
  int cmp = h->compareTo(key);
  if(cmp > 0) {
    return get(h->left, key);
  } else if (cmp < 0) {
    return get(h->right, key);
  } else 
    return h;
}

template<typename Key, typename Val>
void RedBlackBST<Key,Val>::deleteMin()
{
  if(!isRed(root->left) && !isRed(root->right))
    root->color = Color::Red;
  root = deleteMin(root);
  if(root)
    root->color = Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::deleteMin(shared_ptr<Node> h) 
{
  if(!h->left) 
    return h->right;
  if(!isRed(h->left) && !isRed(h->left->left))
  {
    h = removeRedLeft(h);
  }
  h->left = deleteMin(h->left);
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return balance(h);
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::removeRedLeft(shared_ptr<Node> h) 
{
  flipColor(h);
  if(isRed(h->right) && isRed(h->right->left)) 
  {
    h->right = rotateRight(h->right);
    h = rotateLeft(h);
    flipColor(h);
  }
  return h;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::balance(shared_ptr<Node> h)
{
  if(!isRed(h->left) && isRed(h->right))
    h = rotateLeft(h);
  if(isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if(isRed(h->left) && isRed(h->right)) {
    flipColor(h);
  }
  return h;
}

template<typename Key, typename Val>
Key
RedBlackBST<Key,Val>::min() const
{
  if(!root)
    return Val();
  return min(root)->key;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::min(shared_ptr<Node> h) const 
{
  if(!h->left)
    return h;
  return min(h->left);
}

template<typename Key, typename Val>
Key 
RedBlackBST<Key,Val>::max() const
{
  if(!root) 
    return Val();
  return max(root)->key;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::max(shared_ptr<Node> h) const
{
  if(!h->right)
    return h;
  return max(h->right);
}

template<typename Key, typename Val>
void RedBlackBST<Key,Val>::deleteMax()
{
  if(!isRed(root->left) && !isRed(root->right))
    root->color = Color::Red;
  root = deleteMax(root);
  if(root)
    root->color = Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::deleteMax(shared_ptr<Node> h)
{
  if(isRed(h->left))
    h = rotateRight(h);
  if(!h->right)
    return h->left;
  if(!isRed(h->right) && !isRed(h->right->left))
    h = removeRedRight(h);
  h->right = deleteMax(h->right);
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return balance(h);
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::removeRedRight(shared_ptr<Node> h)
{
  flipColor(h);
  if(isRed(h->left->left)) {
    h = rotateRight(h);
    flipColor(h);
  }
  return h;
}

template<typename Key, typename Val>
void RedBlackBST<Key,Val>::delet(const Key& key)
{
  if(!isRed(root->left) && !isRed(root->right))
    root->color = Color::Red;
  root = delet(root, key);
  if(root)
    root->color = Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key,Val>::Node> 
RedBlackBST<Key,Val>::delet(shared_ptr<Node> h, const Key& key) 
{
  int cmp = h->compareTo(key);
  if(cmp > 0) {
    if(!isRed(h->left) && !isRed(h->left->left)) 
      h = removeRedLeft(h);
    h->left = delet(h->left, key);
  } else if(cmp < 0){
    if(isRed(h->left))
      h = rotateRight(h);
    if(!isRed(h->right) && !isRed(h->right->left)) {
      h = removeRedRight(h);
    }
    h->right = delet(h->right, key);
  } else {
    if(!h->right)
      return h->left;
    h->val = get(h->right, min(h->right)->key)->val;
    h->key = min(h->right)->key;
    h->right = deleteMin(h->right);
  }
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return balance(h);
}

template<typename Key, typename Val>
vector<Key> 
RedBlackBST<Key,Val>::keys(const Key& m, const Key& e) const
{
  vector<Key> res;
  keys(root, res, m, e);
  return res;
}

template<typename Key, typename Val>
void 
RedBlackBST<Key,Val>::keys(shared_ptr<Node> h, vector<Key>& res, const Key& m, const Key& e) const
{
  if(!h)
    return ;
  int cmp1 = h->compareTo(m),
    cmp2 = h->compareTo(e);
  if(cmp1 >= 0 && cmp2 <= 0) {
    res.push_back(h->key);
  }
  if(cmp1 > 0) {
    keys(h->left, res, m, e);
  } 
  if(cmp2 < 0) {
    keys(h->right, res, m, e);
  }
}

template<typename Key, typename Val>
vector<Key> 
RedBlackBST<Key,Val>::keys() const
{
  return keys(min(), max());
}
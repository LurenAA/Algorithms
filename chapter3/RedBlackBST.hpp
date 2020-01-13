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
enum Color {
  Red = 1,
  Black = -1
};
template<typename Key, typename Val>
class RedBlackBST{
  public:
    void put(const Key& key, const Val& val);
    void deleteMin();
    void deleteMax();
    void delet(const Key&);

    const int size() const {return root ? root->N : 0;}
    void show() const; //调试
  private:
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
    shared_ptr<Node> root;

    shared_ptr<Node> delet(shared_ptr<Node>, const Key&);
    shared_ptr<Node> balance(shared_ptr<Node>);
    shared_ptr<Node> removeRedLeft(shared_ptr<Node>);
    shared_ptr<Node> removeRedRight(shared_ptr<Node>);
    bool isRed(shared_ptr<Node> )const;
    shared_ptr<Node> deleteMax(shared_ptr<Node>);
    shared_ptr<Node> deleteMin(shared_ptr<Node>);
    void show(shared_ptr<Node>) const; //调试
    shared_ptr<Node> put(shared_ptr<Node> h, const Key& key, const Val& val);
    void flipColor(shared_ptr<Node> h);
    shared_ptr<Node> rotateLeft(shared_ptr<Node> node);
    shared_ptr<Node> rotateRight(shared_ptr<Node> h);
    bool isRed(shared_ptr<Node> node) {
      return node && node->color == Color::Red;
    }
    
};

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::rotateLeft(shared_ptr<Node> h)
{
  auto nh = h->right;
  //没有右节点
  if(!nh) 
    return h;
  //有右节点
  auto nhl = nh->left;
  h->right = nhl;
  nh->left = h;
  nh->color = h->color;
  h->color = Color::Red;
  nh->N = h->N;
  h->N = 1 + Node::Nsize(h->right) + Node::Nsize(h->left);
  return nh;
}

template<typename Key, typename Val>
int RedBlackBST<Key, Val>::Node::Nsize(shared_ptr<Node> h) 
{
  return h ? h->N : 0;
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::flipColor(shared_ptr<Node> h)
{
  if(!h->left || !h->right)
    return ;
  h->color = h->color == Color::Red ? Color::Black:Color::Red;
  h->left->color = h->left->color == Color::Red ? Color::Black:Color::Red;
  h->right->color = h->right->color == Color::Red ? Color::Black:Color::Red;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::rotateRight(shared_ptr<Node> h)
{
  auto nh = h->left;
  if(!nh)
    return h;
  auto nhr = nh->right;
  h->left = nhr;
  nh->right = h;
  nh->color = h->color;
  h->color = Color::Red;
  nh->N = h->N;
  h->N = 1 + Node::Nsize(h->right) + Node::Nsize(h->left);
  return nh;
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::put(const Key& key, const Val& val)
{
  root = put(root ,key,val);
  root->color = Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::put(shared_ptr<Node> h, const Key& key, const Val& val)
{
  if(!h) 
    return make_shared<Node>(key, val, 1, Color::Red);
  int cmp = h->compareTo(key);
  if(cmp > 0) 
    h->left = put(h->left, key, val);
  else if (cmp < 0)
    h->right = put(h->right, key, val);
  else 
    h->val = val;
  //没有左节点时要左旋的原因是：红黑树定义红链接必须在左边
  if(isRed(h->right) && !isRed(h->left)) 
    h = rotateLeft(h);
  if(isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if(isRed(h->left) && isRed(h->right))
    flipColor(h);
  h->N = 1 + Node::Nsize(h->left) + Node::Nsize(h->right);
  return h;
}

template<typename Key, typename Val>
int 
RedBlackBST<Key, Val>::Node::compareTo(const Key& key1) const 
{
  if(key > key1) 
    return 1;
  else if (key < key1)
    return -1;
  return 0;
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::show() const
{
  show(root);
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::show(shared_ptr<Node> h) const
{
  if(!h)
    return ;
  if(h->left) show(h->left);
  cout << h->key << " " << h->val << " " 
  << h->N << " " << h->color << endl;
  if(h->right) show(h->right);    
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::deleteMin() {
  if(!root)
    return ;
  //如果root节点就进入moveRedLeft
  //，必须root的颜色为红，才正确
  if(!isRed(root->left) && !isRed(root->right))
    root->color = Color::Red;
  root = deleteMin(root);
  if(root) root->color = Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::deleteMin(shared_ptr<Node> h) 
{
  if(!h->left) 
    return nullptr;
  if(!isRed(h->left) && !isRed(h->left->left)) {
    h = removeRedLeft(h);
  }
  h->left = deleteMin(h->left);
  return balance(h);
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::removeRedLeft(shared_ptr<Node> h) 
{
  flipColor(h);
  if(isRed(h->right->left)) {
    h->right = rotateRight(h->right);
    h = rotateLeft(h);
    flipColor(h);
  }
  return h;
}

template<typename Key, typename Val>
bool 
RedBlackBST<Key, Val>::isRed(shared_ptr<Node> h)const 
{
  if(!h) 
    return false;
  return h->color == Color::Red;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::balance(shared_ptr<Node> h){
  if(!isRed(h->left) && isRed(h->right))
    h = rotateLeft(h);
  if(isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if(isRed(h->left) && isRed(h->right))
    flipColor(h);
  h->N = Node::Nsize(h->left) + Node::Nsize(h->right) + 1;
  return h;
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::deleteMax()
{
  if(!root)
    return ;
  if(!isRed(root->left) && !isRed(root->right)) 
    root->color = Color::Red;
  root = deleteMax(root);
  if(root) root->color = Color::Black;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::deleteMax(shared_ptr<Node> h) 
{
  if(isRed(h->left))
    h = rotateRight(h);
  if(!h->right)
    return nullptr;
  if(!isRed(h->right) && !isRed(h->right->left))
    h = removeRedRight(h);
  h->right = deleteMax(h->right);
  return balance(h);
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::removeRedRight(shared_ptr<Node> h) 
{
  flipColor(h);
  if(isRed(h->left->left)) {
    h = rotateRight(h);
  }
  return h;
}

template<typename Key, typename Val>
shared_ptr<typename RedBlackBST<Key, Val>::Node> 
RedBlackBST<Key, Val>::delet(shared_ptr<Node> h, const Key& key) 
{
  if(h->compareTo(key) > 0){
     
  } 
  else {
    
  }
  return balance(h);
}

template<typename Key, typename Val>
void RedBlackBST<Key, Val>::delet(const Key& key) 
{
  if(!root)
    return ;
  if(!isRed(root->left) && !isRed(root->right)) 
    root->color = Color::Red;
  root = delet(root);
  if(root) root->color = Color::Black;
}
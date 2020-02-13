/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-13 21:41:50 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-13 23:34:01
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
#include <new>
using namespace std;
/**
 * trie
 **/ 
enum const_value{
  R = 256
};

template<typename Value>
class TrieST
{
public:
  struct Node {
    Value val;
    vector<shared_ptr<Node>> next;
    Node(Value val = Value()) :
      val(val), next(R) {}
  };
private:
  /* data */
  shared_ptr<Node> root;

  shared_ptr<Node> get(shared_ptr<Node> x, string key, int d) const;
  shared_ptr<Node> put(shared_ptr<Node> x, string key, Value val, int d);
  void collect(shared_ptr<Node> x, string pre, queue<string>& q) const;
  void collect(shared_ptr<Node> x, string pat, string pre, queue<string>& q) const;
  int search(shared_ptr<Node> x, string s, int d, int len) const;
  shared_ptr<Node> delet(shared_ptr<Node> x, string s, int d);
public:
  TrieST(/* args */);
  ~TrieST();

  string longestPrefixOf(string s) const;
  Value get(string key) const;
  void put(string key, Value val);  
  queue<string> keys() const;
  queue<string> keysWithPrefix(string pre) const;
  queue<string> keysThatMatch(string pat) const;
  void delet(string s);
};

template<typename Value>
shared_ptr<typename TrieST<Value>::Node> 
TrieST<Value>::delet(shared_ptr<Node> x, string s, int d){
  if(!x) return nullptr;
  if(x->val != Value())
    x->val = Value();
  else {
    unsigned next = static_cast<unsigned>(s.at(d));
    x->next[next] = delet(x->next[next], s, d + 1);
  } 
  if(x->val != Value())
    return x;
  for(int c = 0;  c < R; ++ c)
    if(x->next[c]) return x;
  return nullptr;
}

template<typename Value>
void TrieST<Value>::delet(string s){
  root = delet(root , s, 0);
}

template<typename Value>
int TrieST<Value>::search(shared_ptr<Node> x, string s, int d, int len) const
{
  if(!x) return len;
  if(x->val != Value()) len = d;
  if(s.size() == static_cast<unsigned>(len)) return len;
  unsigned next = static_cast<unsigned>(s.at(d));
  return search(x->next[next], s, d + 1, len);
}

template<typename Value>
string TrieST<Value>::longestPrefixOf(string s) const
{

  int pos = search(root, s, 0, 0);
  return s.substr(0, pos);
}

template<typename Value>
queue<string> TrieST<Value>::keysThatMatch(string pat) const
{
  queue<string > q;
  collect(root,  pat,"", q);
  return q;
}

template<typename Value>
void TrieST<Value>::collect(shared_ptr<Node> x, string pat, string pre, queue<string>& q) const
{
  if(!x) return ;
  if(pre.size() == pat.size() && x->val != Value())
    q.push(pre);
  if(pre.size() == pat.size())
    return ;
  
  for(unsigned c = 0; c < R; ++c)
    if(pat.at(pre.size()) == '.' || pat.at(pre.size()) == static_cast<char>(c))
      collect(x->next[c], pat, pre + static_cast<char>(c), q);
}

template<typename Value>
void TrieST<Value>::collect(shared_ptr<Node> x, string pre, queue<string>& q) const
{
  if(!x) return ;
  if(x->val != Value())
    q.push(pre);
  for(unsigned c = 0; c < R; ++c)
    collect(x->next[c], pre + static_cast<char>(c), q);
}

template<typename Value>
queue<string> TrieST<Value>::keys() const
{
  return keysWithPrefix("");
}

template<typename Value>
queue<string> 
TrieST<Value>::keysWithPrefix(string pre) const
{
  queue<string > q;
  collect(get(root, pre, 0), pre, q);
  return q;
}

template<typename Value>
void TrieST<Value>::put(string key, Value val)
{
  root = put(root, key, val, 0);
}

template<typename Value>
shared_ptr<typename TrieST<Value>::Node> 
TrieST<Value>::put(shared_ptr<Node> x, string key, Value val, int d)
{
  if(!x) x = make_shared<Node>();
  if(d == static_cast<int>(key.size()) ){
    x->val = val;
    return x;
  }
  int pos = static_cast<int>(key.at(d));
  x->next[pos] = put(x->next[pos], key, val, 1+d);
  return x;
}

template<typename Value>
shared_ptr<typename TrieST<Value>::Node> 
TrieST<Value>::get(shared_ptr<Node> x, string key, int d) const
{
  if(!x)
    return nullptr;
  if(d == static_cast<int>(key.size()))
    return x;
  int pos = static_cast<int>(key.at(d));
  return get(x->next[pos], key, 1+d);
}

template<typename Value>
Value TrieST<Value>::get(string key) const
{
  auto x = get(root, key, 0);
  if(!x) return Value();
  return  x->val;
}

template<typename Value>
TrieST<Value>::TrieST(/* args */)
  :root(new Node())
{
}

template<typename Value>
TrieST<Value>::~TrieST()
{
}

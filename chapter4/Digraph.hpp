/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-28 18:29:27 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-28 19:38:58
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
using namespace std;
/**
 * 有向图
 **/ 
class Digraph
{
  public:
    Digraph(int n);
    Digraph(string s);
    ~Digraph() { delete [] adjs;}
    void addEdge(int v, int w);
    int V() const {return v;}
    int E() const {return e;}
    Digraph reverse();
    const list<int>& adj(int v) {return adjs[v];}
  private:
    int v;
    int e;
    list<int>* adjs;
};

Digraph::Digraph(string s)
  : v(0), e(0), adjs(nullptr)
{
  ifstream istrm(s, ios::binary);
  if(!istrm.is_open()) {
    abort();
  }
  int a, b; 
  istrm >> a;
  v = a;
  istrm >> b;
  adjs = new list<int> [v]();
  while(istrm >> a >> b) {
    addEdge(a, b);
  }
  istrm.close();
}

Digraph::Digraph(int n)
  :v(n), e(0), adjs(new list<int> [n])
{
}

void Digraph::addEdge(int v, int w)
{
  adjs[v].push_back(w);
  ++e;
}

Digraph Digraph::reverse()
{
  Digraph d(v);
  for(int i = 0; i < v; ++i)
    for(auto w : adj(i))
    {
      d.addEdge(w, i);
    }
  return d;
}
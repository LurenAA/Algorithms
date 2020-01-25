/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-25 13:54:42 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-25 19:00:07
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;
/**
 * 图
 **/ 

class Graph{
public:
  Graph(int v);
  Graph(string s);
  int V() const {return v;}
  int E() const {return e;}
  list<int> adj(int i) const;
  void addEdge(int v, int w);

  ~Graph() {delete [] adjs;}
private:
  int v; //vertex
  int e; //edge
  list<int> *adjs;
};

Graph::Graph(int v) 
  :v(v), e(0)
  {
    adjs =new list<int> [v];
  }

list<int> 
Graph::adj(int i) const
{
  return adjs[i];
}

void Graph::addEdge(int v, int w)
{
  adjs[v].push_back(w);
  adjs[w].push_back(v);
  e++;
}

Graph::Graph(string s)
{
  ifstream istrm(s, ios::binary);
  if(!istrm.is_open()) {
    abort();
  }
  // istream_iterator<int> inter(istrm), enditer;
  int a, b; 
  istrm >> a;
  v = a;
  istrm >> a;
  // e = a;
  e = 0;
  adjs =new list<int> [v];
  while(istrm >> a >> b) {
    addEdge(a, b);
  }
}
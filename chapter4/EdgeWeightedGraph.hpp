/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-01 20:51:28 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-04 23:10:55
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include "Edge.hpp"
using namespace std;
/**
 * 加权无向图
 **/ 
class EdgeWeightedGraph
{
public:
  EdgeWeightedGraph(int V);
  EdgeWeightedGraph(string s);
  int V() const {return _V;}
  int E() const {return _E;}
  const list<Edge<int> >& adj(int v) const {return adjs[v];};
  void addEdge(Edge<int> e);
  list<Edge<int> > edges() const;
  
private:
  int _V;
  int _E;
  list<Edge<int>>* adjs;
};

EdgeWeightedGraph::EdgeWeightedGraph(int V)
  : _V(V), _E(0), adjs(nullptr)
{
  adjs = new list<Edge<int> >[_V] ();
}

EdgeWeightedGraph::EdgeWeightedGraph(string s)
  : _V(0), _E(0), adjs(nullptr)
{
  ifstream in(s);
  if(!in.is_open()) {
    cout << "打开文件失败" << endl;
    abort();
  }
  int a, b;
  double c;
  in >> a >> b;
  _V = a;
  adjs = new list<Edge<int> >[_V] ();
  // while (in >> a >> b >> c) 
  // {
  //   Edge<int> e(a, b, c);
  //   addEdge(e);
  // }
  do {
    in >> a >> b >> c;
    Edge<int> e(a, b, c);
    addEdge(e);
  } while(!in.eof());
  in.close();
}

void EdgeWeightedGraph::addEdge(Edge<int> e)
{
  int v = e.either(), w = e.other(v);
  adjs[v].push_back(e);
  adjs[w].push_back(e);
  ++_E;
}

list<Edge<int> > EdgeWeightedGraph::edges() const
{
  list<Edge<int >> le;
  for(int j = 0; j < _V; ++j)
    for(auto ej : adjs[j])
      if(ej.other(j) > j) le.push_back(ej);
  return le;
} 
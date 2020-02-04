/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-04 21:51:40 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-04 23:15:36
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <list>
#include <queue>
#include "EdgeWeightedGraph.hpp"
using namespace std;
/**
 * 最小生成树的Prim算法的延时实现
 **/ 
struct greater_ {
  bool operator() (const Edge<int>& a, const Edge<int>& b){
      int cmp = a.compareTo(b);
      if(cmp > 0) 
        return true;
      return false;
    }
};

class LazyPrimMST
{
  public:
    using Eg = Edge<int>;
    LazyPrimMST(EdgeWeightedGraph& g);
    queue<Eg> edges() const {return mst;};
    double weight() const;
  private:
    void visit(EdgeWeightedGraph& g, int v);
    priority_queue<Eg, vector<Eg>,greater_> pq;
    queue<Eg> mst;
    bool *marked;
};

double LazyPrimMST::weight() const
{
  double tl = 0;
  queue<Eg> mst_copy = mst;
  while(mst_copy.size())
  {
    Eg e = mst_copy.front();
    mst_copy.pop();
    tl += e.weight();
  }
  return tl;
}

LazyPrimMST::
LazyPrimMST(EdgeWeightedGraph& g)
  : pq(), mst(), marked(new bool [g.V()])
{
  for(int i = 0; i < g.V(); ++i)
    marked[i] = false;
  visit(g, 0);
  while(!pq.empty())
  {
    Eg e = pq.top();
    pq.pop();
    
    int v = e.either(), w = e.other(v);
    if(marked[v] && marked[w]) {
      continue;
    }
    mst.push(e);
    if(marked[v]) {
      visit(g, w);
    } else {
      visit(g ,v);
    }
  }
}

void LazyPrimMST::visit(EdgeWeightedGraph& g, int v)
{
  marked[v] = true;
  for(auto x : g.adj(v))
  {
    if(!marked[x.other(v)]){
      pq.push(x);
    }
  }
}
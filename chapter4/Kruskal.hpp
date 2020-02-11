/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-11 10:52:16 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-11 11:10:29
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <list>
#include <limits>
#include <queue>
#include "EdgeWeightedGraph.hpp"
#include "IndexMinPQ.hpp"
#include "Graph.hpp"
#include "LazyPrimMST.hpp"
#include "DepthFirstSearch.hpp"
using namespace std;
/**
 * Kruskal算法
 **/ 
class Kruskal
{
  public:
    Kruskal(EdgeWeightedGraph& g);
    double weight() const ;
  private:
    vector<Edge<int> > egs;
};

Kruskal::
Kruskal(EdgeWeightedGraph& g)
  :egs()
{
  priority_queue<Edge<int>, vector<Edge<int>>, greater_> mq;  
  for(auto e: g.edges()) mq.push(e);
  Graph ng(g.V());
  while(mq.size())
  {
    Edge<int> e = mq.top();
    mq.pop();
    int v = e.either(), w = e.other(v);
    DepthFirstSearch df(ng, v);
    if(df.getMarked(w)) 
      continue;
    ng.addEdge(v, w);
    egs.push_back(e);
  }
}

double Kruskal::weight() const
{
  double tl = 0;
  for(auto e: egs) {
    tl += e.weight();
  }
  return tl;
}
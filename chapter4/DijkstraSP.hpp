/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-12 17:49:18 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-12 22:14:02
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include "Edge.hpp"
#include <limits>
#include "EdgeWeightDigraph.hpp"
#include "IndexMinPQ.hpp"
using namespace std;
/**
 * Dijkstra
 **/ 

class DijkstraSP
{
private:
  /* data */
  vector<DirectedEdge> edgeTo;
  vector<double > distTo;
  IndexMinPQ<double> pq;
  
  
public:
  DijkstraSP(EdgeWeightDigraph& g, int v);
  ~DijkstraSP() {};

  bool hasPathTo(int v) const {return distTo[v] < numeric_limits<double>::max();}
  double DistTo(int v) const {return distTo[v];}
  vector<DirectedEdge> pathTo(int v) const ;
};

DijkstraSP::DijkstraSP(EdgeWeightDigraph& g, int v)
  :edgeTo(g.V()), distTo(g.V()), pq(g.V())
{ 
  for(auto& x: distTo)
    x = numeric_limits<double>::max();
  pq.insert(v, 0);
  distTo[v] = 0;
  while(pq.size())
  {
    int from = pq.delMin();
    for(auto e: g.adj(from)) {
      int to = e.to();
      if(distTo[to] > distTo[from] + e.weight()) {
        distTo[to] = distTo[from] + e.weight();
        edgeTo[to] = e;

        if(!pq.contain(to)) 
          pq.insert(to, e.weight());
        else 
          pq.change(to, e.weight());
      }
    }
  }
}


vector<DirectedEdge> 
DijkstraSP::pathTo(int v) const
{
  vector<DirectedEdge> res;
  if(!hasPathTo(v))
    return res;
  while(distTo[v]){
    res.push_back(edgeTo[v]);
    v = edgeTo[v].from();
  }
  reverse(res.begin(), res.end());
  return res;
}
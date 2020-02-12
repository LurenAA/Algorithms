/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-12 22:14:00 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-12 22:29:00
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include "Edge.hpp"
#include <queue>
#include <limits>
#include "EdgeWeightDigraph.hpp"
#include "IndexMinPQ.hpp"
using namespace std;
/**
 * BellmanFord
 **/ 

class BellmanFord
{
private:
  /* data */
  vector<double> distTo;
  vector<DirectedEdge> edgeTo;
  queue<int> q;
  vector<bool > onQ;
public:
  BellmanFord(EdgeWeightDigraph& g, int v);
  ~BellmanFord();
  bool hasPathTo(int v) const {return distTo[v] < numeric_limits<double>::max();}
  double DistTo(int v) const {return distTo[v];}
  vector<DirectedEdge> pathTo(int v) const ;
};

BellmanFord::BellmanFord(EdgeWeightDigraph& g, int v) :
  distTo(g.V()), edgeTo(g.V()), q(), onQ(g.V())
{
  for(int i = 0; i < g.V(); ++i) {
    onQ[i] = false;
    distTo[i] = numeric_limits<double>::max();
  }
  distTo[v] = 0;
  q.push(v);
  onQ[v] = true;
  while(q.size())
  {
    int w = q.front();
    q.pop();
    onQ[w] = false;
    for(auto e: g.adj(w)){
      int ww = e.to();
      if(distTo[ww] > distTo[w] + e.weight())
      {
        distTo[ww] = distTo[w] + e.weight();
        edgeTo[ww] = e;
        if(!onQ[ww]) {
          q.push(ww);
          onQ[ww] =true; 
        }
      }
    }
  }
}

BellmanFord::~BellmanFord()
{
}

vector<DirectedEdge> 
BellmanFord::pathTo(int v) const
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
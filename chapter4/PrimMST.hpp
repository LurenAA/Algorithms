/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-10 17:09:57 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-10 23:44:40
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
using namespace std;
/**
 * Prim算法即时实现
 **/ 

class PrimMST
{
  public:
    PrimMST(EdgeWeightedGraph &g);
    ~PrimMST() {delete [] marked; delete [] distTo;}
    double weight() const;
    const vector<Edge<int> >& edges() const {return egs;}
    void visit(EdgeWeightedGraph& g, int v);
  private:
    IndexMinPQ<double> pq;
    double *distTo;
    bool *marked;
    vector<Edge<int> >egs;
};

PrimMST::
PrimMST(EdgeWeightedGraph &g) :
  pq(g.V()), distTo(new double[g.V()]), marked(new bool [g.V()]), egs(g.V(), Edge<int>(0,0,0))
{
  for(int i = 0; i < g.V(); ++i)
  {
    distTo[i] = std::numeric_limits<double>::max();
    marked[i] = false;
  }
  distTo[0] = 0;
  pq.insert(0, 0);
  while(pq.size()){
    // pq.show();
    visit(g, pq.delMin());
  }
}

void PrimMST::visit(EdgeWeightedGraph& g, int v)
{
  // cout << v << ": " << endl;
  
  marked[v] = true;
  for(auto edg : g.adj(v))
  {
    int w = edg.other(v);
    
    if(marked[w]) continue;
    if(edg.weight() < distTo[w]){
      distTo[w] = edg.weight();
      egs[w] = edg;
      // cout << v << "-" << w << " "<< edg.weight() << endl;
      if(pq.contain(w)) 
        pq.change(w, distTo[w]);
      else 
        pq.insert(w, distTo[w]);
    }
  }
  // for(int i = 0; i < g.V(); ++i) 
  //   cout << egs[i].either() << "-" << egs[i].other(egs[i].either()) << " "<<distTo[i] << endl;
}

double PrimMST::weight() const
{
  double tl = 0;
  for(auto e: egs)
  {
    tl += e.weight();
  }
  return tl;
}
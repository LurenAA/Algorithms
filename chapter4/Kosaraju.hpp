/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-31 21:07:20 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-13 11:27:15
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
#include "Digraph.hpp"
#include "DepthFirstOrder.hpp"
using namespace std;
/**
 * Kosaraju算法
 **/ 
class Kosaraju
{
  public:
    Kosaraju(Digraph& g);
    ~Kosaraju() {delete [] id; delete [] marked;}
    bool stronglyConnected(int v, int w) const {return id[v] == id[w];}
  private:
    void dfs(Digraph& g, int v);
    int count;
    bool *marked;
    int *id;
};

Kosaraju::
Kosaraju(Digraph& g) :
  count(0), marked(new bool [g.V()]), id(new int [g.V()])
  {
    for(int i = 0; i < g.V(); ++i) 
    {
      marked[i] = false;
      id[i] = -1;
    }
    Digraph rg = g.reverse();
    DepthFirstOrder roder(rg);
    stack<int> stk = roder.getReversePost();
    while(!stk.empty()) {
      int k = stk.top();
      stk.pop();
      if(!marked[k]) {
        dfs(g, k);
        count++;
      }
    }
  }

void Kosaraju::dfs(Digraph& g, int v)
{
  id[v] = count;
  marked[v] = true;
  for(auto w : g.adj(v)) {
    if(!marked[w]) {
      dfs(g, w);
    }
  }
}
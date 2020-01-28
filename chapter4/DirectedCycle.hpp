/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-28 20:28:49 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-28 22:28:31
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "Digraph.hpp"
#include <stack>
#include <iterator>
using namespace std;
/**
 * 寻找有向环
 **/ 
class DirectedCycle
{
  public:
    DirectedCycle(Digraph& g);
    ~DirectedCycle();
    vector<stack<int> > cycles;
  private:
    void dfs(Digraph& g, int v);
    bool *marked;
    int *edgeTo;
    bool *stackOn;
};

DirectedCycle::
DirectedCycle(Digraph& g)
  : cycles(), marked(new bool [g.V()]), edgeTo(new int [g.V()]), stackOn(new bool [g.V()])
  
{
  for(int i = 0; i < g.V(); ++i) {
    marked[i] = false;
    stackOn[i] = false;
  }
  for(int i = 0; i < g.V(); ++i)
    if(!marked[i]) dfs(g, i);
}

void 
DirectedCycle::dfs(Digraph& g, int v)
{
  stackOn[v] = true;
  marked[v] = true;
  for(auto x : g.adj(v)) {
    if(!marked[x]) {
      edgeTo[x] = v;
      dfs(g, x);
    } else if (stackOn[x]){
      stack<int> tk;
      for(int w = v ; w != x; w = edgeTo[w])
      {
        tk.push(w);
      }
      tk.push(x);
      cycles.push_back(tk);
    }
  }
  stackOn[v] = false;
}

DirectedCycle::
~DirectedCycle()
{
  delete [] marked;
  delete [] edgeTo;
  delete [] stackOn;
}
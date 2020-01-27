/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-27 15:10:58 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-27 15:39:11
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
#include <Graph.hpp>
using namespace std;
/**
 * 连通分量
 **/ 
class CC{
  public:
    CC(Graph& g);
    int getCount() const {return count;}
    int getId(int i) const {return id[i];}
    bool connected(int v, int w) {return id[v] == id[w];}
  private:
    void dfs(Graph&g, int v);
    bool* marked;
    int *id;
    int count;
};

CC::CC(Graph& g)
  :marked(nullptr), id(nullptr), count(0)
{

  marked = new bool[g.V()] ();
  id = new int [g.V()] ();
  for(int i = 0; i < g.V(); ++i) {
    marked[i] = false;
  }
  for(int i = 0; i < g.V(); ++i) {
    if(!marked[i]) {
      dfs(g, i);
      count++;
    }
  }
}

void CC::dfs(Graph&g, int v)
{
  marked[v] = true;
  id[v] = count;
  for(auto x : g.adj(v)) {
    if(!marked[x])
      dfs(g, x);
  }
}
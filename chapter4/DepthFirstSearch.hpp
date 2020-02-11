/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-25 18:23:46 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-11 11:16:31
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <Graph.hpp>
using namespace std;
/**
 * 深度优先搜索
 **/ 

class DepthFirstSearch{
public:
  int getCount() const {return count;}
  bool getMarked(int i) const {return marked[i];}

  DepthFirstSearch(Graph& g, int i);
  ~DepthFirstSearch() {delete [] marked;}
private:
  void dfs(Graph& g, int v);
  bool *marked;
  int count;
};


DepthFirstSearch::DepthFirstSearch(Graph& g, int i)
  : count(0)
{
  marked = new bool [g.V()];
  for(int i = 0; i < g.V(); ++i)
    marked[i] = false;
  dfs(g, i);
}

void DepthFirstSearch::dfs(Graph& g, int v)
{
  marked[v] = true;
  ++count;
  for(auto x: g.adj(v)) {
    if(!marked[x]) dfs(g, x);
  }
}
/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-27 13:46:34 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-27 16:47:33
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
 * 广度优先搜索
 **/ 
class BreadthFirstPaths
{
  public:
    BreadthFirstPaths(Graph& g, int s);
    bool hasPathTo(int v) const {return marked[v];}
    stack<int> pathTo(int v);
  private:
    void bfs(Graph& g, int s);
    bool *marked;
    int *edgeTo;
    int s;
};

BreadthFirstPaths::
BreadthFirstPaths(Graph& g, int s)
   :marked(nullptr), edgeTo(nullptr), s(s)
{
  marked = new bool [g.V()]();
  edgeTo = new int [g.V()]();
  for(int i = 0; i < g.V(); ++i) {
    marked[i] = false;
  }
  bfs(g, s);
}

void 
BreadthFirstPaths::bfs(Graph& g, int s)
{
  marked[s] = true;
  queue<int> qu;
  qu.push(s);
  int i;
  while(!qu.empty()) 
  {
    i = qu.front();
    qu.pop();
    for(auto x : g.adj(i)) 
    {
      if(!marked[x]) {
        marked[x] = true;
        edgeTo[x] = i;
        qu.push(x);
      }
    }
  }
}

stack<int> BreadthFirstPaths::pathTo(int v)
{
  stack<int> stk;
  if(!hasPathTo(v)) 
    return stk;
  for( ; v != s ; v = edgeTo[v])
  {
    stk.push(v);
  }
  stk.push(v);
  return stk;
}
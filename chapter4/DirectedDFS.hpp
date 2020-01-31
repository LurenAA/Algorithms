/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-28 19:38:34 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-31 22:04:01
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "Digraph.hpp"
#include <iterator>
using namespace std;
/**
 * 有向图DFS
 **/ 
class DirectedDFS
{
  public:
    DirectedDFS(Digraph& g, int s);
    DirectedDFS(Digraph& g, vector<int> ss);
    ~DirectedDFS() {delete [] marked;}
    bool getMarked(int i) {return marked[i];}
  private:
    void dfs(Digraph& g, int v);
    bool *marked;
};

DirectedDFS::DirectedDFS(Digraph& g, int s) :
  marked(new bool [g.V()])
{
  for(int i = 0; i < g.V(); ++i)
    marked[i] = false;
  dfs(g, s);
}

DirectedDFS::DirectedDFS(Digraph& g, vector<int> ss) :
  marked(new bool [g.V()])
{
  for(int i = 0; i < g.V(); ++i)
    marked[i] = false;
  for(auto s : ss)
    dfs(g, s);
}

void DirectedDFS::dfs(Digraph& g, int v)
{
  marked[v] = true;
  for(auto x : g.adj(v)) 
  {
    if(!marked[x]) 
      dfs(g ,x);
  }
}
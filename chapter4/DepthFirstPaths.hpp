/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-25 19:14:34 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-25 20:27:27
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <Graph.hpp>
using namespace std;
/**
 * 深度优先搜索
 * 寻找路径
 **/ 
class DepthFirstPaths
{
public:
  DepthFirstPaths(Graph& g, int s);
  ~DepthFirstPaths() {delete [] edgeTo; delete [] marked;}
  bool hasPathTo(int v) const {return marked[v];};
  vector<int> pathTo(int v);
private:
  void dfs(Graph& g, int v);
  int *edgeTo;
  bool *marked;
  int s; //起点
};

DepthFirstPaths::DepthFirstPaths(Graph& g, int s)
  : edgeTo(nullptr), marked(nullptr), s(s)
{
  edgeTo = new int [g.V()];
  marked = new bool [g.V()] ;
  for(int i = 0;i < g.V(); ++i) {
    marked[i] = false;
  }
  dfs(g, s);
}

void DepthFirstPaths::dfs(Graph& g, int v)
{
  marked[v] = true;
  for(auto x : g.adj(v)) {
    if(!marked[x]) {
      edgeTo[x] = v;
      dfs(g, x);
    }
  }
}

vector<int> 
DepthFirstPaths::pathTo(int v)
{
  vector<int> vec;
  if(!marked[v]) return vec;
  vec.push_back(v);
  while(v != s) 
  {
    v = edgeTo[v];
    vec.push_back(v);
    
  }
  reverse(vec.begin(), vec.end());
  return vec;
}
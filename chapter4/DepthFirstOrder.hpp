/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-28 22:34:55 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-28 22:58:26
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include "Digraph.hpp"
#include <iterator>
using namespace std;
/**
 * 基于深度优先搜索的顶点排序
 **/ 
class DepthFirstOrder{
  public:
    DepthFirstOrder(Digraph& g);
    ~DepthFirstOrder() {delete [] marked;}
    const queue<int >& getPre() const {return pre;}
    const queue<int >& getPost() const {return post;}
    const stack<int >& getReversePost() const {return reversePost;}
  private:
    void dfs(Digraph& g, int v);
    bool *marked;
    queue<int > pre;
    queue<int > post;
    stack<int > reversePost;
};

DepthFirstOrder::
DepthFirstOrder(Digraph& g)
  : marked(nullptr) ,pre(), post(), reversePost()
{
  marked = new bool [g.V()];
  for(int i = 0; i < g.V(); ++i) 
    marked[i] = false;
  for(int i = 0; i < g.V(); ++i)
    if(!marked[i]) dfs(g, i);
}

void 
DepthFirstOrder::dfs(Digraph& g, int v)
{
  pre.push(v);
  marked[v] = true;
  for(auto w : g.adj(v))
    if(!marked[w]) dfs(g, w);
  
  post.push(v);
  reversePost.push(v);
}
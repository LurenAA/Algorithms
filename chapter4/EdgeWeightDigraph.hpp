/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-12 10:15:02 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-12 11:02:29
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "Digraph.hpp"
#include <iostream>
#include <iterator>
#include "DirectedEdge.hpp"
using namespace std;
/**
 * 加权有向图
 **/
class EdgeWeightDigraph
{
  public:
    EdgeWeightDigraph(string name);
    ~EdgeWeightDigraph() {delete [] adjs;}
    void addEdge(DirectedEdge );
    int E() const {return e;}
    int V() const {return v;}
    const vector<DirectedEdge> & adj(int v) const{return adjs[v];}
    vector<DirectedEdge> edges()const;
  private:
    int e;
    int v;
    vector<DirectedEdge >* adjs;
};

EdgeWeightDigraph::
EdgeWeightDigraph(string s)
  : e(0), v(0), adjs(nullptr)
{
  ifstream in(s);
  if(!in.is_open()) {
    cout << "打开文件失败" << endl;
    abort();
  }
  int a, b;
  double c;
  in >> a >> b;
  v = a;
  adjs = new vector<DirectedEdge > [v]();
  // while (in >> a >> b >> c) 
  // {
  //   Edge<int> e(a, b, c);
  //   addEdge(e);
  // }
  do {
    in >> a >> b >> c;
    DirectedEdge e(a, b, c);
    addEdge(e);
  } while(!in.eof());
  in.close();
}

void EdgeWeightDigraph::addEdge(DirectedEdge e)
{
  adjs[e.from()].push_back(e);
  this->e++;
}

vector<DirectedEdge> EdgeWeightDigraph::edges() const
{
  vector<DirectedEdge> bags;
  for(int i = 0; i < V(); ++i)
  {
    for(auto e: adjs[i])
      bags.push_back(e);
  }
  return bags;
}
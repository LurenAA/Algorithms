/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-27 16:47:30 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-27 17:08:22
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
#include <map>
using namespace std;
/**
 * 符号图
 **/ 
class SymbolGraph
{
  public:
    SymbolGraph(string stream);
    bool contain(string s) const {return st.count(s) > 0;}
    int index(string s) {return st[s];}
    string name(int v) {return keys[v];}
  private:
    map<string, int> st;
    string *keys;
    Graph* g;
};

SymbolGraph::SymbolGraph(string filename)
{
  ifstream in(filename);
  vector<string > vec;
  string a, b;
  while(in >> a >> b) {
    if(!st.count(a))
      st.insert({a,st.size()});
    if(!st.count(b)) 
      st.insert({b,st.size()});
  }
  keys = new string [st.size()];
  for(auto n : st) {
    keys[n.second] = n.first;
  }
  g = new Graph(st.size());
  in.seekg(0);
  while(in >> a >> b) {
    g->addEdge(st[a], st[b]);
  }
  in.close();
}
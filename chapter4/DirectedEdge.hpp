/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-12 10:11:54 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-12 19:35:17
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
 * 加权有向边
 **/ 
class DirectedEdge
{
  public:
    DirectedEdge(int v = 0, int w = 0, double weight = 0) 
      : v(v), w(w), _weight(weight) {}
    bool operator==(const DirectedEdge& rhs) const {
      return rhs.v == v && rhs.w == w && rhs._weight == _weight;
    }
    double weight() {return _weight;}
    int from() const{return v;}
    int to() const {return w;}
  private:
    int v;
    int w;
    double _weight;
};
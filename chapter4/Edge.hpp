/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-01 20:29:57 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-04 22:30:43
 */
#pragma once
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;
/**
 * 加权边
 **/ 
template <typename T>
class Edge 
{
public:
  Edge(T v, T w, double weight);
  double weight() const {return _weight;}
  const T& either() const {return v;}
  const T& other(const T& vertex);
  int compareTo(const Edge<T>& e) const;
  string toString() const;
private:
  T v, w;
  double _weight;
};

template<typename T>
Edge<T>::Edge(T v, T w, double weight)
  : v(v), w(w), _weight(weight)
{
}

template<typename T>
const T& Edge<T>::other(const T& vertex)
{
  if(vertex == w) return v;
  else if(vertex == v) return w;
  else throw exception();
}

template<typename T>
int Edge<T>::compareTo(const Edge<T>& e) const
{
  if(_weight > e.weight()) return 1;
  else if(_weight < e.weight()) return -1;
  else return 0;
}

template<typename T>
string Edge<T>::toString() const
{
  ostringstream ins;
  ins << v << "-" << w << " " << weight << "\n";
  return ins.str();
}
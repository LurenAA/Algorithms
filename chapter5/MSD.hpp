/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-13 13:22:27 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-13 14:55:33
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
using namespace std;

/**
 * 高位优先的字符串排序
 **/ 
class MSD
{
private:
  int R; //标准ascii=128
  vector<string> aux;

  int charAt(string& s,unsigned int i) const;
  void sort(vector<string>& s, int lo, int hi, int pos);
public:
  MSD(vector<string>& s);
  ~MSD();
};

MSD::MSD(vector<string>& s)
  :R(128), aux(s.size())
{
  sort(s, 0, s.size(), 0);
}

MSD::~MSD()
{
}

int MSD::charAt(string& s, unsigned int i) const
{
  if(i >= s.size())
   return -1;
  else return static_cast<int>(s[i]);
}

void MSD::sort(vector<string>& s, int lo, int hi, int pos)
{
  if(hi - lo <= 1) {
    // std::sort(s.begin() + lo, s.begin() + hi);
    return;
  }
  vector<int> count(R + 2, 0);
  for(int i = lo; i < hi; ++i) 
    count.at(charAt(s.at(i), pos) + 2)++;
  for(int i = 0; i < R + 1; ++i)
    count.at(i + 1) += count.at(i);
  for(int i = lo; i < hi; ++i)
    aux[count[charAt(s[i], pos) + 1]++] = s[i];
  for(int i = lo; i < hi; ++i)
    s[i] = aux[i - lo];
  
  for(int i = 1; i <= R; ++i)
    sort(s, lo + count[i], lo + count[i + 1], pos + 1);
}
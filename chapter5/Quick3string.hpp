/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-13 14:55:29 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-13 15:23:13
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
 * 三向字符串快速排序
 **/ 
class Quick3string
{
private:
  /* data */
  int charAt(string& s,unsigned int i) const;
  void sort(vector<string>& a, int lo, int hi, int p);
public:
  Quick3string(vector<string>& a);
  ~Quick3string();
};

int Quick3string::charAt(string& s, unsigned int i) const
{
  if(i >= s.size())
   return -1;
  else return static_cast<int>(s[i]);
}

Quick3string::Quick3string(vector<string>& a)
{
  sort(a, 0, a.size() - 1, 0);
}

Quick3string::~Quick3string()
{
}

void Quick3string::sort(vector<string>& a, int lo, int hi, int p)
{
  if(lo >= hi)
    return ;
  int lr = lo,
   ml = hi,
   i = lo + 1,
   v = charAt(a.at(lo), p);
  while(i <= ml) {
    int t = charAt(a.at(i), p);
    if(v < t) swap(a.at(i), a.at(ml--));
    else if (v == t) ++i;
    else swap(a.at(i++), a.at(lr++));
  }
  sort(a, lo, lr - 1, p);
  sort(a, ml + 1, hi, p);
  if(v >= 0) sort(a, lr, ml, p + 1);
}
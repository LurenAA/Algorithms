/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-13 11:27:12 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-13 13:22:41
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
 * 低位优先的字符串排序
 **/ 
class LSD
{
private:
  /* data */
public:
  LSD(vector<string>& a, int w);
  ~LSD();
};

LSD::LSD(vector<string>& a, int w)
{
  vector<string > aux(a.size());
  unsigned int R = 128;
  for(int v = w - 1; v >= 0; --v)
  {
    int count[R + 1] = {0};
    for(unsigned i = 0; i < a.size(); ++i)
      count[static_cast<int>(a[i][v]) + 1]++;
    for(unsigned i = 0; i < R; ++i)
      count[i + 1] += count[i];
    for(unsigned i = 0; i < a.size(); ++i)
      aux[count[static_cast<int>(a[i][v])]++] = a[i];
    for(unsigned i = 0; i < a.size(); ++i)
      a[i] = aux[i];
  }
}

LSD::~LSD()
{
}

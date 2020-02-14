/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-14 21:08:02 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-14 21:17:53
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
 * BoyerMoore
 **/ 
class BoyerMoore
{
private:
  /* data */
  static constexpr int R = 256;
  string pat;
  int right[R];

public:
  BoyerMoore(const string& s);
  int search(const string& s) const;
  ~BoyerMoore();
};

int BoyerMoore::search(const string& s) const {
  int i = 0, j, skip = 0;
  for( ;i <= s.size() - pat.size(); i += skip) {
    skip = 0;
    for(j = pat.size() - 1; j >= 0; --j) {
      if(s.at(i + j) != pat.at(j)) {
        skip = j - right[s.at(i + j)];
        if(skip < 1) skip = 1;
        break;
      }
    }
    if(!skip) return i;
  }
  return s.size();
}

BoyerMoore::BoyerMoore(const string& s)
  :pat(s), right({0})
{
  fill(begin(right), end(right), -1);
  for(unsigned i = 0; i < s.size(); ++i)
    right[s.at(i)] = i;    
}

BoyerMoore::~BoyerMoore()
{
}

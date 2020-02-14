/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-14 18:48:56 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-14 19:36:56
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
 * Kmp
 **/ 

class Kmp
{
private:
  /* data */
  static constexpr int R = 256;
  string pat;
  vector<vector<int>> dfa;

public:
  Kmp(string pat);
  ~Kmp();

  int search(const string& s) const;
};

Kmp::Kmp(string pat)
  : pat(pat), dfa(R, vector<int>(pat.size()))
{
  int M = pat.size();
  for(int i = 0; i < R; ++i)
    dfa[i][0] = 0;
  dfa[pat.at(0)][0] = 1;
  for(int X = 0, j = 1; j < M ; ++j)
  {
    for(int i = 0; i < R; ++i)
      dfa[i][j] = dfa[i][X];
    dfa[pat.at(j)][j] = 1 + j;

    X = dfa[pat.at(j)][X];
  }
}

Kmp::~Kmp()
{
}

int Kmp::search(const string& s) const
{
  unsigned i = 0, j = 0;
  for(; j < s.size() && i < pat.size(); ++j)
    i = dfa[s.at(j)][i];
  if(j == s.size()) return j;
  return j - pat.size();
}

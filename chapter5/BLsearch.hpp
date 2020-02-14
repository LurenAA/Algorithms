/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-13 23:39:13 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-14 18:49:01
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
 * 暴力子字符串查找
 **/ 
class BLsearch
{
private:
  /* data */
public:
  static int search(string s, string txt) {
    for(unsigned i = 0;  i <= txt.size() - s.size(); ++ i)
    {
      unsigned j = 0;
      for( ; j < s.size(); ++j)
        if(txt[i + j] != s[j]) break;
      if(j == s.size()) return i;
    }
    return txt.size();
  }
};



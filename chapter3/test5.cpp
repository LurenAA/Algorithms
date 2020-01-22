/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-22 19:11:45 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-22 20:16:51
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "LinearProbingHashST.hpp"
#include <vector>
#include <string>
using namespace std;

/**
 * 线性探测法的散列表的单元测试
 **/ 

TEST_CASE("put", "[ST]") {
  LinearProbingHashST<int> st(2);
  st.put(1, 1);
  st.put(2, 2);
  REQUIRE(st.size() == 2);
  st.put(3, 3);
  st.put(7, 7);
  st.put(19, 19);
  st.put(22, 22);
  st.put(43, 43);
  st.put(48, 48);
  st.put(56, 56);
  st.put(70, 70);
  REQUIRE(st.size() == 10);
  st.delet(7);
  REQUIRE(st.size() == 9);
}
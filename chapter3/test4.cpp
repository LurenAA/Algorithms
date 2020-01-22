/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-22 18:10:15 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-22 19:11:47
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "SeparateChainingHashST.hpp"
#include <vector>
#include <string>
using namespace std;

/**
 * 拉链法的散列表的单元测试
 **/ 

TEST_CASE("put", "[schST]") {
  SeparateChainingHashST<string> st(10);
  st.put(1, "1");
  st.put(11, "11");
  REQUIRE(st.size() == 2);
  REQUIRE(st.get(11) == "11");
  REQUIRE(st.get(1) == "1");
  st.put(123, "123");
  REQUIRE(st.size() == 3);
  REQUIRE(st.get(123) == "123");
}
/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-21 21:13:54 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-21 21:14:15
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "AvlTree.hpp"
#include <vector>
#include <string>
using namespace std;

/**
 * avl树单元测试
 **/ 

TEST_CASE("put", "[avl]") {
  AvlTree<char, char> tri;
  tri.put('M','M');
  REQUIRE(tri.get('M')->height == 1);
  tri.put('N','N');
  REQUIRE(tri.get('M')->height == 2);
  tri.put('O','O');
  auto N = tri.get('N');
  REQUIRE(N->height == 2);
  REQUIRE(N->left->height == 1);
  REQUIRE(N->right->height == 1);
  tri.put('L','L');
  tri.put('K','K');
  REQUIRE(N->height == 3);
  REQUIRE(N->left->height == 2);
  REQUIRE(N->right->height == 1);
  tri.put('Q','Q');
  REQUIRE(N->height == 3);
  REQUIRE(N->left->height == 2);
  REQUIRE(N->right->height == 2);
  tri.put('P','P');
  REQUIRE(N->height == 3);
  REQUIRE(N->left->height == 2);
  REQUIRE(N->right->height == 2);
  tri.put('H','H');
  REQUIRE(N->height == 4);
  REQUIRE(N->left->height == 3);
  REQUIRE(N->right->height == 2);
  tri.put('I','I');
  REQUIRE(N->height == 4);
  REQUIRE(N->left->height == 3);
  REQUIRE(N->right->height == 2);
  tri.put('A','A');
  REQUIRE(N->height == 4);
  REQUIRE(N->left->height == 3);
  REQUIRE(N->right->height == 2);
  REQUIRE(tri.isBalanced() == true);

  SECTION("deleteMin") {
    tri.deleteMin();
    REQUIRE(tri.isBalanced() == true);
    tri.deleteMin();
    REQUIRE(tri.isBalanced() == true);
    tri.deleteMin();
    REQUIRE(tri.isBalanced() == true);
    tri.deleteMin();
    REQUIRE(tri.isBalanced() == true);
    tri.deleteMin();
    REQUIRE(tri.isBalanced() == true);
    tri.deleteMin();
    REQUIRE(tri.isBalanced() == true);
  }

  SECTION("delet") {
    tri.delet('A');
    REQUIRE(tri.isBalanced() == true);
  }

  SECTION("delet1") {
    tri.delet('I');
    REQUIRE(tri.isBalanced() == true);
  }
}
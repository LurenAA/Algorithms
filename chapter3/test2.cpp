/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-19 10:21:08 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-19 11:35:48
 */

#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "RedBlackBST.hpp"
#include <vector>
#include <string>
using namespace std;

/**
 * 红黑树单元测试
 **/

TEST_CASE("put", "[rdBST]") {
  RedBlackBST<char, char> bst;
  SECTION("test size") {
    vector<char> iv1{'S','E','A','R','C','H','X','M','P','L'};
    for(size_t k = 0; k < iv1.size(); ++k) { 
      bst.put(iv1[k], iv1[k]);
      REQUIRE(bst.size() == k + 1);
    }

    SECTION("deleteMin") {
      bst.deleteMin();
      REQUIRE(bst.size() == 9);
      REQUIRE(bst.min() == 'C');
      bst.deleteMin();
      REQUIRE(bst.size() == 8);
      REQUIRE(bst.min() == 'E');
      bst.deleteMin();
      REQUIRE(bst.size() == 7);
      REQUIRE(bst.min() == 'H');
      bst.deleteMin();
      REQUIRE(bst.size() == 6);
      REQUIRE(bst.min() == 'L');
      bst.deleteMin();
      REQUIRE(bst.size() == 5);
      REQUIRE(bst.min() == 'M');
      bst.deleteMin();
      REQUIRE(bst.size() == 4);
      REQUIRE(bst.min() == 'P');
      bst.deleteMin();
      REQUIRE(bst.size() == 3);
      REQUIRE(bst.min() == 'R');
      bst.deleteMin();
      REQUIRE(bst.size() == 2);
      REQUIRE(bst.min() == 'S');
      bst.deleteMin();
      REQUIRE(bst.size() == 1);
      REQUIRE(bst.min() == 'X');
      bst.deleteMin();
      REQUIRE(bst.size() == 0);
    }

    SECTION("deleteMax") {
      bst.deleteMax();
      REQUIRE(bst.max() == 'S');
      REQUIRE(bst.size() == 9);
      bst.deleteMax();
      REQUIRE(bst.size() == 8);
      REQUIRE(bst.max() == 'R');
      bst.deleteMax();
      REQUIRE(bst.size() == 7);
      REQUIRE(bst.max() == 'P');
      bst.deleteMax();
      REQUIRE(bst.size() == 6);
      REQUIRE(bst.max() == 'M');
      bst.deleteMax();
      REQUIRE(bst.size() == 5);
      REQUIRE(bst.max() == 'L');
      bst.deleteMax();
      REQUIRE(bst.size() == 4);
      REQUIRE(bst.max() == 'H');
      bst.deleteMax();
      REQUIRE(bst.size() == 3);
      REQUIRE(bst.max() == 'E');
      bst.deleteMax();
      REQUIRE(bst.size() == 2);
      REQUIRE(bst.max() == 'C');
      bst.deleteMax();
      REQUIRE(bst.size() == 1);
      REQUIRE(bst.max() == 'A');
      bst.deleteMax();
      REQUIRE(bst.size() == 0);
    }

    SECTION("delete") {
      bst.delet('X');
      auto v1 = bst.keys();
      REQUIRE(bst.size() == 9);
      REQUIRE(bst.max() == 'S');
      REQUIRE(v1.size() == 9);
      bst.delet('A');
      REQUIRE(bst.size() == 8);
      REQUIRE(bst.min() == 'C');
    }

    SECTION("delete1") {
      bst.delet('M');
      REQUIRE(bst.size() == 9);
      REQUIRE(bst.get('M') == nullptr);
      bst.delet('E');
      REQUIRE(bst.size() == 8);
      REQUIRE(bst.get('E') == nullptr);
    } 
  }
  SECTION("test every step") {
    bst.put('S','S');
    REQUIRE(bst.size() == 1);
    bst.put('E','E');
    REQUIRE(bst.size() == 2);
    auto ne = bst.get('E');
    REQUIRE(ne->color == Color::Red);
    bst.put('A', 'A');
    REQUIRE(bst.size() == 3);
    auto na = bst.get('A');
    REQUIRE(na->color == Color::Black);
    REQUIRE(ne->color == Color::Black);
    bst.put('R','R');
    REQUIRE(bst.size() == 4);
    auto nr = bst.get('R');
    REQUIRE(nr->color == Color::Red);
  }
}

TEST_CASE("put2", "[rdBST]") {
  RedBlackBST<char, char> bst;
  SECTION("test size") {
    vector<char> iv1{'A','C','E','H','L','M','P','R','S','X'};
    for(size_t k = 0; k < iv1.size(); ++k) { 
      bst.put(iv1[k], iv1[k]);
      REQUIRE(bst.size() == k + 1);
    }
  }
}
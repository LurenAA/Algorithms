/*
 * @Author: xiao gongbai 
 * @Date: 2020-01-14 23:20:44 
 * @Last Modified by: xiao gongbai
 * @Last Modified time: 2020-01-15 02:44:08
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "BST.hpp"
#include <vector>
#include <string>
using namespace std;

TEST_CASE("put", "[BST]") {
  BST<char, char> bst;
  SECTION("case 1") {
    vector<char> init_keys{'H','C','S','A', 'E','R','X'};
    for(size_t i = 0; i < init_keys.size(); ++i) {
      bst.put(init_keys[i], init_keys[i]);
      REQUIRE(bst.size() == i + 1);
    }
    
    vector<char> keys = bst.keys();
    REQUIRE(keys.size() == init_keys.size());
    vector<char> keys1 = bst.keys('C', 'S');
    REQUIRE(keys1.size() == 5);
    auto keys2 = bst.keys('C', 'H');
    REQUIRE(keys2.size() == 3);

    auto H = bst.get('H', 1);
    REQUIRE(H->N == 7);
    auto C = bst.get('C', 1);
    REQUIRE(C->N == 3);
    auto S = bst.get('S', 1);
    REQUIRE(S->N == 3);
    auto A = bst.get('A', 1);
    REQUIRE(A->N == 1);

    auto flg = bst.floor('G');
    REQUIRE(flg == 'E');
    auto flh = bst.floor('H');
    REQUIRE(flh == 'H');
    auto flz = bst.floor('Z');
    REQUIRE(flz == 'X');
    auto flb = bst.floor('B');
    REQUIRE(flb == 'A');
    auto flc = bst.floor('C');
    REQUIRE(flc == 'C');
    auto flt = bst.floor('T');
    REQUIRE(flt == 'S');
    auto flq = bst.floor('Q');
    REQUIRE(flq == 'H');
  }
  
  SECTION("case 2") {
    vector<char> init_keys{'S','E','A','R', 'C','H','X'};
    for(size_t i = 0; i < init_keys.size(); ++i) {
      bst.put(init_keys[i], init_keys[i]);
      REQUIRE(bst.size() == i + 1);
    }

    INFO("test keys");
    auto keys = bst.keys();
    REQUIRE(keys.size() == init_keys.size());
    auto keys1 = bst.keys('E','S');
    REQUIRE(keys1.size() == 4);

    INFO("test get");
    auto S = bst.get('S', 1);
    REQUIRE(S->N == 7);
    auto C = bst.get('C', 1);
    REQUIRE(C->N == 1);
    auto E = bst.get('E', 1);
    REQUIRE(E->N == 5);
    auto A = bst.get('A', 1);
    REQUIRE(A->N == 2);

    bool cta = bst.contain('A');
    REQUIRE(cta == true);
    bool cts = bst.contain('S');
    REQUIRE(cts == true);
    
    auto flg = bst.floor('G');
    REQUIRE(flg == 'E');
    auto flh = bst.floor('H');
    REQUIRE(flh == 'H');
    auto flz = bst.floor('Z');
    REQUIRE(flz == 'X');
    auto flb = bst.floor('B');
    REQUIRE(flb == 'A');
  }
}

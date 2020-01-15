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

    auto clq = bst.ceiling('Q');
    REQUIRE(clq == 'R');
    auto clO = bst.ceiling('O');
    REQUIRE(clO == 'R');
    auto clR = bst.ceiling('R');
    REQUIRE(clR == 'R');
    auto clI = bst.ceiling('I');
    REQUIRE(clI == 'R');
    auto clc = bst.ceiling('C');
    REQUIRE(clc == 'C');
    auto cle = bst.ceiling('E');
    REQUIRE(cle == 'E');
    auto clf = bst.ceiling('F');
    REQUIRE(clf == 'H');

    REQUIRE((bst.select(0) == 'A'));
    REQUIRE((bst.select(1) == 'C'));
    REQUIRE((bst.select(2) == 'E'));
    REQUIRE((bst.select(3) == 'H'));
    REQUIRE((bst.select(4) == 'R'));
    REQUIRE((bst.select(5) == 'S'));
    REQUIRE((bst.select(6) == 'X'));

    REQUIRE(bst.rank('A') == 0);
    REQUIRE(bst.rank('B') == 1);
    REQUIRE(bst.rank('D') == 2);
    REQUIRE(bst.rank('F') == 3);
    REQUIRE(bst.rank('R') == 4);

    SECTION("case 1.1") {
      bst.deleteMin();
      REQUIRE(bst.size() == 6);
      REQUIRE(bst.select(0) == 'C');
      REQUIRE(bst.get('C', 1)->N == 2);

      bst.deleteMin();
      REQUIRE(bst.size() == 5);
      REQUIRE(bst.select(0) == 'E');
      REQUIRE(bst.get('E', 1)->N == 1);

      bst.deleteMin();
      REQUIRE(bst.size() == 4);
      REQUIRE(bst.select(0) == 'H');
      REQUIRE(bst.get('H', 1)->N == 4);

      bst.deleteMin();
      REQUIRE(bst.size() == 3);
      REQUIRE(bst.select(0) == 'R');
      REQUIRE(bst.get('R', 1)->N == 1);

      bst.deleteMin();
      REQUIRE(bst.size() == 2);
      REQUIRE(bst.get('S', 1)->N == 2);
      
      bst.deleteMin();
      REQUIRE(bst.size() == 1);
      REQUIRE(bst.get('X', 1)->N == 1);

      bst.deleteMin();
      REQUIRE(bst.size() == 0);
      
    }

    SECTION("case 1.2") {
      bst.deleteMax();
      REQUIRE(bst.max() == 'S');
      REQUIRE(bst.size() == 6);

      bst.deleteMax();
      REQUIRE(bst.max() == 'R');
      REQUIRE(bst.size() == 5);

      bst.deleteMax();
      REQUIRE(bst.max() == 'H');
      REQUIRE(bst.size() == 4);

      bst.deleteMax();
      REQUIRE(bst.max() == 'E');
      REQUIRE(bst.size() == 3);

      bst.deleteMax();
      REQUIRE(bst.max() == 'C');
      REQUIRE(bst.size() == 2);

      bst.deleteMax();
      REQUIRE(bst.max() == 'A');
      REQUIRE(bst.size() == 1);

      bst.deleteMax();
      REQUIRE(bst.size() == 0);
    }

    SECTION("case 1.3") {
      REQUIRE(bst.size() == 7);
      bst.delet('C');
      REQUIRE(bst.rank('E') == 1);
      REQUIRE(bst.rank('A') == 0);
      REQUIRE(bst.size() == 6);

      bst.delet('H');
      REQUIRE(bst.size() == 5);
      REQUIRE(bst.rank('R') == 2);

      bst.delet('R');
      REQUIRE(bst.size() == 4);
      REQUIRE(bst.rank('S') == 2);
      REQUIRE(bst.rank('A') == 0);
      REQUIRE(bst.rank('E') == 1);

    }
  }
  
  SECTION("case 2") {
    vector<char> init_keys{'S','E','A','R', 'C','H','X'};
    for(size_t i = 0; i < init_keys.size(); ++i) {
      bst.put(init_keys[i], init_keys[i]);
      REQUIRE(bst.size() == i + 1);
    }

    auto keys = bst.keys();
    REQUIRE(keys.size() == init_keys.size());
    auto keys1 = bst.keys('E','S');
    REQUIRE(keys1.size() == 4);

    auto S = bst.get('S', 1);
    REQUIRE(S->N == 7);
    auto C = bst.get('C', 1);
    REQUIRE(C->N == 1);
    auto E = bst.get('E', 1);
    REQUIRE(E->N == 5);
    auto A = bst.get('A', 1);
    CAPTURE(A);
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

    auto clf = bst.ceiling('F');
    REQUIRE(clf == 'H');
    auto clb = bst.ceiling('B');
    REQUIRE(clb == 'C');

    auto s0 = bst.select(0);
    REQUIRE(s0 == 'A');
    REQUIRE((bst.select(1) == 'C'));
    REQUIRE((bst.select(2) == 'E'));
    REQUIRE((bst.select(3) == 'H'));
    REQUIRE((bst.select(4) == 'R'));
    REQUIRE((bst.select(5) == 'S'));
    REQUIRE((bst.select(6) == 'X'));

    REQUIRE(bst.rank('A') == 0);
    REQUIRE(bst.rank('B') == 1);
    REQUIRE(bst.rank('D') == 2);
    REQUIRE(bst.rank('F') == 3);
    REQUIRE(bst.rank('R') == 4);

    SECTION("case 2.1") {
      bst.deleteMin();
      REQUIRE(bst.rank('C') == 0);
      REQUIRE(bst.size() == 6);

      bst.deleteMin();
      REQUIRE(bst.rank('E') == 0);
      REQUIRE(bst.size() == 5);

      bst.deleteMin();
      REQUIRE(bst.rank('H') == 0);
      REQUIRE(bst.size() == 4);

      bst.deleteMin();
      REQUIRE(bst.rank('R') == 0);
      REQUIRE(bst.size() == 3);
    }
  }
}

/*
 * @Author: XiaoGongBai 
 * @Date: 2020-02-13 10:30:43 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-02-13 23:58:23
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "LSD.hpp"
#include "MSD.hpp"
#include "Quick3string.hpp"
#include "TrieST.hpp"
#include "BLsearch.hpp"
using namespace std;

/**
 * 测试
 **/ 

TEST_CASE("5.1")
{
  vector<string> strs = {
    "4PGC938", "2IYE230", "3CI0720", "1ICK750", "1OHV845", "4JZY524", "1ICK750",
    "3CIO720", "1OHV845", "1OHV845", "2RLA629", "2RLA629", "3ATW723"
  };
  LSD lsd(strs, 7); 
  REQUIRE(strs[0] == "1ICK750");
  REQUIRE(strs[1] == "1ICK750");
  REQUIRE(strs[2] == "1OHV845");
  REQUIRE(strs[3] == "1OHV845");
  REQUIRE(strs[4] == "1OHV845");
  REQUIRE(strs[5] == "2IYE230");
  REQUIRE(strs[strs.size() - 1] == "4PGC938");
  vector<string > strs2 = {
    "she", "sells", "seashells", "by", "the", "seashore", "the", "shells",
    "she", "sells", "are", "surely", "seashells"
  };
  SECTION("msd") {
    MSD msd(strs2);
    REQUIRE(strs2[0] == "are");
    REQUIRE(strs2[1] == "by");
    REQUIRE(strs2[2] == "seashells");
  }
  SECTION("q3s") {
    Quick3string msd(strs2);
    REQUIRE(strs2[0] == "are");
    REQUIRE(strs2[1] == "by");
    REQUIRE(strs2[2] == "seashells");
  }
}

TEST_CASE("5.2"){
  vector<string > strs2 = {
    "she", "sells", "seashells", "by", "the", "seashore", "sea"
  };
  TrieST<int> trie;
  for(unsigned x = 0; x < strs2.size(); ++x)
    trie.put(strs2.at(x), x + 1);
  REQUIRE(trie.get("she") == 1);
  REQUIRE(trie.get("the") == 5);
  REQUIRE(trie.keys().size() == 7);
  REQUIRE(trie.keysThatMatch("the").size() == 1);
  REQUIRE(trie.keysThatMatch("seash...").size() == 1);
  REQUIRE(trie.longestPrefixOf("seashels") == "sea");
  trie.delet("sea");
  REQUIRE(trie.keys().size() == 6);
  REQUIRE(trie.get("sea") == 0);
}

TEST_CASE("5.3"){
  REQUIRE(BLsearch::search("AAAAE","AAAAAAAAAE") == 5);
}
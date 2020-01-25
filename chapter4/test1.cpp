/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-25 14:40:47 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-25 20:17:50
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "Graph.hpp"
#include "DepthFirstSearch.hpp"
#include "DepthFirstPaths.hpp"
#include <vector>
#include <string>
using namespace std;

/**
 * 图测试
 **/ 

TEST_CASE("Graph") {
  Graph g("tinyG.txt");
  REQUIRE(g.V() == 13);
  REQUIRE(g.E() == 13);
  REQUIRE(g.adj(0).size() == 4);
  REQUIRE(g.adj(1).size() == 1);
}

/**
 *  dfs
 **/  
TEST_CASE("dfs") {
  Graph g(6);
  g.addEdge(0, 2);
  g.addEdge(0, 1);
  g.addEdge(0, 5);
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(2, 4);
  g.addEdge(3, 5);
  g.addEdge(3 ,4);

  SECTION("DepthFirstSearch") {
    DepthFirstSearch dfs(g, 0);
    REQUIRE(dfs.getMarked(0) == true);
    REQUIRE(dfs.getMarked(2) == true);
    REQUIRE(dfs.getMarked(3) == true);
    REQUIRE(dfs.getMarked(4) == true);
  }

  SECTION("DepthFirstPaths") {
    DepthFirstPaths dfs(g, 0);
    vector<int> vec = dfs.pathTo(4);
    REQUIRE(vec == vector<int>{0,2,3,4});
  }
}

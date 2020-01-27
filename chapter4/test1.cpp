/*
 * @Author: XiaoGongBai 
 * @Date: 2020-01-25 14:40:47 
 * @Last Modified by: XiaoGongBai
 * @Last Modified time: 2020-01-27 17:09:41
 */
#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Common.hpp"
#include "Graph.hpp"
#include "DepthFirstSearch.hpp"
#include "DepthFirstPaths.hpp"
#include "BreadthFirstPaths.hpp"
#include "CC.hpp"
#include <vector>
#include <string>
#include "SymbolGraph.hpp"
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

  CC c(g);
  REQUIRE(c.connected(0, 1));
  REQUIRE(c.connected(1, 2));
  REQUIRE(c.connected(2, 3));
  REQUIRE(c.connected(3, 4));
  REQUIRE(c.connected(4, 5));
  REQUIRE(c.connected(5, 6));
  REQUIRE(c.connected(7, 8));
  REQUIRE(c.connected(9, 10));
  REQUIRE(c.connected(10, 11));
  REQUIRE(c.connected(11, 12)); 
}

/**
 *  dfs
 **/  
TEST_CASE("dfs") {
  SymbolGraph g1("routes.txt");
  
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

  SECTION("BreadthFirstPaths") {
    BreadthFirstPaths bfs(g, 0);
    stack<int> stk;
    SECTION("1") {
      stk.push(1);
      stk.push(0);
      REQUIRE(bfs.pathTo(1) == stk);
    }
    SECTION("2") {
      stk.push(2);
      stk.push(0);
      REQUIRE(bfs.pathTo(2) == stk);
    }
    SECTION("5") {
      stk.push(5);
      stk.push(0);
      REQUIRE(bfs.pathTo(5) == stk);
    }
    
    SECTION("3") {
      stk.push(3);
      stk.push(2);
      stk.push(0);
      REQUIRE(bfs.pathTo(3) == stk);
    }
    SECTION("4") {
      stk.push(4);
      stk.push(2);
      stk.push(0);
      REQUIRE(bfs.pathTo(4) == stk);
    }
  }
}

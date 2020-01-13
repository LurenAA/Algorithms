#include "BinarySearchST.hpp"
#include "SequentialSearchST.hpp"
#include "BST.hpp"
#include "RedBlackBST.hpp"
#include <fstream>
#include <iterator>


int main(int argc, char** argv) {
  /**
   * 通用测试
   * 输入一个数字统计长度
   * 大于等于这个数字的字符串
   **/ 
  // if(argc != 2) {
  //   cout << "输入统计字符串的最小长度" << endl;
  //   return 0;
  // } 
  // size_t minLen = atoi(argv[1]);
  // if(minLen <= 0) {
  //   cout << "长度必须为正数" << endl;
  //   return 0;
  // }
  // ifstream in("tale.txt");
  // if(!in.is_open()) {
  //   cout << "打开文件失败" << endl;
  //   return 0;
  // }
  // istream_iterator<string> inIter(in), end;
  // string str;
  
  // BST<string, int> st;
  // while(inIter != end) {
  //   str.assign(*inIter);
  //   if(str.size() >= minLen) {
  //     if(!st.contain(str)) st.put(str, 1);
  //     else st.put(str, st.get(str) + 1);
  //   }
  //   ++inIter;
  // }
  // in.close();
  // st.show();
  
  // /**
  //  * 统计出现次数最多的
  //  **/ 
  // int max = 0, time;
  // string theKey = "";
  // for(auto x : st.keys()) {
  //   time = st.get(x);
  //   if(time > max) {
  //     theKey = x;
  //     max = time;
  //   }
  // }
  // cout << "max: " << theKey << " " << max << endl;

  /**
   * 二叉查找树测试
   **/ 
  // BST<int, int> st;
  // vector<int> vec({12,343,123,123,444,21,142,64,223,676}); //= Common::getInstance()->getRandomVector(10);
  // for(auto x : vec) 
  //   st.put(x,x);
  // st.show();
  // cout << "max, min: " << st.max() << " " << st.min() << endl;
  // cout << "floor, ceiling: " << st.floor(60) << " " << st.ceiling(60) << endl;
  // cout << "select: " << st.select(0)  << " " << st.select(3) << " " << st.select(5) << " " << st.select(9) << endl;
  // cout << "rank: " << st.rank(56) << " " << st.rank(57) << " " << st.rank(58) << endl;
  // // for(int i = 10; i > 1; --i) {
  // //   cout << endl;
  // //   st.deleteMin();
  // //   st.show();
  // //   cout << endl;
  // // }
  // st.delet(343);
  // st.show();

  /**
   * 测试红黑树
   **/ 
  vector<char> test1{'S','E','A','R','C','H','X','M','P','L'};
  vector<char> test2{'A','C','E','H','L','M','P','R','S','X'};
  RedBlackBST<char, char> st1,st2;
  for(size_t i = 0; i < test1.size(); ++i) {
    st1.put(test1[i], test1[i]);
    st2.put(test2[i], test2[i]);
  }
  st1.show();
  // cout << endl;
  // st2.show();
  for(size_t i = 0; i < test2.size(); ++i){
    cout << endl;
    // st1.deleteMin();
    st1.deleteMax();
    st1.show();
  }
  return 1;
}
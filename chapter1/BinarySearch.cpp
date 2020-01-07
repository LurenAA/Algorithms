/**
 * 递归实现的二分查找
 **/ 
#include <vector>
#include <iostream>
using namespace std;

//左闭右开还是左右都是闭区间
int BinarySearch(vector<int>& a,int lo,int ho, int key) {
  // if(lo > ho) return -1;
  // int mid = (lo + ho) / 2;
  // if(a[mid] > key) return BinarySearch(a, lo, mid - 1, key);
  // else if(a[mid] < key) BinarySearch(a, mid + 1, ho, key);
  // else return mid;
  if(lo >= ho) return -1;
  int mid = (lo + ho) / 2;
  if(a[mid] > key) return BinarySearch(a, lo, mid, key);
  else if(a[mid] < key) BinarySearch(a, mid + 1, ho, key);
  else return mid;
}


int main() {
  vector<int> vs{1,2,3,4,12,34,555,1234,5321};
  cout << BinarySearch(vs, 0, vs.size() ,2) << endl;
  cout << BinarySearch(vs, 0, vs.size() ,34) << endl;
  cout << BinarySearch(vs, 0, vs.size() ,324) << endl;
  cout << BinarySearch(vs, 0, vs.size() ,555) << endl;
  return 0;
}
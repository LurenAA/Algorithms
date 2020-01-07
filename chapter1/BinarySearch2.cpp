/**
 * 非递归实现的二分查找
 **/ 
#include <vector>
#include <iostream>
using namespace std;

int BinarySearch(vector<int>& a, int key) {
  int lo = 0,
    ho = a.size(),
  mid;
  while(lo < ho) {
    mid = (lo + ho) / 2;
    if(a[mid] > key) ho = mid;
    else if(a[mid] < key) lo = mid + 1;
    else return mid;
  }
  return -1;
}


int main() {
  vector<int> vs{1,2,3,4,12,34,555,1234,5321};
  cout << BinarySearch(vs, 2) << endl;
  cout << BinarySearch(vs, 34) << endl;
  cout << BinarySearch(vs, 324) << endl;
  cout << BinarySearch(vs, 555) << endl;
  return 0;
}
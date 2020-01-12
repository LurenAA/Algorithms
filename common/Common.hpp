#ifndef __COMMON_HPP
#define __COMMON_HPP
#include <vector>
#include <iostream>
#include <time.h>

class Common {
  public:
  template<class iterator>
  void show(iterator,iterator) const;

  std::vector<int> getRandomVector(int length, uint_fast32_t  seed = time(NULL),bool isSort = false) const; 
  static Common* getInstance();
  private:
  Common() = default;
};

template<class iterator>
void Common::show(iterator begin,iterator end)const {
    auto begin_cp = begin;
    while(begin_cp != end) {
      std::cout << *begin_cp++;
      if(begin_cp != end)
        std::cout << " ";
    }
    std::cout << std::endl;
  }
#endif
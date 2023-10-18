#ifndef basicfunctions_hpp
#define basicfunctions_hpp

#include <iostream>
#include <vector>

namespace util{
  template<typename CollectType, typename ExtraType = CollectType>
  class BasicFunctions{
    public:
    static void print(CollectType c){
      std::cout << c << '\n';
    }

    static void print(ExtraType e){
      std::cout << e << '\n';
    }

    static void toVector(CollectType c, std::vector<CollectType> vec){
      vec.push_back(c);
    }

    static void toVector(ExtraType e, std::vector<ExtraType> vec){
      vec.push_back(e);
    }

    static void toArr(CollectType c, CollectType arr[]){
      int i = 0;
      arr[i] = c;
      i++;
    }

    static void toArr(ExtraType e, ExtraType arr[]){
      int i = 0;
      arr[i] = e;
      i++;
    }
  };
}
#endif
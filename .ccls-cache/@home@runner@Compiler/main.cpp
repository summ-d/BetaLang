#include <iostream>
#include "src/compiler/util/collections/collections.hpp"

int main(void ){ 
  util::string s = "Hello World";

  std::cout << s.asCstr() << '\n';
  
  util::intlist il;
  for(int i = 0; i < 6; i++){
    il.append(i);
  }

  il.forEach([](int i){
    std::cout << i << '\n';
  });

  
  return 0;
  
  
}


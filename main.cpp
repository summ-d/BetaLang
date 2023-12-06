#include <iostream>
#include "src/compiler/util/collections/collections.hpp"

int main(void ){ 
  util::string s = "Hello World";

  std::cout << s.asCstr() << '\n';
  
  return 0;
  
  
}


#ifndef abstractsyntax_hpp
#define abstractsyntax_hpp

#include "collections/collections.hpp"
#include <stdio.h>

namespace util{
  typedef unsigned char u8;
  
  struct TokenDiscriptor{
    Str name;
    u8 type;
    int count = 0;
    static TokenDiscriptor parse(Str s);
  };

  struct Token{
    TokenDiscriptor td;
    Str token;
    
  };  
    
  
  
  
}
  

#endif
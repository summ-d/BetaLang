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

  struct LangToken{
    
  };
  struct Token{
    TokenDiscriptor td;
    Str token;
    
  };


  class TokenDiscriptorScraper{};

  class TokenConstScraper{
    std::ofstream outFile;
    std::ifstream inFile;

    public:
      TokenConstScraper(Str name = "const.tk");

  };  
  
  
  
}
  

#endif
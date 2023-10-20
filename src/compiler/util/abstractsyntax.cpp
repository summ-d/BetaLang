#include "abstractsyntax.hpp"


namespace util{
  
    TokenDiscriptor TokenDiscriptor::parse(Str s){

    }

    TokenConstScraper::TokenConstScraper(Str name){
        outFile.open("typegen/typegen.hpp", std::ios_base::app);
        inFile.open(name.asStdStr());
        if( !outFile.is_open() || 
            !inFile.is_open() || 
            inFile.peek() == inFile.eof()  )
        {
               
        }
        return;
    }


  
}

  


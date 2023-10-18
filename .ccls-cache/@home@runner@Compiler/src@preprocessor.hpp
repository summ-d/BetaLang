#ifndef preprocessor_hpp
#define preprocessor_hpp


#include <fstream>
#include "util/abstractsyntax.hpp"
#include "util/collections/collections.hpp"
#include "util/collections/specialptr.hpp"


typedef struct {
  util::Str errMessage;
  util::
} Error;

typedef struct {
  util::Str line;
  util::Str fileName;
  
} ParsedData;

class Preprocessor{
  util::AbstractSyntax<> syntaxTree;
  util::LinkedList<util::Token> tokenList;
  


  public:
  Preprocessor(util::Str fileName);
  Preprocessor(std::ifstream inputFile);

  void collectLines();

};




#endif
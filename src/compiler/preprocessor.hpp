#ifndef preprocessor_hpp
#define preprocessor_hpp

#include "util/abstractsyntax.hpp"
#include "util/collections/collections.hpp"
#include "util/collections/specialptr.hpp"
#include <fstream>

namespace beta {
typedef struct {
  util::Str errMessage;
  int line;
} Error;

typedef struct {
  util::Str line;
  util::Str fileName;
} ParsedData;

class Logger {
  static util::LinkedList<Error> errors;
  static std::ofstream file;

public:
  static void init(util::Str file = "Log.log");
  static void log(Error e);
  static void print();
};

class Preprocessor {
  util::AbstractSyntax<> syntaxTree;
  util::LinkedList<util::Token> tokenList;

public:
  Preprocessor(util::Str fileName);
  Preprocessor(std::ifstream inputFile);

  util::LinkedList<ParsedData> collectLines(); // for debugging puropses
};
} // namespace beta

#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

typedef uint8_t u8;

struct Token{
  static const u8 UNSPEC{0};
  static const u8 NO_CHILD{1};
  static const u8 ONE_CHILD{2};
  static const u8 TWO_CHILD{3};
  static const u8 THREE_CHILD{4};
  static const u8 FOUR_CHILD{5};
  u8 level;
  string message;
  Token(u8 level, string message){
    this->level = level;
    this->message = message;
  }
  static Token parse(string line){
    string temp;
    istringstream iss(line);
    char lev;
    u8 tpe;
    iss >> temp >> lev;
    switch(lev){
      case 'c':
        tpe = Token::UNSPEC;
      case '0':
        tpe = Token::NO_CHILD;
      case '1':
        tpe = Token::ONE_CHILD;
      case '2':
        tpe = Token::
      case '3':
        
      case '4':
      default:
        break;
    }
    return Token(lev, temp);
  }
};

struct SortedTokens{
  vector<Token> first, second, third, fourth, none, unspec;
};

struct IOError{
  string message;
  IOError(string message, int line){
    this->message = message;
    message.append(to_string(line));
  }
};

class TokenScraper{
  ifstream file;
  public:
  TokenScraper(string filename);
  void parseFile();
  struct SortedTokens sort();
  ~TokenScraper();
};

TokenScraper::TokenScraper(string filename){
  file.open(filename);
  if(!file.is_open() || file.peek() == file.eof()){
    throw new IOError("Cannot open file at line:", __LINE__);
    file.close();
    return;
  }
}

void TokenScraper::parseFile(){
  std::string temp, tkn, lev;
  while(getline(file, temp)){
    
  }
}




#include "tokenizer.hpp"

namespace beta::token{
    
    TokenScraper::TokenScraper(util::Str fileName){
        this->file.open(fileName.asStdStr());
        if(!file.is_open() || file.peek() == file.eof()){
            // IOError e(fileName, "Cannot Open File at", __LINE__);
            // Logger::log(e);
        }
    }

    void TokenScraper::read(){
        util::Str temp;
        while (*temp.getline(file)){
            this->lines.append(temp);
        }
        return;
    }

    util::LinkedList<TokenType> TokenScraper::parseTokens(){
        this->lines.forEach([](util::Str &s){
            toktype_t tok;
            
        });
    }

    TokenScraper::~TokenScraper(){

    }

    ToToken::ToToken(util::LinkedList<util::Str>& linkedList){
        linkedList.forEach([&](util::Str &s){
            this->tokens.append(s);
        });
    }

    void ToToken::parse(){
        this->tokens.forEach([](util::Str &s){
            
        });
    }

    util::LinkedList<Token>& ToToken::toTokens(){

    }

    ToToken::~ToToken(){

    }

}
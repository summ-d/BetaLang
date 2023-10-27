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
        util::LinkedList<TokenType> tokens;
        this->lines.forEach([&tokens](util::Str &s){
            toktype_t tok;
            std::istringstream parser;
            char delim;
            char num;
            parser >> tok.token >> delim >> num;
            switch(num){
                case '0':
                    tok.childNum = Children::NONE;
                    break;
                case '1':
                    tok.childNum = Children::ONE;
                    break;
                case '2':
                    tok.childNum = Children::TWO;
                    break;
                case '3':
                    tok.childNum = Children::THREE;
                    break;
                case '4':
                    tok.childNum = Children::FOUR;
                    break;
                case 'C':
                    tok.childNum = Children::UNSPEC;
                    break;
                default:
                    break;
            }
            tokens.append(tok);
        });
        return tokens;
    }

    TokenScraper::~TokenScraper(){
        file.close();
    }

    ToToken::ToToken(util::LinkedList<util::Str>& linkedList){
        linkedList.forEach([&](util::Str &s){
            this->tokens.append(s);
        });
    }

    // tokenList is the list of tokens.
    // tokens is the list of tokens
    // anatomy of a token:
    // @use JVM;
    // <keyword> <value>

    void ToToken::parse(util::LinkedList<TokenType> tokenList){
        this->tokens.forEach([&tokenList, this](util::Str &s){
            
        });
    }

    util::LinkedList<Token>& ToToken::toTokens(){

    }

    ToToken::~ToToken(){

    }

}
#pragma once
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

    #include "util/collections/collections.hpp"
    #include <sstream>

    namespace beta::token{
        enum Children{
            NONE,
            ONE,
            TWO,
            THREE, 
            FOUR, 
            UNSPEC
        };


        typedef struct TokenType{
            util::Str token;
            Children childNum;
        } toktype_t;

        class TokenScraper{
            std::ifstream file;
            util::LinkedList<util::Str> lines;


            public:
            TokenScraper(util::Str fileName = "tokens.tk");
            void read();
            util::LinkedList<util::Str> expose(){
                return this->lines;
            }
            util::LinkedList<TokenType> parseTokens();
            ~TokenScraper();
        };


        typedef struct Token{
            toktype_t tokenType;
            util::Str token;
        } token_t;
        
        class ToToken{
            util::LinkedList<util::Str> tokens;

            public:
            ToToken(util::LinkedList<util::Str>& linkedList);
            void parse();
            util::LinkedList<Token>& toTokens();
            ~ToToken();
        };

    }


#endif
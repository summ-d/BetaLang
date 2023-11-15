#pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

    #include "tokenizer.hpp"
    #include "globals.hpp"

    namespace beta::lexer{
    
    struct InvalidToken: public err::BaseError{
        token::token_t token;
        void print() const override;  
    };

    struct NoMain: public err::BaseError{
        void print() const override;
        util::string fileName;
    };


    class Lexer{
        util::LinkedList<util::Str> tokens;
        token::TokenList tokenList;
        util::LinkedList<token::TokenType> possibleTokens;
        std::ifstream file;
        token::TokenScraper ts;
        globals::globconfig_t config;

        public:
        Lexer(globals::globconfig_t gc);
        void getTokens();
        void parseToTokens();
        void sortToStart();
        util::LinkedList<util::Str> expose();
        ~Lexer();
    };
    
    }
#endif

#pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

    #include "tokenizer.hpp"
    #include "globals.hpp"

    namespace beta::lexer{
    


    class Lexer{
        util::LinkedList<util::Str> tokens;
        token::TokenList tokenList;
        util::LinkedList<token::TokenType> possibleTokens;
        std::ifstream file;
        token::TokenScraper ts;

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

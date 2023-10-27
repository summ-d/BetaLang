#pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

    #include "tokenizer.hpp"
    #include "typegen/typegen.hpp"

    namespace beta::lexer{
    // Temporary struct to prevent errors
    typedef struct GlobalConfig {
        util::string fileName;
        util::string startPoint;
        util::PossibleArch arch;
    } globconfig_t;
    

    class Lexer{
        util::LinkedList<util::Str> tokens;
        token::TokenList tokenList;
        std::ifstream file;

        public:
        Lexer(globconfig_t gc);
        void getTokens();
        void parseToTokens();
        void sortToStart();
        util::LinkedList<util::Str> expose();
        ~Lexer();
    };
    }

#endif

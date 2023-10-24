#pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

    #include "util/collections/collections.hpp"

    namespace beta::lexer{
    // Temporary struct to prevent errors
    typedef struct GlobalConfig {

    } globconfig_t;
    

    class Lexer{
        util::LinkedList<util::Str> tokens;

        public:
        Lexer(globconfig_t gc);
        void getTokens();
        void sortToStart();
        util::LinkedList<util::Str> expose();
        ~Lexer();
    };
    }

#endif

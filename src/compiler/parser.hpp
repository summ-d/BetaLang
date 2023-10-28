#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include "tokenizer.hpp"

namespace beta::parser{
    enum Keywords{
        PACK,
        IMPORT,
        EXPORT,
        EXTERNAL,
        OBJECT,
        COMPOSITION,
        ABSTRACT,
        CONST,

    };

    typedef struct ParsedToken{
        token::token_t token;
        Keywords type;
    } partok_t;


    typedef struct GlobalConfig{

    } globconfig_t;

    class Parser{
        public:
        Parser(globconfig_t gc);
        

        ~Parser();
    };
}


#endif
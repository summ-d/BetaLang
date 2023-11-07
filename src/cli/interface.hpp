#pragma once
#ifndef COMMANDLINE_HPP
#define COMMANDLINE_HPP

#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

namespace cmd{



    enum Types{
        IN_FILE,
        OUT_FILE,
        FLAG,
        MARKER,
        OTHER
        // Open to make more
    };


    typedef struct Token {
        Types t;
        std::string token;
    } token_t;
    
    typedef std::vector<token_t> TokenLine;

    TokenLine& parse(std::string s);

    class Scraper{

        public:
        Scraper(std::string fileName);

    };

}


#endif
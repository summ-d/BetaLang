#include "lexer.hpp"

namespace beta::lexer{


    Lexer::Lexer(globconfig_t gc){
        file.open(gc.fileName.asStdStr());
        
    }

    void Lexer::getTokens(){

    }

    void Lexer::parseToTokens(){

    }

    void Lexer::sortToStart(){

    }

    util::LinkedList<util::string> Lexer::expose(){

    }

    Lexer::~Lexer(){

    }

}
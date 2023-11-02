#include "lexer.hpp"

namespace beta::lexer{


    Lexer::Lexer(globals::globconfig_t gc){
        file.open(gc.fileName.asStdStr());
        if(!file.is_open() || file.peek() == file.eof()){
            globals::IOError e;
            e.fileName = gc.fileName;
            e.line = 7;
            e.message = "Could Not open file or file is empty";
            err::Logger::log(e);
        }
        ts.read();
    }

    void Lexer::getTokens(){
        util::string temp;
        ts.parseTokens();
        while(*temp.getline(this->file)){
            tokens.append(temp);   
        }
        this->possibleTokens = ts.parseTokens();
    }

    void Lexer::parseToTokens(){
        this->tokens.forEach([this](util::string &s){

        });
    }

    void Lexer::sortToStart(){

    }

    util::LinkedList<util::string> Lexer::expose(){

    }

    Lexer::~Lexer(){
        file.close();
    }

}
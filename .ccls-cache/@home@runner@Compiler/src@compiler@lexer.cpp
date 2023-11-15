#include "lexer.hpp"

namespace beta::lexer{

    void InvalidToken::print() const{
        std::cout << "Error at:" << this->line << ".";
    }

    void NoMain::print() const{
        std::cout << "No Main Function in file\n";
    }


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
           this->possibleTokens.forEach([this, &s](token::TokenType &token){
                token::token_t tok;
                if(util::strcmp(s.asCstr(), token.token.asCstr())){
                    tok.token = s;
                    tok.tokenType.childNum = token.childNum;
                    tok.tokenType.token = token.token;
                } else {
                    tok.token = s;
                    InvalidToken ivt;
                    ivt.line = __LINE__;
                    ivt.message = "Invalid Token";
                    ivt.token.token = tok.token;
                    err::Logger::log(ivt);
                }
                this->tokenList.append(tok);
           }); 
        });
    }

    void Lexer::sortToStart(){
        util::LinkedList<token::token_t> tempOne;
        util::LinkedList<token::token_t> tempTwo;
        this->tokenList.forEach([this, &tempTwo, &tempOne](token::token_t &token){
            if(util::strcmp(token.token.asCstr(), config.startPoint.asCstr()) && !config.startPoint.isEmpty()){
                tempTwo.append(token);
            }
            tempOne.append(token);
        });
        if(tempTwo.isEmpty()){
            NoMain nm;
            nm.fileName = config.fileName;
            nm.line = __LINE__;
            nm.message = "No Main Function in Non-Module File";
            err::Logger::log(nm);
        }
        token::token_t temporary;
        temporary.token = config.startPoint;
        this->tokenList.forEach([&temporary](token::token_t &token){
            
        });
    }

    util::LinkedList<util::string> Lexer::expose(){

    }

    Lexer::~Lexer(){
        file.close();
    }

}
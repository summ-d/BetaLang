#include "preprocessor.hpp"

namespace beta::preproc{

    const util::string Preprocessor::possible[] = {"@start", "@use", "@include", "@def", "@end", "@eval", "@alias"};

    inline Types get(int i){
        switch(i){
           case 0:
                return Types::ATSTART;
                break;
            case 1:
                return Types::ATUSE;
                break;
            case 2:
                return Types::ATINCLUDE;
                break;
            case 3:
                return Types::ATDEF;
                break;
            case 4:
                return Types::ATEND;
                break;
            case 5:
                return Types::ATEVAL;
                break;
            case 6:
                return Types::ATALIAS;
                break;
            default:
                break;
        }
        return;
    }


Preprocessor::Preprocessor(util::string fileName){
    try {
        createAndCheck(fileName);
    }
    catch(IOError e) {
        util::Logger::log(e);
    }
    
}

void Preprocessor::scanTokens(){
    util::string str;
    while(*str.getline(inFile, ' ')){
        if(str[0] == '@'){
            int i = 0;
            for (i = 0; i < 6; i++){
                if(util::strcmp(possible[i].asCstr(), str.asCstr())){
                    token_t token;
                    token.token = str;
                    
                }
            }
            
        }
    }
    return;
}

void Preprocessor::evaluate(){}

std::ofstream& Preprocessor::getGeneratedFile(){

}

util::LinkedList<util::string> Preprocessor::expose(){

}

Preprocessor::~Preprocessor(){

}


} // namespace beta

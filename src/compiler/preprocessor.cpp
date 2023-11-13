#include "preprocessor.hpp"

namespace beta::preproc{

<<<<<<< HEAD
    EvalDiscriptor parseExpession(pproc_t existing, util::string expression){
        evdis_t ed = (evdis_t)existing;
        
        return ed;
    }

    util::RelationalMap<globals::objdis_t, long> parseExternal(util::string external){
        
    }

    Preprocessor::Preprocessor(util::string fileName){
        file.open(fileName.asStdStr());
        if(!file.is_open() || file.peek() == file.eof()){
            globals::ioerr_t error;
            error.fileName = fileName;
            error.line = __LINE__;
            error.message = "Error Opening File";
            err::Logger::log(&error);
=======
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
>>>>>>> 1a8c0bd77e0e3c889cce2034e37a4bfc0f7fcd9f
        }
        return;
    }

<<<<<<< HEAD
    void Preprocessor::parseLines(){
        util::string temp;
        while(*temp.getline(file)){
            lines.append(temp);
        }
        
        for(int i = 0; i < lines.getSize(); i++){
            this->wrds.append(util::parse(lines[i]));
        }
    }

    void Preprocessor::checkForMarker(char marker){
        long length = 0;
        for(int i = 0; i < wrds.getSize(); i++){
            for(int j = 0; j < wrds[i].getSize(); i++){
                length += wrds[i].getAt(j).getSize();
                if(wrds[i].getAt(j)[0] == marker){
                    occurances.append(wrds[i].getAt(j), length);
                    switch(this->parse(wrds[i].getAt(j))){
                        case 0: case 2: case 5:
                            if(wrds[i].isLast(wrds[i].nodeAt(j))){
                                expressions.append(wrds[i + 1].getAt(0), wrds[i + 1].getAt(0).getSize() + length);
                                if(wrds[i + 1].getAt(0)[wrds[i + 1].getAt(0).getSize() - 1] != ';'){
                                    globals::unexerr_t error;
                                    error.filePos = length + (wrds[i + 1].getAt(0).getSize() - 1);
                                    error.line = __LINE__;
                                    error.message = "Expected Semicolon";
                                    err::Logger::log(&error);
                                }
                            } else{
                                expressions.append(wrds[i].getAt(j + 1), length);
                            }
                            break;
                        case 1: case 7:
                            if(wrds[i].isLast(wrds[i].nodeAt(j))){
                                util::string temp = wrds[i + 1].getAt(0);
                                if(wrds[i + 1].isLast(wrds[i + 1].nodeAt(0))){
                                    temp.concat(wrds[i + 2].getAt(0));
                                    expressions.append(temp, length);
                                    if(temp[temp.getSize() - 1] != ';'){
                                        globals::unexerr_t error;
                                        error.filePos = length + (temp.getSize() - 1);
                                        error.line = __LINE__;
                                        error.message = "Expected Semicolon";
                                        err::Logger::log(&error);
                                    }
                                }
                            } else{
                                util::string temp = wrds[i][j + 1];
                                temp.concat(wrds[i][j + 2]);
                                expressions.append(temp, length + temp.getSize());
                            }
                            break;
                        case 3: case 6:
                            int countV = 0;
                            int countH = 0;
                            util::string temp;
                            while(util::strcmp(wrds[i + countH][j + countV].asCstr(), "@end") != true && !wrds[i + countH].isLast(wrds.nodeAt(countH + i))){
                                temp.concat(wrds[i + countH][j + countV]);
                                expressions.append(temp, length + temp.getSize());
                                if(wrds[i].isLast(wrds[i + countH].nodeAt(j + countV))){
                                    countH++;
                                }
                                countV++;
                            }
                            break;
                        case 4:
                            break;
                        case 8:
                            // TODO: come up with way to not die doing this
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void Preprocessor::parseToTokens(){
        for(int i = 0; i < occurances.size(); i++){
            pproc_t ppt;
            int startCount = 0;
            switch(this->parse(occurances[i].dataOne)){
                case 0:
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_USE;
                    ppt.semi = ';';
                    udis_t ud = (udis_t)ppt;
                    ud.arch = this->parseArch(expressions[i].dataOne);
                    tokens.append(ud, occurances[i].dataTwo);
                    break;
                case 1:
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_ALIAS;
                    ppt.semi = ';';
                    adis_t ad = (adis_t)ppt;
                    ad.type = util::parse(expressions[i].dataOne)[0];
                    ad.alias = util::parse(expressions[i].dataOne)[1];
                    tokens.append(ad, occurances[i].dataTwo);
                    break;
                case 2:
                    ppt.fullToken = occurances[i].dataOne;
                    gc.startPoint = expressions[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_START;
                    ppt.semi = ';';
                    sdis_t sd = (sdis_t)ppt;
                    sd.startPoint = expressions[i].dataOne;
                    tokens.append(sd, occurances[i].dataTwo);
                    if(startCount > 0){
                        // Throw error
                    }
                    startCount++;
                    break;
                case 3:
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_EVAL;
                    ppt.semi = ';';
                    evdis_t edis = parseExpession(ppt, expressions[i].dataOne);
                    tokens.append(edis, occurances[i].dataTwo);
                    break;
                case 4:
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_END;
                    ppt.semi = ';';
                    tokens.append(ppt, occurances[i].dataTwo);
                    break;
                case 5:
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_INCLUDE;
                    ppt.semi = ';';
                    indis_t id = (indis_t)ppt;
                    id.includeFn = occurances[i].dataOne;
                    tokens.append(id, occurances[i].dataTwo);
                    break;
                case 6:
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_EXTERNAL;
                    ppt.semi = ';';
                    extdis_t exdis = (extdis_t)ppt;
                    
                    break;
                case 7:
                    break;
                case 8:
                    break;
                default: 
                    break;
            }
        }  
    }

}
=======

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
>>>>>>> 1a8c0bd77e0e3c889cce2034e37a4bfc0f7fcd9f

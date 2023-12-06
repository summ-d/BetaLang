#include "preprocessor.hpp"

namespace beta{
namespace preproc{

    EvalDiscriptor parseExpession(pproc_t existing, util::string expression){
     //TODO 
      EvalDiscriptor edis; 
    }



    util::RelationalMap<globals::objdis_t, long> parseExternal(util::string external){
        
    }

    util::RelationalMap<util::string, globals::Type> parseTemplate(util::string args){
      util::stringlist sl = util::parse(args, '(');  
      util::RelationalMap<util::string, globals::Type> map;
      map.append(sl[0], globals::Type::DEFUN);
      util::stringlist sl2 = util::parse(sl[1], ',');
      for(int i = 0; i < sl2.getSize(); i++){
        map.append(sl2[i], globals::getType(util::parse(sl2[i])[1]));
      }
      return map;
    }

    Preprocessor::Preprocessor(util::string fileName){
        file.open(fileName.asStdStr());
        if(!file.is_open() || file.peek() == file.eof()){
            globals::ioerr_t error;
            error.fileName = fileName;
            error.line = __LINE__;
            error.message = "Error Opening File";
            err::Logger::log(&error);
        }
        return;
    }

    void Preprocessor::parseLines(){
        util::string temp;
        while(*temp.getline(file)){
            lines.append(temp);
        }

        for(int i = 0; i < lines.getSize(); i++){
            if(lines[i][0] == '/' && lines[i][1] == '/') continue;
            this->wrds.append(util::parse(lines[i]));
        }
    }

    void Preprocessor::checkForMarker(char marker){
        for(int i = 0; i < wrds.getSize(); i++){
            for(int j = 0; j < wrds[i].getSize(); i++){
                this->length += wrds[i].getAt(j).getSize();
                if(wrds[i].getAt(j)[0] == marker){
                    occurances.append(wrds[i].getAt(j), this->length);
                    switch(this->parse(wrds[i].getAt(j))){
                        case 0: case 2: case 5:
                            if(wrds[i].isLast(wrds[i].nodeAt(j).get())){
                                expressions.append(wrds[i + 1].getAt(0), wrds[i + 1].getAt(0).getSize() + this->length);
                                if(wrds[i + 1].getAt(0)[wrds[i + 1].getAt(0).getSize() - 1] != ';'){
                                    globals::unexerr_t error;
                                    error.filePos = this->length + (wrds[i + 1].getAt(0).getSize() - 1);
                                    error.line = __LINE__;
                                    error.message = "Expected Semicolon";
                                    err::Logger::log(&error);
                                }
                            } else{
                                expressions.append(wrds[i].getAt(j + 1), this->length);
                            }
                            break;
                        case 1: case 7:
                            if(wrds[i].isLast(wrds[i].nodeAt(j).get())){
                                util::string temp = wrds[i + 1].getAt(0);
                                if(wrds[i + 1].isLast(wrds[i + 1].nodeAt(0).get())){
                                    temp.concat(wrds[i + 2].getAt(0));
                                    expressions.append(temp, this->length);
                                    if(temp[temp.getSize() - 1] != ';'){
                                        globals::unexerr_t error;
                                        error.filePos = this->length + (temp.getSize() - 1);
                                        error.line = __LINE__;
                                        error.message = "Expected Semicolon";
                                        err::Logger::log(&error);
                                    }
                                }
                            } else{
                                util::string temp = wrds[i][j + 1];
                                temp.concat(wrds[i][j + 2]);
                                expressions.append(temp, this->length + temp.getSize());
                            }
                            break;
                        case 3: case 6: {
                            int countV = 0;
                            int countH = 0;
                            util::string temp;
                            while(util::strcmp(wrds[i + countH][j + countV].asCstr(), "@end") != true && !wrds[i + countH].isLast(wrds[i].nodeAt(countH + i).get())){
                                temp.concat(wrds[i + countH][j + countV]);
                                expressions.append(temp, this->length + temp.getSize());
                                if(wrds[i].isLast(wrds[i + countH].nodeAt(j + countV).get())){
                                    countH++;
                                }
                                countV++;
                            }
                            break;
                          }  
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
                case 0: {
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = occurances[i].dataOne[0];
                    ppt.t = Type::AT_USE;
                    ppt.semi = occurances[i].dataOne[occurances[i].dataOne.findFirst(';').unwrap()];
                    udis_t ud = *(udis_t*)&ppt;
                    ud.arch = this->parseArch(expressions[i].dataOne);
                    tokens.append(&ud, occurances[i].dataTwo);
                    break;
                }
                case 1:{
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = occurances[i].dataOne[0];
                    ppt.t = Type::AT_ALIAS;
                    ppt.semi = occurances[i].dataOne[occurances[i].dataOne.findFirst(';').unwrap()];
                    adis_t ad = *(adis_t*)&ppt;
                    ad.type = util::parse(expressions[i].dataOne)[0];
                    ad.alias = util::parse(expressions[i].dataOne)[1];
                    tokens.append(&ad, occurances[i].dataTwo);
                    break;
                }
                case 2: {
                    //TODO: Also Do checks on NO_START
                    ppt.fullToken = occurances[i].dataOne;
                    gc.startPoint = expressions[i].dataOne;
                    ppt.marker = occurances[i].dataOne[0];
                    ppt.t = Type::AT_START;
                    ppt.semi = ';';
                    sdis_t sd = *(sdis_t*)&ppt;
                    sd.startPoint = expressions[i].dataOne;
                    tokens.append(&sd, occurances[i].dataTwo);
                    if(startCount > 0){
                        // Throw error
                    }
                    startCount++;
                    break;
                  }
                case 3: {
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_EVAL;
                    ppt.semi = ';';
                    evdis_t edis = parseExpession(ppt, expressions[i].dataOne);
                    tokens.append(&edis, occurances[i].dataTwo);
                    break;
                }
                case 4: {
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_END;
                    ppt.semi = ';';
                    tokens.append(&ppt, occurances[i].dataTwo);
                    break;
                  }
                case 5: {
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_INCLUDE;
                    ppt.semi = ';';
                    indis_t id = *(indis_t*)&ppt;
                    id.includeFn = occurances[i].dataOne;
                    tokens.append(&id, occurances[i].dataTwo);
                    break;
                  }    
                case 6: {
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_EXTERNAL;
                    ppt.semi = ';';
                    extdis_t exdis = *(extdis_t*)&ppt;
                    util::stringlist temp = util::parse(expressions[i].dataOne);
                    exdis.fileName = temp[0];
                    exdis.endDirective = temp.getBack();
                    exdis.startPosition = occurances[i].dataTwo;
                    exdis.endPosition = expressions[i].dataTwo;
                    tokens.append(&exdis, occurances[i].dataTwo);
                    break;
                  }  
                case 7: {
                    ppt.fullToken = occurances[i].dataOne;
                    ppt.marker = '@';
                    ppt.t = Type::AT_DEFINE;
                    ppt.semi = ';';
                    defdis_t defdis = *(defdis_t*)&ppt;
                    defdis.name = util::parse(expressions[i].dataOne)[0];
                    defdis.value = util::parse(expressions[i].dataOne)[1];
                    tokens.append(&defdis, occurances[i].dataTwo);
                    break;
                  }
                case 8:{
                  ppt.fullToken = occurances[i].dataOne;
                  ppt.marker = occurances[i].dataOne[0];
                  ppt.t = Type::AT_DEFUN;
                  ppt.semi = expressions[i].dataOne[expressions[i].dataOne.findFirst("@end;").unwrap() + 3];
                  // Dereferecing a cast from a refernce of the paent struct to a pointer of the child struct
                  atdef_t atdef = *(atdef_t*)&ppt;
                  atdef.args = util::RelationalMap<util::string, globals::Type> (parseTemplate(util::parse(expressions[i].dataOne, '\n')[0]));
                  atdef.children = util::RelationalMap<globals::bdis_t, long>(globals::parseBasic(util::parse(expressions[i].dataOne, '\n')));
                  atdef.colon = expressions[i].dataOne[expressions[i].dataOne.findFirst(':').unwrap()];
                  atdef.endDir = expressions[i].dataOne.substr(expressions[i].dataOne.findFirst((char*)"@end").unwrap(), 4);
                  atdef.type = globals::Type::DEFUN;
                  int ref = expressions[i].dataOne.findAll((char*)"=>")[0];
                  atdef.retType = globals::getType(expressions[i].dataOne.substr(ref + 2));
                  tokens.append(&atdef, occurances[i].dataTwo);
                  break;
                }
                default:
                    break;
            }
        }
        this->checkFlags();  
    }

    void Preprocessor::checkFlags(){
       for(int i = 0; i < this->lines.getSize(); i++){
            if(lines[i].startsWith("[!@")){
                flag_t flag;
                flag.total = lines[i];
                flag.starting = lines[i].substr(0, 3);
                flag.closingBracket = lines[i][lines[i].lastPos() - 1];
                flag.semi = lines[i][lines[i].lastPos()];
                this->flags.append(flag, this->length + lines[i].getSize());
            }
       }
    }

    void Preprocessor::evaluate(){
        for(int i = 0; i < this->tokens.size(); i++){
           pproc_t* currentToken = this->tokens[i].dataOne;
           long pos = this->tokens[i].dataTwo; 
           // For Eval Blocks
           if(evdis_t* eval = static_cast<evdis_t*>(currentToken)){
                double numberOne = this->getNumber(std::get<util::string>(eval->operandOne));
                double numberTwo = this->getNumber(std::get<util::string>(eval->operandTwo));
                switch(eval->op){
                    case Operators::EQUALS:
                        eval->value = (numberOne == numberTwo);
                        break;
                    case Operators::GREATER_THAN:
                        eval->value = (numberOne > numberTwo);
                        break;
                    case Operators::GREATER_THAN_OR_EQUAL:
                        eval->value = (numberOne >= numberTwo);
                        break;
                    case Operators::LESS_THAN_OR_EQUAL:
                        eval->value = (numberOne <= numberTwo);
                        break;
                    case Operators::LESS_THAN:
                        eval->value = (numberOne < numberTwo);
                    case Operators::NOT_EQUAL:
                        eval->value = (numberOne != numberTwo);
                    default:
                        break;
                }
                // TODO: Change these to pointers
                tokens.after(eval, pos, i); 
           }
           // For External Blocks
           // Forgive me
           if(extdis_t* exdis = static_cast<extdis_t*>(currentToken)){
               
           } 
        }
    }
  }
}
#pragma once
#ifndef preprocessor_hpp
#define preprocessor_hpp

#include "util/abstractsyntax.hpp"
#include "util/collections/collections.hpp"
#include "util/collections/special/specialptr.hpp"
#include "util/sfine/structchecker.hpp"
#include "globals.hpp"
#include <fstream>
//TODO: Make own implementation
#include <tuple>
#include<iostream>

namespace beta{
namespace preproc {

    enum Type{
        AT_ALIAS,
        AT_START,
        AT_EVAL,
        AT_END,
        AT_INCLUDE,
        AT_EXTERNAL,
        AT_DEFINE,
        AT_USE,
        AT_DEFUN
    };

    enum Operators{
        EQUALS,
        GREATER_THAN,
        LESS_THAN,
        GREATER_THAN_OR_EQUAL,
        LESS_THAN_OR_EQUAL,
        NOT_EQUAL
    };


    typedef struct PreprocToken{
        char marker;
        util::string fullToken;
        //util::string expression;
        char semi;
        Type t;
    } pproc_t;

    typedef struct UseDiscriptor: public PreprocToken{
        util::PossibleArch arch;
        typedef long use_t;
    } udis_t;

    typedef struct AliasDescriptor: public PreprocToken{
        util::string type;
        util::string alias;
        typedef float alias_t;
    } adis_t;

    typedef struct StartDesciptor: public PreprocToken{
        util::string startPoint;
        typedef char start_t;
    } sdis_t;

    util::string possibleOp[6] = {
      "==",
      ">"
      "<"
      ">=",
      "<="
      "!="
    };
  
    Operators parseOp(util::string op){
        int i;
        for(i = 0; i < 6; i++) if(util::strcmp(possibleOp[i].asCstr(), op.asCstr())) break;
        switch (i){
          case 0:
            return Operators::EQUALS;
          case 1:
            return Operators::GREATER_THAN;
          case 3:
            return Operators::GREATER_THAN_OR_EQUAL;
          case 4:
            return Operators::LESS_THAN_OR_EQUAL;
          case 2:
            return Operators::LESS_THAN;
          case 5:
            return Operators::NOT_EQUAL;
          default:
            break;
        }
    }
  
    typedef struct EvalDiscriptor: public PreprocToken{
        char openPar;
        std::tuple<util::string, globals::Type> operandOne;
        std::tuple<util::string, globals::Type> operandTwo;
        util::string oper;
        Operators op;
        char endPar;
        char colon;
        typedef int eval_t;
        bool value;
    } evdis_t;

    typedef struct DefDiscriptor: public PreprocToken{
      typedef long long def_t;
      util::string name;
      util::string value;
      globals::Type t;
    } defdis_t;

    EvalDiscriptor parseExpession(pproc_t existing, util::string expression);

    typedef struct IncludeDescriptor: public PreprocToken {
        util::string includeFn;
        typedef bool include_t;
    } indis_t;

    typedef struct ExternalDescriptor: public PreprocToken{
        util::string fileName;
        util::string endDirective;
        long startPosition;
        long endPosition;
        util::RelationalMap<util::string, long> parsedString;
        util::RelationalMap<globals::objdis_t, long> children;
        typedef double extern_t;
    } extdis_t;

    util::RelationalMap<globals::objdis_t, long> parseExternal(util::string external);

    typedef struct PreDefunDescriptor: public globals::FunctionDescriptor, PreprocToken{
      util::RelationalMap<util::string, globals::Type> args;
      util::string endDir;
      char colon;
      util::RelationalMap<globals::bdis_t, long> children;
    } atdef_t;

    util::RelationalMap<util::string, globals::Type> parseTemplate(util::string args);

    typedef struct FlagDescriptor{
        util::string total;
        util::string starting;
        util::string flag;
        char closingBracket;
        char semi;
    } flag_t;

    class Preprocessor{
        long length;
        util::stringlist lines;
        util::RelationalMap<flag_t, long> flags;
        util::LinkedList<util::stringlist> wrds;
        util::RelationalMap<util::string, long> occurances;
        util::RelationalMap<util::string, long> expressions;
        util::RelationalMap<pproc_t*, long> tokens;
        util::RelationalMap<util::DummyInheriter, long> tokenCheckers;
        std::ifstream file;
        globals::globconfig_t gc;
        globals::finfo_t info;

        util::string possible[9] = {
            "@use", // 0
            "@alias", // 1
            "@start", // 2
            "@eval", // 3
            "@end", // 4
            "@include", // 5
            "@external", // 6
            "@def", // 7
            "@defun" // 8
        };

        util::string possibleArch[8] = {
            "ARM",
            "AVR",
            "x86_64",
            "x86",
            "JVM",
            "MIPS",
            "RISC-V",
            "MSIL"
        };

        int parse(util::string str){
            for(int i = 0; i < 9; i++){
                if(util::strcmp(possible[i].asCstr(), str.asCstr())){
                    return i;
                }
            }
            return -1;   
        }

        double loopAndCompare(util::string keyword){
            for(int i = 0; i < tokens.size(); i++){
                if(defdis_t* temp = static_cast<defdis_t*>(tokens[i].dataOne)){
                    if(temp->value.isNumber() && util::strcmp(keyword.asCStr(), temp->name.asCStr())){
                        return temp->value.getNumber();
                    }
                }
            }
            // TODO: Some better exit code failure
            return 0;
        }

        double getNumber(util::string number){
            if(!number.isNumber()){
                return loopAndCompare(number);
            }
            return number.getNumber();
        }

        util::PossibleArch parseArch(util::string str){
            util::PossibleArch a;
            int i = 0;
            for(i = 0; i < 7; i++){
                if(util::strcmp(possible[i].asCstr(), str.asCstr())){
                    break;
                }
            }
            switch(i){
                case 0:
                    a = util::PossibleArch::ARM;
                case 1:
                    a = util::PossibleArch::AVR;
                case 2:
                    a =  util::PossibleArch::X86_64;
                case 3:
                    a =  util::PossibleArch::X86;
                case 4:
                    a= util::PossibleArch::JVM;
                case 5:
                    a= util::PossibleArch::MIPS;
                case 6:
                    a = util::PossibleArch::RISC;
                case 7:
                    a = util::PossibleArch::MSIL;
                default:
                    break;
            }
            a =  util::PossibleArch::ERROR;
            return a;
        }
  

        public:
        Preprocessor(util::string fileName);
        void parseLines();
        void checkForMarker(char marker);
        void parseToTokens();
        void checkFlags();
        void evaluate();
        void replace();
        util::LinkedList<pproc_t> expose();
        globals::globconfig_t returnGlobal();
        ~Preprocessor();
    };
}
} // namespace beta

#endif
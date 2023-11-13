#pragma once
#ifndef preprocessor_hpp
#define preprocessor_hpp

<<<<<<< HEAD
#include "util/abstractsyntax.hpp"
#include "util/collections/collections.hpp"
#include "util/collections/special/specialptr.hpp"
#include "util/sfine/structchecker.hpp"
#include "globals.hpp"
#include <fstream>

namespace beta::preproc {

    enum Type{
        AT_ALIAS,
        AT_START,
        AT_EVAL,
        AT_END,
        AT_INCLUDE,
        AT_EXTERNAL,
        AT_USE
    };

    enum Operators{
        EQUALS,
        GREATER_THAN,
        LESS_THAN,
        GREATER_THAN_OR_EQUAL,
        LESS_THAN_OR_EQUAL,
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

    typedef struct EvalDiscriptor: public PreprocToken{
        char openPar;
        util::string operandOne;
        util::string operandTwo;
        Operators op;
        char endPar;
        char colon;
        typedef int eval_t;
    } evdis_t;

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
        util::RelationalMap<globals::objdis_t, long> children;
        typedef double extern_t;
    } extdis_t;

    util::RelationalMap<globals::objdis_t, long> parseExternal(util::string external);

    class Preprocessor{
        util::stringlist lines;
        util::LinkedList<util::stringlist> wrds;
        util::RelationalMap<util::string, long> occurances;
        util::RelationalMap<util::string, long> expressions;
        util::RelationalMap<pproc_t, long> tokens;
        util::RelationalMap<util::DummyInheriter, long> tokenCheckers;
        std::ifstream file;
        globals::globconfig_t gc;

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

        util::string possibleArch[7] = {
            "ARM",
            "AVR",
            "x86_64",
            "x86",
            "JVM",
            "MIPS",
            "RISC-V"
        };

        int parse(util::string str){
            for(int i = 0; i < 9; i++){
                if(util::strcmp(possible[i].asCstr(), str.asCstr())){
                    return i;
                }
            }
            return -1;   
        }

        util::PossibleArch parseArch(util::string str){
            int i = 0;
            for(i = 0; i < 6; i++){
                if(util::strcmp(possible[i].asCstr(), str.asCstr())){
                    break;
                }
            }
            switch(i){
                case 0:
                    return util::PossibleArch::ARM;
                case 1:
                    return util::PossibleArch::AVR;
                case 2:
                    return util::PossibleArch::X86_64;
                case 3:
                    return util::PossibleArch::X86;
                case 4:
                    return util::PossibleArch::JVM;
                case 5:
                    return util::PossibleArch::MIPS;
                case 6:
                    return util::PossibleArch::RISC;
                default:
                    break;
            }
            return util::PossibleArch::ERROR;
=======
#include "util/collections/logger.hpp"


namespace beta::preproc {

    enum Types{
        ATSTART,
        ATUSE,
        ATINCLUDE,
        ATDEF,
        ATEND,
        ATEVAL,
        ATALIAS
    };

        
    typedef struct IOError: public util::BaseError{
        util::string fileName;
        IOError() = default;
        IOError(util::string filename, util::string message, int line);
    } ioerr_t;

    typedef struct Token{
        util::string token;
        Types type;
    } token_t;
    typedef struct GlobalConfig{
        util::u8 archType;
        util::string startPoint;
    } globconfig_t;

    class Preprocessor{
        std::ofstream outfile;
        std::ifstream inFile;
        util::LinkedList<util::string> tokens;

        static const util::string possible[7];

        void createAndCheck(util::string fileName){
            inFile.open(fileName.asStdStr());
            if(!inFile.is_open() || inFile.peek() == inFile.eof()){
                throw new IOError(fileName, "could not open file at line", __LINE__);
            }
            return;
>>>>>>> 1a8c0bd77e0e3c889cce2034e37a4bfc0f7fcd9f
        }

        public:
        Preprocessor(util::string fileName);
<<<<<<< HEAD
        void parseLines();
        void checkForMarker(char marker);
        void parseToTokens();
        void evaluate();
        util::LinkedList<pproc_t> expose();
        globals::globconfig_t returnGlobal();
        ~Preprocessor();

=======
        void scanTokens();
        void evaluate();
        std::ofstream& getGeneratedFile();
        util::LinkedList<util::string> expose();
        ~Preprocessor();
>>>>>>> 1a8c0bd77e0e3c889cce2034e37a4bfc0f7fcd9f
    };


} // namespace beta

#endif
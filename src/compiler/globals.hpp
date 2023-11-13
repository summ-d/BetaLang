#pragma once
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "collections/collections.hpp"
#include "typegen/typegen.hpp"
#include "errors.hpp"


namespace beta::globals {

    typedef struct GlobalConfig {
        util::string fileName;
        util::string startPoint;
        util::PossibleArch arch;  
    } globconfig_t;
    
    typedef struct IOError: public virtual err::BaseError{
        util::string fileName; 
        void print() const override{
            std::cout << "error Opening File:" << this->raw
            << "info:\n" << "Line:" << this->line << '\n' << "Message:"  
            << this->rawTwo << '\n';
        }
        private:
            const char* raw = fileName.asCstr();
            const char* rawTwo = message.asCstr();
    } ioerr_t;

    typedef struct UnterminatedExpressionError: public virtual err::BaseError{
        void print() const override{
            std::cout << "Error on parsing file:" << this->line
            << "Info:\n" << "File Position:" << this->filePos << '\n' << "Message:"
            << this->raw << '\n'; 
        }
        
        long filePos;

        private:
        const char* raw = message.asCstr();
    } unexerr_t;

    typedef struct ObjTypeDiscriptor{

    } objdis_t;

    enum Type{
        INTEGER, //1
        INT8, //2
        INT16,//3
        INT32,//4
        INT64,//5
        INTMAX,//21
        UINT8,//6
        UINT16,//7
        UINT32,//8
        UINT64,//9
        UINTMAX,//22
        FLOAT,//10
        FLOAT8, //11
        FLOAT16,//12
        FLOAT32,//13
        FLOAT64,//14
        FLOMAX,//23
        BOOLEAN,//15
        STRING,//16
        CHAR,//17
        OBJECT,//18
        COMPOSITION,//19
        DEFUN,//20
        VOID,//24
        UNKNOWN
    };

    enum Qualifiers{
        ASYNC,
        STATIC,
        CONST,
        VOLATILE,
        CONSTEXPR,
        RESTRICT, // Hint
        REGISTER, // Hint
        PUB,
        PRIV,
        PROP
    };

    typedef struct BasicDescriptor{
        util::RelationalMap<Qualifiers, int> qualifiers;
        Type type;
        util::string name;
        util::string expression;
        util::string assignment;
        int ptrs;
        int refs;
    } bdis_t;


    typedef struct FunctionDescriptor: BasicDescriptor{
        util::RelationalMap<bdis_t, long> children;
        int bracketCount;
        util::RelationalMap<Type, util::string> args;
        char openParen;
        char closedParen;
        char semiOrBreacket;
        char closingBracket;
        Type retType;
    } fdis_t;


    util::string possTypes[24] = {
        "Integer", //0
        "Int8",//1
        "Int16",//2
        "Int32",//
        "Int64",//3
        "IntMax",//4
        "Uint8",//5
        "Uint16",//6
        "Uint32",//7
        "Uint64",//8
        "UintMax",//9
        "Float",//10
        "Flo8",//11
        "Flo16",//12
        "Flo32",//13
        "Flo64",//14
        "FloMax",//15
        "Boolean",//16
        "String",//17
        "Char",//18
        "Obj",//19
        "Comp",//20
        "defun",//21
        "Void"//22
    };

    util::string posQual[10] = {
        "async",
        "static",
        "const",
        "volatile",
        "constexpr",
        "restrict",
        "register",
        "pub",
        "priv",
        "prop"
    };


    Type getType(util::string str){
        int i;
        for(i = 0; i < 23; i++) if(util::strcmp(str.asCstr(), possTypes[i].asCstr())) break;
        switch (i){
            case 0: return Type::INTEGER;
            case 1: return Type::INT8;
            case 2: return Type::INT16;
            case 3: return Type::INT32;
            case 4: return Type::INT64;
            case 5: return Type::INTMAX;
            case 6: return Type::UINT8;
            case 7: return Type::UINT16;
            case 8: return Type::UINT32;
            case 9: return Type::UINT64;
            case 10: return Type::UINTMAX;
            case 11: return Type::FLOAT;
            case 12: return Type::FLOAT8;
            case 13: return Type::FLOAT16;
            case 14: return Type::FLOAT32;
            case 15: return Type::FLOAT64;
            case 16: return Type::FLOMAX;
            case 17: return Type::BOOLEAN;
            case 18: return Type::STRING;
            case 19: return Type::CHAR;
            case 20: return Type::OBJECT;
            case 21: return Type::COMPOSITION;
            case 22: return Type::DEFUN;
            case 23: return Type::VOID;
            default:
                return Type::UNKNOWN;
        }
    }

    util::RelationalMap<Qualifiers, int> parseQual(util::string str){
        util::stringlist sl = util::parse(str);
        for(int i = 0; i < sl.getSize(); i++){
            if(util::strcmp(sl[i].asCstr(), "pub") && i != 0){

            }
        }
    }

    

    fdis_t funcParse(util::string line, bdis_t bd){
        fdis_t fd = (fdis_t)bd;
        util::stringlist tokens = util::parse(line, ' ');
        fd.name = tokens[0].substr(0, '(');
        //fd.args.append();
    }

} // namespace beta::globals


#endif

#ifndef logger_hpp
#define logger_hpp

#include "collections.hpp"
#include <iostream>

namespace util{

typedef struct{
    Str name;
    int line;   
} BaseError;

class Logger{
    static LinkedList<BaseError> errs;

    public:
    static void log(BaseError e);

    static void print();
};

void Logger::log(BaseError e){
    Logger::errs.append(e);
}

void Logger::print(){
    Logger::errs.forEach([](const BaseError& be){
        std::cout << be.name << "at:" << be.line << "\n";
    });
}

}


#endif
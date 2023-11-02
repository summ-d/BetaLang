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
            std::cout << "error: " << this->message 
            << "At Line:" << this->line 
            << "Opening: " << this->fileName << "\n";
        }
    };


} // namespace beta::globals


#endif

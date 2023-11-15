#pragma once
#ifndef COMPILERBASE_HPP
#define COMPILERBASE_HPP

    #include "compiler/preprocessor.hpp"


    namespace beta{
        preproc::Preprocessor* preprocessorInvokation;



        void preprocess(util::string fileName);

    }


#endif
#include <iostream>
#include "src/compilerbase.hpp"
#include "src/compiler/util/errors.hpp"

int main(int argc, char** argv){
    beta::preprocess(util::string(argv[1]));
    beta::err::Logger::printTrace();
}



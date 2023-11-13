#include "compilerbase.hpp"

namespace beta{
    
    
    void preprocess(util::string fileName){
        preprocessorInvokation = new preproc::Preprocessor(fileName);
        preprocessorInvokation->parseLines();
        preprocessorInvokation->checkForMarker('@');
        preprocessorInvokation->parseToTokens();
        preprocessorInvokation->evaluate();
    } 


}
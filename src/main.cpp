#include "string/str.hpp"
#include <iostream>

using namespace beta;

int main(int argc, char const *argv[]){
    
    util::string str = "Hello World!";

    std::cout << str.c_str() << '\n'; 

    return 0;
}

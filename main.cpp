#include <iostream>
<<<<<<< HEAD
#include "src/compilerbase.hpp"
#include "src/compiler/util/errors.hpp"

int main(int argc, char** argv){
    beta::preprocess(util::string(argv[1]));
    beta::err::Logger::printTrace();
}
=======
#include <fstream>
>>>>>>> 1a8c0bd77e0e3c889cce2034e37a4bfc0f7fcd9f


int main(void){
    std::ofstream test("main.cpp", std::ios_base::app);

    test.seekp(20);
    test.write("TEST", 5);

    std::cout << "Hello World!\n"; 
    return 0;
}


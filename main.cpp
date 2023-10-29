#include <iostream>
#include <fstream>


int main(void){
    std::ofstream test("main.cpp", std::ios_base::app);

    test.seekp(20);
    test.write("TEST", 5);

    std::cout << "Hello World!\n"; 
    return 0;
}


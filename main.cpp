#include <iostream>
#include "src/compiler/util/collections/collections.hpp"

int main(void){
    util::string s = "Hello World!";
    std::cout << s.asCstr();

    util::LinkedList<int> intlist;
    for (int i = 0; i < 10; i++){
        intlist.append(i);
    }

    intlist.forEach([](int &num){
        std::cout << num << '\n';
    });
}



#include <iostream>


using namespace std;

int main(void){
    std::cout << typeid(int*).name() << '\n';
}
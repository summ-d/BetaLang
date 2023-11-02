#pragma once
#ifndef ERRORS_HPP
#define ERRORS_HPP

    #include "collections/collections.hpp"
    #include <iostream>

    namespace beta::err{
        struct BaseError{
            util::string message;
            int line;
            virtual void print() const = 0;
            friend std::ostream& operator<<(std::ostream& os, const BaseError& be){
                be.print();
                return os;
            }
        };

        class Logger{
            static util::LinkedList<BaseError&> errors;

            public:
            static void log(BaseError &e){
                errors.append(e);
            }

            static void printTrace(){
                errors.forEach([](BaseError &e){
                    std::cout << e;
                });
            }

        };
    }

#endif
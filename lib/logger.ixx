//
// Created by jack on 1/20/24.
//

export module util.logger;
import util.linkedlist;
import util.string;
#include <iostream>

export namespace beta::util {
    typedef struct BaseError: std::exception {
        string error;
        int line;

        [[nodiscard]] const char* what() const noexcept override {

        }
    } be_t;

    class Logger {
        static list<>
    public:
        static void Log(){}


    };


}
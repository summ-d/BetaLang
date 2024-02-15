//
// Created by jack on 2/12/24.
//

export module util.output;

import util.syscalls;
import util.utility;

namespace beta::util {

    export class Output {
        public:

        template<tps::size_t N>
        static void println(const char (&line)[N]) {
            char* buffer = new char[fn::strlen(line) + 1];
            fn::memcpy(line, buffer, fn::strlen(line));
            buffer[fn::strlen(line)] = '\n';
            sys::sys_write(1, buffer);
        }

        static void println(long long num) {
            const char* buffer = fn::longString(num);
            char* buff = new char[fn::strlen(buffer) + 1];
            fn::strcpy(buffer, buff);
            buff[fn::strlen(buffer)] = '\n';
            sys::sys_write(1, buff);
        }

        static void println(double num) {
            const char* buff = fn::doubleString(num);
            char* buffer = new char[fn::strlen(buff) + 1];
            fn::strcpy(buff, buffer);
            buffer[fn::strlen(buff)] = '\n';
            sys::sys_write(1, buff);
        }

        static void newline() {
            sys::sys_write(1, "\n");
        }

    };



}

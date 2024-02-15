//
// Created by jack on 2/14/24.
//

#define in(a) "r"(a)
#define out(a) "=r"(a)
#define inout(a) "+r"(a)

#define STRUCT_BUILDER(name,a,b,c,d,e,f,g,h,i,j) \
struct name {                                    \
    a;                                           \
    b;                                           \
    c;                                           \
    d;                                           \
    e;                                           \
    f;                                           \
    g;                                           \
    h;                                           \
    i;                                           \
    j;                                           \
};

export module util.thread.threadutils;


import util.utility;

namespace beta::util{

    namespace sys {
        export int sys_futex(tps::i32* uaddr, tps::i16 op_ftx, tps::i32 val,
                             tps::TimeSpec* timeout, tps::i32* uaddr2, tps::i32 val3) {

        }
    }

    namespace thread {


    }


}

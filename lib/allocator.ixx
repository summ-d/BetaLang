//
// Created by jack on 2/12/24.
//

#define RSEQ_SIG (1U << 1)

#define in(a) "r"(a)
#define out(a) "=r"(a)
#define inout(a) "+r"(a)

#define resq(expr, a , b, c, d, e)                                          \
                    volatile tps::u64 _pc;                                  \
                    int ok = 1;                                             \
                    tps::CritSec* _cs = nullptr;                            \
                    asm volatile( "movq $0, %1;"                            \
                                  "leaq 90f(%%rip), %%rdi;"                 \
                                  "movq %%rdi, 8(%1);"                      \
                                  "negq %%rdi;"                             \
                                  "movq %%rdi, 16(%1);"                     \
                                  "leaq 91f(%%rip), %%rdi;"                 \
                                  "addq %%rdi, 16(%1);"                     \
                                  "leaq 92f(%%rip), %%rdi;"                 \
                                  "movq %%rdi, 24(%1);"                     \
                                  "movq %1, %%rdi;"                         \
                                  "movq %%rdi, 8(%8);"                      \
                                  "90:\n\t"                                 \
                                  expr                                      \
                                  "jmp 93f;"                                \
                                  ".int 0x53053053;"                        \
                                  "92: \n\t"                                \
                                  "xor %2, %2;"                             \
                                  "93: \n\t"                                \
                                  "movq $0, 8(%8);"                         \
                                  \
                                : out(_pc), inout(_cs), inout(ok), inout(a),\
                                  inout(b), inout(c), inout(d), inout(e)    \
                                : in(current_thread_rseq())                 \
                                : "rdi", "memory");

export module util.allocator;

import util.syscalls;
import util.utility;
import util.pointers;
import util.allocator.freelist;

namespace beta::util::alloc {

    tps::Rseq* current_thread_rseq() {
        class RseqBox {
            ptr::UniquePtr<tps::Rseq> _rseq = ptr::UniquePtr<tps::Rseq>();

            public:

            explicit RseqBox(ptr::UniquePtr<tps::Rseq>&& rseq) {
                this->_rseq.swap(rseq);
            }

            ptr::UniquePtr<tps::Rseq>& under() {
                return this->_rseq;
            }

            ~RseqBox() {
                sys::sys_rseq(this->_rseq.raw(), true, RSEQ_SIG);
                _rseq.~UniquePtr();
            }
        };

        thread_local RseqBox RSEQ = RseqBox {
            new tps::Rseq {
                .cpu_id_start = 0,
                .cpu_id = 0,
                .crit_sec = 0,
                .flags = 0
            }
        };

        using rseq_func = void (*)(tps::Rseq*, bool, tps::u32);

        thread_local rseq_func func = sys::sys_rseq;

        func(RSEQ.under().raw(), false, RSEQ_SIG);

        return RSEQ.under().raw();
    }


    template<typename T>
    class PerCpu {
        public:

        ptr::SharedPtr<T> checkout(ptr::SharedPtr<T> replacement) {

        }

    };

    template<typename T>
    class Allocator {

    };
}
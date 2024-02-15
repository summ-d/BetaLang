//
// Created by jack on 2/12/24.
//

#define inout(a) "+r"(a)
#define out(a) "=r"(a)
#define in(a) "r"(a)

export module util.syscalls;

import util.utility;

namespace beta::util::sys {

    export void sys_exit(tps::i32 code){}

    export int sys_write(tps::u32 fdis, const char* msg) {
        tps::size_t len = fn::strlen(msg);
        int rax;
        asm volatile("movl %1, %%edi;"
                     "movq %2, %%rsi;"
                     "movq %3, %%rdx;"
                     "movq $1, %%rax;"
                     "syscall;"
                     "movl %%eax, %0;"
                    : inout(rax)
                    : in(fdis), in(msg), in(len)
                    : "rax", "rdi", "rsi", "rdx");
        return rax;
    }

    export void sys_rseq(tps::Rseq* rseq, bool unregister, tps::u32 sig) {
        bool valid = true;
        while (valid) {
            volatile int rax = 334;
            asm volatile("movq %1, %%rdi;"
                         "movq %4, %%rsi;"
                         "movq %2, %%rdx;"
                         "movq %3, %%r10;"
                         "movl %5, %%eax;"
                         "syscall;"
                         "movl %%eax, %0;"
                        : inout(rax)
                        : in(rseq), in((tps::u64)unregister), in(sig), in(sizeof(rseq)), in(rax)
                        :"rdi", "rsi", "rax", "rdx", "r10");
            switch (rax) {
                case 0:
                    valid = false;
                    break;
                case -4:
                    continue;
                default:
                    sys_exit(rax);
                    break;
            }
        }
    }

    export volatile tps::SysInfo* sys_sysinfo() {
        volatile tps::SysInfo* info_struct = nullptr;
        asm volatile("movq %0, %%rdi;"
                     "movl $99, %%rax;"
                     "syscall;"
                    : out(info_struct)
                    :: "rax", "rdi");
        return info_struct;
    }

}

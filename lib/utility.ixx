//
// Created by jack on 2/12/24.
//

export module util.utility;


namespace beta::util {

    namespace tps {
        export typedef long long size_t;
        export typedef int i32;
        export typedef unsigned int u32;
        export typedef unsigned char u8;
        export typedef char i8;
        export typedef unsigned short u16;
        export typedef short i16;
        export typedef long int time_t;
        export typedef unsigned long long u64;

        export using nullptr_t = decltype(nullptr);

        export struct TimeSpec {
            time_t tv_sec;
            i32 tv_nsec;
        };

        export struct Rseq {
            u32 cpu_id_start;
            u32 cpu_id;
            u64 crit_sec;
            u32 flags;
        };

        export struct CritSec {
            u32 version;
            u32 flags;
            u64 start;
            u64 len;
            u64 abort_handler;
        };

        export template<class T>
        struct RmRef {typedef T type; };

        export template<class T>
        struct RmRef<T&> {typedef T type;};

        export template<class T>
        struct RmRef<T&&> {typedef T type; };

        export struct SysInfo {
            i32 uptime;
            u32 loads[3];
            u32 totalram;
            u32 freeram;
            u32 sharedram;
            u32 bufferram;
            u32 totalswap;
            u32 freeswap;
            u16 procs;
            u16 pad;
            u32 totalhigh;
            u32 freehigh;
            u32 mem_unit;
            char _f[20 - 2 * sizeof(long)- sizeof(int)];
        };
    }

    namespace fn {
        export inline tps::size_t strlen(const char* str) {
            const char* s;
            for(s = str; *s; ++s);
            return (s - str);
        }

        export inline void strcpy(const char* src, char* dest) {
            for(int i = 0; i < strlen(src) && i < strlen(dest); i++) dest[i] = src[i];
        }

        template<typename T, tps::size_t N>
        tps::size_t arrlen(const T (&)[N]){
            return N;
        }

        export template<typename T, tps::size_t N, tps::size_t I>
        inline void memcpy(const T (&src)[N], T (&dest)[I], tps::size_t size) {
            for(int i = 0; i < size && i < arrlen(src) && i < arrlen(dest); i++) dest[i] = src[i];
        }

        int digitNumber(long long num) {
            if(num < 0) num = -num;
            if(num == 0) return 1;
            int count = 0;
            while(num != 0){
                num /= 10;
                ++count;
            }
            return count;
        }

        export const char* longString(long long num) {
            const int max = 21;
            char result[21];
            bool negative = false;

            if(num < 0){
                negative = true;
                num = -num;
            }

            int idx = max - 2;
            //result[idx] = '\0';

            do{
                result[--idx] = '0' + (num % 10);
                num /= 10;
            } while(num != 0);

            if(negative) result[--idx] = '-';
            return &result[idx];
        }

        export const char* doubleString(double num) {
            const int max = 50;
            char* result = new char[50];
            int intLength = digitNumber(static_cast<long long>(num));
            bool negative = false;

            if(num < 0) negative = true; num = -num;
            int idx = 0;
            if(negative) result[idx++] = '-';
            int intPrt = static_cast<int>(num);
            while (intPrt > 0){
                result[idx++] = '0' + (intPrt % 10);
                intPrt /= 10;
            }

            for(int i = 0; i < idx / 2; ++i) {
                char tmp = result[i];
                result[i] = result[idx - 1 - i];
                result[idx - 1 - i] = tmp;
            }

            result[idx++] = '.';

            for(int i = 0; i < 6; ++i) {
                num *= 10;
                int digit = static_cast<int>(num) % 10;
                result[idx++] = '0' + digit;
            }
            return result;
        }

        export template<typename T>
        void swap(T& rhs, T& lhs) {
            T temp = rhs;
            rhs = lhs;
            lhs = temp;
        }

        export template<class T>
        inline T&& forward(typename tps::RmRef<T>::type& t) noexcept {
            return static_cast<T&&>(t);
        }

        export template<class T>
        inline T&& forward(typename tps::RmRef<T>::type&& t) noexcept {
            return static_cast<T&&>(t);
        }


    }

}
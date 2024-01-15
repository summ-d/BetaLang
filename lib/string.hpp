//
// Created by jack on 1/14/24.
//

#ifndef COMPILER_STRING_HPP
#define COMPILER_STRING_HPP

#include "allocators.hpp"

namespace beta::util {

    typedef unsigned short size_t;

    inline size_t strlen(const char* s1);

    inline bool strcmp(const char* s1, const char* s2);

    inline void copystr(const char* src, char *dest, int size);

    template<typename St, typename Al = alloc::sAllocator<St>>
    class [[maybe_unused]] String {
        using str = St *;

        str underlying;

        Al allocator;

        size_t len{};

    public:
        String() = default;
        explicit String(str s);
        String(const String<St, Al> &other);
        String(String<St, Al>&& other) noexcept;

        String<St, Al>& operator=(const str& s);
        String<St, Al>& operator=(const String<St, Al>& other);
        String<St, Al>& operator=(String<St, Al>&& other) noexcept;

        str s_raw() const;
        const char* c_str() const;

        const St& operator[](int idx) const;
        St& operator[](int idx);

        constexpr bool operator==(St* &other) const;
        constexpr bool operator==(const String<St, Al>& other) const;
        constexpr bool operator==(String<St, Al>&& other) const noexcept;

        void append(St s);
        void append(str s);
        void append(const String<St, Al>& other);
        void append(String<St, Al>&& other) noexcept;

        String<St, Al>& operator+=(const St& s);
        String<St, Al>& operator+=(const str& s);
        String<St, Al>& operator+=(const String<St, Al>& other);
        String<St, Al>& operator+=(String<St, Al>&& other) noexcept;

        bool has(St& ele) const;
        bool has(const str& ele) const;

        size_t length() const;
    };

    [[maybe_unused]] typedef String<char> string;
}


#endif //COMPILER_STRING_HPP

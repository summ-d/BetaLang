#pragma once
#ifndef STR_HPP
#define STR_HPP

#include "alloc/allocators.hpp"

namespace beta::util{

    inline bool strcmp(const char* one, const char* two);
    inline bool strlen(const char* one);


    template<typename S, typename A = alloc::sAllocator<S>>
    class String{
        S* str;

        public:
        String() = default;
        String(const S* s);
        String(String<S>& other);
        String(String<S>&& other);

        void push_back(S s);
        void append(const S*& str); 
        
        S at(int pos) const;

        const S* s_raw() const;
        const char* c_str() const;

        S& operator[](int pos);
        const S& operator[](int pos) const;

        String<S, A>& operator=(const String<S, A>& other);
        String<S, A>& operator=(String<S, A>&& other) noexcept;
    
        constexpr bool operator==(const String<S, A>& other) const;
        bool operator==(String<S, A>& other) const;

        constexpr bool operator!=(const String<S, A>& other) const;
        bool operator!=(String<S, A>& other) const { return !(*this == other); }


    };


    typedef String<char> string;

}


#endif
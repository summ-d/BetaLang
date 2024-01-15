//
// Created by jack on 1/14/24.
//

#include "string.hpp"

namespace beta::util {

    inline size_t strlen(const char* s1) {
        const char* s;
        for(s = s1; *s; ++s);
        return (s - s1);
    }

    inline bool strcmp(const char* s1, const char* s2) {
        for(int i = 0; i < strlen(s1) && i < strlen(s2); i++) {
            if(s1[i] != s2[i]) return false;
        }
        return true;
    }

    inline void copystr(const char* src, char* dest, int size) {
        for(int i = 0; i < size; i++) dest[i] = src[i];
    }

    template<typename St, typename Al>
    String<St, Al>::String(typename beta::util::String<St, Al>::str s) {
        this->len = strlen(s);
        this->underlying = this->allocator.allocate(this->len);
        copystr(s, this->underlying, this->len);
    }

    template<typename St, typename Al>
    String<St, Al>::String(const String<St, Al> &other) {
        this->len = strlen(other.underlying);
        this->underlying = this->allocator.allocate(this->len);
        copystr(other.underlying, this->underlying, this->len);
    }

    template<typename St, typename Al>
    String<St, Al>::String(String<St, Al> &&other) noexcept {
        this->len = strlen(other.underlying);
        this->underlying = this->allocator.allocate(this->len);
        copystr(other.underlying, this->underlying, this->len);
    }

    template<typename St, typename Al>
    String<St, Al>& String<St, Al>::operator=(const typename beta::util::String<St, Al>::str &s) {
        this->len = strlen(s);
        this->underlying = this->allocator.allocate(this->len);
        copystr(s, this->underlying, this->len);
        return *this;
    }

    template<typename St, typename Al>
    String<St, Al>& String<St, Al>::operator=(const String<St, Al> &other) {
        if(&other != this){
            this->len = strlen(other.underlying);
            this->underlying = this->allocator.allocate(this->len);
            copystr(other.underlying, this->underlying, this->len);
        }
        return *this;
    }

    template<typename St, typename Al>
    String<St, Al>& String<St, Al>::operator=(String<St, Al> &&other) noexcept {
        this->len = strlen(other.underlying);
        this->underlying = this->allocator.allocate(this->len);
        copystr(other.underlying, this->underlying, this->len);
    }
}
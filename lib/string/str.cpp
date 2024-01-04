#include "str.hpp"

namespace beta::util{

    inline bool strcmp(const char* one, const char* two){

    }

    inline bool strlen(const char* one){
        const char *s;
        for(s = one; *s; ++s);
        return(s - one);
    }

    template<typename S, typename A>
    String<S, A>::String(const S* s){

    }

    template<typename S, typename A>
    String<S, A>::String(String<S>& other){

    }

    template<typename S, typename A>
    String<S, A>::String(String<S>&& other){

    }

    template<typename S, typename A>
    void String<S, A>::push_back(S s){

    }

    template<typename S, typename A>
    void String<S, A>::push_back(S s){

    }

    template<typename S, typename A>
    void String<S, A>::append(const S*& str){

    }

    template<typename S, typename A>
    S String<S, A>::at(int pos) const{}

    template<typename S, typename A>
    const S* String<S, A>::s_raw() const{

    }

    template<>
    const char* String<char>::c_str() const{
        return (const char*)this->str;
    }

    template<typename S, typename A>
    S& String<S, A>::operator[](int pos){

    }

    template<typename S, typename A>
    const S& String<S, A>::operator[](int pos) const {

    }
    
}
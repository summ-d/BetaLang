#include "allocators.hpp"

namespace beta::util::alloc {
    
    template<typename T, typename U>
    void vAllocator<T, U>::deallocate(T* one, U* two){
        if(two != nullptr){
            delete two;
        }
        if(one != nullptr){
            delete one;
        }
        two = nullptr;
        one = nullptr;
    }

    template<typename T>
    T* sAllocator<T>::allocate_single(int numof){
        return (T*) new unsigned char[sizeof(T) * numof];
    }

    template<typename T, typename U>
    typename vAllocator<T, U>::alloc_t dAllocator<T, U>::allocate_double(int numof){
        return vAllocator<T, U>::AllocBlock((T*) new unsigned char[numof * sizeof(T)], (U*) new unsigned char[numof * sizeof(U)]);
    }

    template<typename T, typename U>
    T* dAllocator<T, U>::allocate_single(int numof){
        return (T*) new unsigned char[numof * sizeof(T)];
    }

    template<typename T, typename U>
    U* dAllocator<T, U>::allocate_some(int numof){
        return (U*) new unsigned char[numof * sizeof(U)];
    }

}
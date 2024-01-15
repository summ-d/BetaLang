//
// Created by jack on 1/14/24.
//

#include "allocators.hpp"

namespace beta::util::alloc {
    template<typename T>
    T* sAllocator<T>::allocate(int num) {
        return new T[num];
    }


    template<typename T>
    T* sAllocator<T>::allocate_size(int size) {
        return (T*) new unsigned char[size];
    }

    template<typename T>
    void sAllocator<T>::deallocate(T *ptr) {
        delete ptr;
    }
}
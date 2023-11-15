#include "smartarray.hpp"

namespace util{

    template<typename ArrayType>
    SmartArray<ArrayType>::SmartArray(ArrayType* pointer){
        this->pointer = pointer;
    }

    template<typename ArrayType>
    SmartArray<ArrayType>::SmartArray(int size){
        this->pointer = new ArrayType[size];
    }

    template <typename ArrayType>
    ArrayType& SmartArray<ArrayType>::operator[](int& i){
        if(i < this->size){
            return pointer[i];
        }
        else return this[0];
    }

    template<typename ArrayType>
    ArrayType& SmartArray<ArrayType>::operator*(){
        return pointer[0];
    }

    template<typename ArrayType>
    int SmartArray<ArrayType>::size(){
        const ArrayType* ptr;
        for(ptr = pointer; *ptr; ptr++);
        return(ptr - pointer);
    }

    template<typename ArrayType>
    void SmartArray<ArrayType>::operator=(const ArrayType*& other){
        this->pointer = other;
    }

    template<typename ArrayType>
    void SmartArray<ArrayType>::operator=(const SmartArray<ArrayType>& other){
        this->pointer = other.unwrap();
    }

    template<typename ArrayType>
    SmartArray<ArrayType>& SmartArray<ArrayType>::operator=(SmartArray<ArrayType>& other){
        SmartArray<ArrayType> arr(other.unwrap());
        return arr;
    }

    template<typename ArrayType>
    ArrayType* SmartArray<ArrayType>::unwrap(){
        return this->pointer;
    }

    template<typename ArrayType>
    SmartArray<ArrayType>& SmartArray<ArrayType>::operator++(){
        SmartArray<ArrayType> result = *this;
        ++count;
        return result;
    }

    template<typename ArrayType>
    SmartArray<ArrayType>& SmartArray<ArrayType>::operator++(int){
        SmartArray<ArrayType> result = *this;
        count++;
        return result;
    }

    template<typename ArrayType>
    ArrayType SmartArray<ArrayType>::get(){
        return this[this->count];
    }

    template<typename ArrayType>
    SmartArray<ArrayType>::~SmartArray(){
        delete this->pointer;
    }

}
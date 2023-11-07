#pragma once
#ifndef SMARTARRAY_HPP
#define SMARTARRAY_HPP
namespace util{

template<typename ArrayType>
class SmartArray{
    ArrayType* pointer;

    int pSize = this->size();
    int count = 0;

    public:
    SmartArray(ArrayType *pointer = nullptr);
    SmartArray(int size);
    ArrayType& operator[](int& i);
    ArrayType& operator*();
    void operator=(const SmartArray<ArrayType>& other);
    void operator=(const ArrayType*& other);
    SmartArray<ArrayType>& operator=(SmartArray<ArrayType>& other);
    SmartArray<ArrayType>& operator++();
    SmartArray<ArrayType>& operator++(int);
    ArrayType get();
    int size();
    ArrayType* unwrap();
    ~SmartArray();

};
}



#endif
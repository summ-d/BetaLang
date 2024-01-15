//
// Created by jack on 1/14/24.
//

#include "smartptr.hpp"


namespace beta::util::sp{

    template<typename T>
    Smartptr<T>::Smartptr(T *ptr) {
        this->underlying = new T;
        this->underlying = ptr;
    }

    template<typename T>
    Smartptr<T>::Smartptr(const Smartptr<T> &other) {
        this->underlying = new T;
        this->underlying = other.underlying;
    }


    template<typename T>
    [[maybe_unused]] Smartptr<T>::Smartptr(Smartptr<T> &&other) noexcept{
        this->underlying = new T;
        this->underlying = other.underlying;
    }

    template<typename T>
    T* Smartptr<T>::raw() const {
        return this->underlying;
    }

    template<typename T>
    Smartptr<T>& Smartptr<T>::operator=(T *&other) {
        this->underlying = new T;
        this->underlying = other;
        return *this;
    }

    template<typename T>
    Smartptr<T>& Smartptr<T>::operator=(const Smartptr<T> &other) {
        if(&other != this){
            delete this->underlying;
            this->underlying = new T;
            this->underlying = other.underlying;
        }
        return *this;
    }

    template<typename T>
    Smartptr<T>& Smartptr<T>::operator=(Smartptr<T> &&other) noexcept {
        delete this->underlying;
        this->underlying = new T;
        this->underlying = other.underlying;
        return *this;
    }

    template<typename T>
    constexpr bool Smartptr<T>::operator==(T *&other) const {
        return other == this->underlying;
    }

    template<typename T>
    constexpr bool Smartptr<T>::operator==(const Smartptr<T> &other) const {
        return other.underlying == this->underlying;
    }

    template<typename T>
    constexpr bool Smartptr<T>::operator==(Smartptr<T> &&other) const noexcept {
        return other.underlying == this->underlying;
    }

    template<typename T>
    const T& Smartptr<T>::operator[](int idx) const {
        return this->underlying[idx];
    }

    template<typename T>
    T& Smartptr<T>::operator[](int idx) {
        return this->underlying[idx];
    }

    template<typename T>
    const T* Smartptr<T>::operator->() const {
        return this->underlying;
    }

    template<typename T>
    T* Smartptr<T>::operator->(){
        return this->underlying;
    }

    template<typename T>
    const T& Smartptr<T>::operator*() const {
        return *this->underlying;
    }

    template<typename T>
    T& Smartptr<T>::operator*() {
        return *this->underlying;
    }
}
#include "smartpointer.hpp"

namespace beta::util::smpt{
    
    template<typename Pt>
    Smartpointer<Pt>::Smartpointer(Pt* pointer){
        this->underlying = pointer;
    }

    template<typename Pt>
    Smartpointer<Pt>::Smartpointer(Smartpointer<Pt>& other){
        this->underlying = other.get();
    }

    template<typename Pt>
    Smartpointer<Pt>::Smartpointer(Smartpointer<Pt>&& other){
        this->underlying = other.get();
    }

    template<typename Pt>
    Pt* Smartpointer<Pt>::get() const {
        return this->underlying;
    }

    template<typename Pt>
    Pt& Smartpointer<Pt>::operator*(){
        return this->*underlying;
    }

    template<typename Pt>
    Pt* Smartpointer<Pt>::operator->(){
        return this->underlying;
    }

    template<typename Pt>
    Pt& Smartpointer<Pt>::operator[](int idx){
        return this->underlying[idx];
    }

    template<typename Pt>
    const Pt& Smartpointer<Pt>::operator[](int idx) const{
        return this->underlying[idx];
    }

    template<typename Pt>
    Smartpointer<Pt>& Smartpointer<Pt>::operator=(const Smartpointer<Pt>& other){
        return Smartpointer<Pt>(other);
    }
    
    template<typename Pt>
    bool Smartpointer<Pt>::operator==(const Smartpointer<Pt>& other) const{
        return this->underlying == other.get();
    }

    template<typename Pt>
    bool Smartpointer<Pt>::operator!=(const Smartpointer<Pt>& other) const{
        return this->underlying != other.get();
    }
}
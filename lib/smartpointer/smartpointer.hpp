#pragma once
#ifndef POINTER_HPP
#define POINTER_HPP

namespace beta::util::smpt{

    template<typename Pt>
    class Smartpointer{
        Pt* underlying;

        public:
        Smartpointer() = default;
        Smartpointer(Pt* pointer);
        Smartpointer(Smartpointer<Pt>& other);
        Smartpointer(Smartpointer<Pt>&& other);
        
        Pt* get() const;
        Pt& operator*();
        Pt* operator->();
        Pt& operator[](int idx);
        const Pt& operator[](int idx) const;

        Smartpointer<Pt>& operator=(const Smartpointer<Pt>& other);
        bool operator==(const Smartpointer<Pt>& other) const;
        bool operator!=(const Smartpointer<Pt>& other) const;

        ~Smartpointer(){ delete this->underlying; }
    };

}

#endif
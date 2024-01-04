#pragma once
#ifndef ALLOC_HPP
#define ALLOC_HPP

namespace beta::util::alloc{

    
    template<typename T, typename U = T>
    class vAllocator{
        public:
        typedef struct AllocBlock{
            T* one;
            U* two;
            AllocBlock(T* one, U* two = nullptr){
                this->one = one;
                this->two = two;
            }
        } alloc_t;

        virtual alloc_t allocate_double(int numof){}
        virtual T* allocate_single(int numof) = 0;
        virtual U* allocate_some(int numof){}
        void deallocate(T* one, U* two = nullptr); 
    };

    template<typename T>
    class sAllocator: public virtual vAllocator<T>{
        T* allocate_single(int numof) override;
    };

    template<typename T, typename U>
    class dAllocator: public virtual vAllocator<T, U>{
        typename vAllocator<T, U>::alloc_t allocate_double(int numof) override;
        T* allocate_single(int numof) override;
        U* allocate_some(int numof) override;
    };
}



#endif
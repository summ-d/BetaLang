#pragma once
#ifndef COLLECTIONS
#define COLLECTIONS


namespace beta::util::collect{

    template<typename T, typename U = T>
    struct CollectData{
        CollectData(T t, U u = t){this->one = o; this->two = u;}
        T one;
        U two;
    };


    template<typename T, typename U = T>
    class vCollections{
        
        public:

        virtual T at(int pos) = 0;
        virtual CollectData<T, U> at_pair(int pos){}
        virtual T front() = 0;
        virtual T back() = 0;

        virtual CollectData<T, U> front_pair(){}
        virtual CollectData<T, U> back_pair(){}

        virtual void insert(T t, int pos, U u = t) = 0;
        virtual void push_back(T t, U u = t) = 0;
        
    };


}


#endif
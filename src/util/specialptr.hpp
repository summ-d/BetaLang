#ifndef specialptr_hpp
#define specialptr_hpp

  #include "util.hpp"

  namespace util{
  template<typename Pointer>
  class SmartPointer{
    Pointer* ptr;


    explicit SmartPointer(Pointer* ptr = nullptr){this->ptr = ptr}

    ~SmartPointer(){ delete ptr; }

    Pointer& operator*(){return *ptr;}

    Pointer* operator->(){ return ptr; }

    Pointer& operator[](int pos){
      return ptr[pos];
    }

    void operator=(Pointer* ptr){
      this->ptr = ptr;
    }

    void* operator new(size_t size){
      this->ptr = ::operator new(size);
      return ptr;
    }

    void operator delete(void* ptr){  
      delete ptr;
    }
  };
  }

#endif
#ifndef specialptr_hpp
#define specialptr_hpp


  namespace util{
  typedef unsigned long size_t;
  template<typename Pointer>
  class SmartPointer{
    Pointer* ptr;

    public:

    explicit SmartPointer(Pointer* ptr = nullptr){ this->ptr = ptr; }

    ~SmartPointer(){ 
      if(ptr != nullptr){
        delete ptr;
      } return;
    }

    Pointer& operator*(){return *ptr;}

    Pointer* operator->(){ return ptr; }

    Pointer& operator[](int pos){
      return ptr[pos];
    }

    void operator=(Pointer* ptr){
      this->ptr = ptr;
    }

    SmartPointer<Pointer> operator=(const Pointer*& pointer){
      return new SmartPointer<Pointer>(pointer);
    }

    constexpr friend bool operator==(const SmartPointer<Pointer>& p1, const SmartPointer<Pointer>& p2);
    constexpr bool operator==(std::nullptr_t np){
      return this->ptr = np;
    }

    Pointer* get(){
      return this->ptr;
    }

    void deletePtr(){
      delete ptr;
      ptr = nullptr;
    }
    
  };

  template<typename Pointer>
  constexpr bool util::operator==(const SmartPointer<Pointer>& p1, const SmartPointer<Pointer>& p2) {
    return p1.ptr == p2.ptr;
  }

  }

#endif
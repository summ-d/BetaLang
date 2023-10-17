#ifndef specialptr_hpp
#define specialptr_hpp


  namespace util{
  template<typename Pointer>
  class SmartPointer{
    Pointer* ptr;

    public:

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

    Pointer* get(){
      return this->ptr;
    }
  };
  }

#endif
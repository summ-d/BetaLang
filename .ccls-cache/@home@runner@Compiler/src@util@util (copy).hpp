#ifndef util_hpp
#define util_hpp

#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include "specialptr.hpp"
#include <type_traits>

namespace util{

  typedef unsigned char u8;
  #define PURE =0

  template<typename Consumee>
  class Consumer{
    std::function<void(Consumee)> pConsume;
    
  
    public:
      template<class Consume>
      Consumer<Consumee>(Consume c):  pConsume(c){}
      
      void accept(Consumee c){
          pConsume(c);
      }
  };

  template<typename Consumee, typename Return = Consumee>
  class RetConsumer{
      std::function<Return(Consumee)> pConsume;

      public:
      template <class Consume>
      RetConsumer<Consumee>(Consume c): pConsume(c){}

      Return accept(Consumee c){
        return pConsume(c);
      }
  };

  template<typename Alloc>
  class Allocator{
    Alloc** arr;
    int max_size;
    int count = 0;
  
    public:
    Allocator(int max_size){
      arr = new Alloc*[max_size];
      this->max_size = max_size;
    }
    Alloc* allocate(size_t size){
      void* ptr = new u8[size];
      arr[count] = (Alloc*)ptr;
      count++;
      return (Alloc*)ptr;
    }
    void* dealloc(Alloc *ptr){
      delete ptr;
      ptr = nullptr;
      return nullptr;
    }
    ~Allocator(){
      for(int i = 0; i < max_size; i++){
        if(arr[i] != nullptr){
          delete arr[i];
        }
      }
    }
  };



  
  template<typename It>
  class Iterator{
  

    using diff_type = std::ptrdiff_t;
    using val_type = It;
    using ptr_type = It*;
    using ref_type = It&;

    ptr_type m_ptr;

    public:
  
    virtual Iterator<It> begin() PURE;
    virtual Iterator<It> end() PURE;

    Iterator(ptr_type ptr): m_ptr(ptr){}

    virtual ref_type operator*() PURE;
    virtual ptr_type operator->() PURE;
    Iterator<It>& operator++() PURE;
    Iterator<It> operator++(int) PURE;

    friend bool operator==(const Iterator<It>& a, const Iterator<It>& b){
      return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const Iterator<It>& a, const Iterator<It>& b){
      return a.m_ptr != b.m_ptr;
    }
    
    Iterator<It> operator+(int) PURE;

    virtual ~Iterator();
  };

  template<typename CollectType>
  class CollectionsBase{
    public:
    virtual void forEach(Consumer<CollectType> c) PURE;
    virtual void insertAfter(CollectType data, int pos) PURE;
    virtual void insertBefore(CollectType data, int pos) PURE;
    virtual void push(CollectType data) PURE;
    virtual void append(CollectType data) PURE;
    virtual size_t getSize() PURE;
    virtual int find(CollectType data) PURE;
    
    virtual ~CollectionsBase();
  };
  
  template<typename LinkType>
  class Node{
    public:
    SmartPointer<Node> next = nullptr;
    SmartPointer<Node> prev = nullptr;
    LinkType data;
    Node(LinkType data){
      this->data = data;
    }
  
  };
  
  template<typename LinkType, typename Alloc = Allocator<LinkType>>
  class LinkedList: virtual public CollectionsBase<LinkType>, virtual public Iterator<Node<LinkType>>{
  
  
    private:

      SmartPointer<Node<LinkType>> first;
      SmartPointer<Node<LinkType>> last;

      using node = Node<LinkType>;
    
    public:

      LinkedList(LinkType data): Iterator<node>(first){
        first = new node(data);
        last = new node();

        first->next = last;
        first->prev = nullptr;
        last->next = nullptr;
        last->prev = first;
      }

      void forEach(Consumer<LinkType> c) override{}

    
      
  
      
      
  
  };

  class Tokens{};

  class TokenScraper{};
  
  template<typename AbstractType, typename Alloc = Allocator<AbstractType>>
  class AbstractSyntax: virtual public CollectionsBase<AbstractType>, TokenScraper{};
  
}

#endif
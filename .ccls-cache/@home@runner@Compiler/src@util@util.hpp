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

    protected:
      using diff_type = std::ptrdiff_t;
      using val_type = It;
      using ptr_type = It*;
      using ref_type = It&;
    
      ptr_type m_ptr;

    public:
  
    virtual Iterator<It> begin() const noexcept PURE;
    virtual Iterator<It> end() const noexcept PURE;

    ptr_type unwrap(){
      return this->m_ptr; 
    }

    Iterator(ptr_type ptr): m_ptr(ptr){};

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

  template<typename CollectType, typename Extra = CollectType>
  class CollectionsBase{
    using it_type = Iterator<Extra>;
    using it_ref = Iterator<Extra>&;
    using it_ptr = Iterator<Extra>*;
    using const_it = const Iterator<Extra>;
  
    public:
    virtual void forEach(Consumer<CollectType> c) PURE;
    virtual void insertAfter(CollectType data, int pos) PURE;
    virtual void insertBefore(CollectType data, int pos) PURE;
    virtual void push(CollectType data) PURE;
    virtual void append(CollectType data) PURE;
    virtual size_t getSize() PURE;
    virtual it_type find(CollectType data) PURE;  
    
    virtual it_type erase(it_type pos) PURE;
    virtual it_type erase(it_type first, it_type last) PURE;
    
    virtual ~CollectionsBase();
  };

  template<typename T>
  class Node{
    public:
    SmartPointer<Node> prev;
    SmartPointer<Node> next;
    T data;
    Node(T data){
      this->data = data;
    }
    Node(Node<T>& node){
      this = node;
    }
  };
  
  template<typename LinkType, typename Alloc = Allocator<LinkType>, typename Return = LinkType>
  class LinkedList: public virtual CollectionsBase<LinkType, Node<LinkType>>, public virtual Iterator<Node<LinkType>>{
      using Node = Node<LinkType>;
      SmartPointer<Node> first;
      SmartPointer<Node> last;


      using const_it = const Iterator<Node>;
      using it_type = Iterator<Node>;
      using it_ref = Iterator<Node>&;

      void handle_insert(int pos, SmartPointer<Node> node){}
  

      public:
      LinkedList(LinkType data): Iterator<Node>(nullptr){
        first = new Node(data);
        last = new Node(); 
      };

      LinkedList(Node n): Iterator<Node>(n){
        first = new Node(n);
        last = new Node();
        return;
      };

      Iterator<LinkType> begin() const noexcept override{
        return this->first;
      }

      Iterator<LinkType> end() const noexcept override{
        return this->last->next;
      }

      Node& operator*() override{}
      Node* operator->() override{}
      it_ref operator++() override{}
      it_type operator++(int) override{}
      it_type operator+(int) override{}

      size_t getSize() override{
        SmartPointer<Node> temp = first;
        int count;
        while(temp != this->end()){
          temp = temp->next;
          count++;
        }
        return count;
      }
  
      void forEach(Consumer<LinkType> c) override{
        for(int i = 0; i < this->getSize(); i++){
          c.accept(this->begin() + i);
        }
      }

      void insertAfter(LinkType data, int pos) override{
        
      }
      void insertBefore(LinkType data, int pos) override{}
      void push(LinkType data) override{}
      void append(LinkType data) override{}
      it_type find(LinkType data) override{}
      it_type erase(it_type pod) override{}
      it_type erase(it_type first, it_type last) override{}
  
      Return forEach(RetConsumer<LinkType, Return> e){}
      
      ~LinkedList();
  
  };

  struct Token{
    
  };

  class TokenScraper{};
  
  template<typename AbstractType, typename Alloc = Allocator<AbstractType>>
  class AbstractSyntax: virtual public CollectionsBase<AbstractType>, TokenScraper{};
  
}

#endif
#ifndef util_hpp
#define util_hpp

#include "basicfunctions.hpp"
#include <functional>
#include <type_traits>
#include <iostream>
#include <string>
#include <fstream>
#include "specialptr.hpp"

namespace util {

//typedef unsigned short size_t;
typedef unsigned char u8;

#define PURE = 0

bool strcmp(const char *str1, const char *str2) {
  for (int i = 0; str1[i] != 0x00 || str2[i] != 0x00; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}

template <typename Alloc> class Allocator {
  
  Alloc* arr;

  int count = 0;

  public:
  Alloc* allocate(const size_t size){
    void* ptr = new u8[size];
    arr[count] = (Alloc*)ptr;
    count++;
    return (Alloc*)ptr;
  }

  Alloc* allocateCount(const int num){
    void* ptr = new u8[sizeof(Alloc) * num];
    arr[count] = (Alloc*)ptr;
    count++;
    return (Alloc*)ptr;
  }

  void deallocate(Alloc *alloc){
    delete alloc;
  }
  
  ~Allocator(){
    for (int i = 0; i < count; i++){
      delete arr[i];
    }
    return;
  }

  
};
 

template <class Consumee> class Consumer {

  std::function<void(Consumee)> consume_;

public:
  template <class Consume> Consumer<Consumee>(Consume c) : consume_(c) {}
  void accept(Consumee c) {
    consume_(c); 
  }
};

namespace option{

  struct AssertError{
    const char* message;
    bool abort;
    long long line;
    const char* file;
  };
  
  template<typename Ass, typename Err = AssertError> class Assert{
    public:
    void assert(Ass a, bool abort){
      const char* type = typeid(Ass).name();
      if(strcmp(type, typeid(AssertError).name())){
        AssertError err;
        err.message = "It is not True";
        err.file = __FILE__;
        err.line = __LINE__;
        if(!a && abort != true) throw err;
        if(!a && abort == true) exit(-1);
      } else{
        if(!a) throw Err();
      }
    }
  };

 
  
  template <typename Opt>
  class Option{
    bool is_enabled;

    Opt o;

    enum Options{
      None,
      Some
    };

    public:
    Option(Opt o){
      Options::Some = o;
      this->o = o;
      if(std::is_pointer<Opt>::value){
        #define IS_POINTER
      }
    }

    Option(){
      Opt o;
      Options::Some = o;
      this->o = o;
      if(std::is_pointer<Opt>::value){
        #define IS_POINTER
      }
    }

    inline void set_output(bool v){
      is_enabled = v;
    }

    Opt unwrap(){
      if(this->is_enabled){
        return Options::Some;
      } else {
        Assert<bool> a;
        try{
          a.assert(this->is_enabled, false);
        } catch(AssertError e){
          throw e;
        }
      }
    }


    inline void setAfter(Opt o){
      this->o = o;
      Options::Some = o;
    }
  
    #ifdef IS_POINTER
    
    Opt& operator[](int pos){
      return o[pos]; 
    }


    Opt& operator*(){return *o;}
    Opt* operator->(){return o;}

    #endif

    friend std::ostream& operator<<(std::ostream& in, const Option<Opt>& opt){
      std::cout << opt.unwrap();
      return in;
    }

    friend std::istream& operator>>(std::istream& in, const Option<Opt>& opt){
      opt.setAfter(std::cin);
      return in;
    }

  };

  template <typename T>
  constexpr bool operator==(const Option<T>& opt1, const Option<T>& opt2){
    opt1.set_output(true);
    opt2.set_output(true);
    return opt1.unwrap() == opt2.unwrap();
  }
  
}


template <typename CollectType, typename ExtraType = CollectType>
class CollectionsBase : public BasicFunctions<CollectType, ExtraType> {

public:
  static constexpr u8 BEFORE{0};
  static constexpr u8 AFTER{1};
  static constexpr u8 LEAST{2};
  static constexpr u8 GREATEST{3};

  virtual void forEach(Consumer<CollectType> c) {}
  virtual void forEach(Consumer<ExtraType> c) {}
  virtual size_t getSize() PURE;
  virtual void append(CollectType data) PURE;
  virtual void append(ExtraType data) {}
  virtual void insert(int pos, u8 pol, CollectType data) PURE;
  virtual void insert(int pos, u8 pol, ExtraType data) {}
  virtual void push(CollectType data) {}
  virtual void push(ExtraType data) {}
  virtual bool isEmpty() PURE;
  virtual void *nuke() PURE;
  virtual option::Option<int*> find(CollectType c) PURE;
  virtual option::Option<int*> find(ExtraType e) {}
  virtual option::Option<int> findFirst(CollectType c) PURE;
  virtual option::Option<int> findFirst(ExtraType e){}
  virtual void sort(u8 pol){}
};


template <typename Str, typename Alloc = Allocator<Str>>
class String : public CollectionsBase<Str, char> {
private:
  Str s;

  typedef CollectionsBase<Str> Collections;

  Allocator<Str> alloc;

public:
  String(Str s) { this->s = s; }
  String(){this->s = nullptr;}
  

  /*
    Inherited function from `CollectionsBase` <br />
    parameters:<br />
    `Consumer<char>`: function that is getting repeated forEach
  */
  void forEach(Consumer<char> c) override {
    for (int i = 0; i < this->getSize(); i++) {
      c.accept(this->asCStr()[i]);
    }
  }

  /*
    Inherited function from `CollectionsBase`<br />
    parameters:<br />
    none<br />
    return type:<br />
    `size_t` aka `unsigned short`
  */
  size_t getSize() override {
    size_t size = 0;
    for (size = 0; this->asCKStr()[size] != '\0'; ++size);
    return size;
  }

  /*
    Inherited from `CollectionsBase`<br />
    Parameters: <br />
    `Str`: generic representation of String type<br />
    return type:<br />
    none
  */
  void append(const Str data) override {
    Str* new_str = alloc.allocate(sizeof(data) + sizeof(this->s));
    for(int i = 0; i < (sizeof(data) + this->getSize()); i++){
      new_str[i] = s[i];
      if(i < this->getSize()){
        new_str[i] = data[i];
      }
    }
    s = new_str;
    delete new_str;
  }

  char end(){
    return this->s[this->getSize()];
  }

  char beg(){
    return this->s[0];
  }

  void append(char data) override {
    Str* new_str = alloc.allocate(sizeof(this->s) + sizeof(char));
    new_str = s + data;
    s = new_str;
    delete new_str;
  }

  void insert(int pos, u8 pol, const Str data) override {
    Str* new_str = alloc.allocate(sizeof(this->s) + sizeof(data));
    for(int i = 0; i < (sizeof(this->s) + sizeof(data)); i++){
      new_str[i] = s[i];
      if(i == pos){
        switch (pol){
          case Collections::BEFORE:
            for (int j = i - 1; j - i < sizeof(data); j++){
              new_str[j] = data[j - i];
            }
            i++;
          case Collections::AFTER:
            for(int j = i + 1; j - i < sizeof(data); j++){
              new_str[j] = data[j - i];
            }
            i--;
          default:
            option::Assert<u8> assert;
            try{
              assert.assert(pos != Collections::AFTER || Collections::BEFORE, false);
            } catch(option::AssertError e){
              throw e;
            }
            return;
        }
      }
    }
  }

  void insert(int pos, u8 pol, char data) override {
    Str* new_str = alloc.allocate(sizeof(this->s) + sizeof(char));
    for(int i = 0; i < sizeof(this->s) + 1; i++){
      new_str[i] = s[i];
      if(i == pos){
        switch(pol){
          case Collections::BEFORE:
            new_str[i - 1] = data;
            i++;
          case Collections::AFTER:
            new_str[i + 1] = data;
            i--;
          default:
            option::Assert<u8> assert;
            try{
              assert.assert(pos != Collections::AFTER || Collections::BEFORE, false);
            } catch(option::AssertError e){
              throw e;
            }
            return;
        }
      }
      
    }
  }

  void push(const Str data) override {
    Str* new_str = alloc.allocate(sizeof(this->s) + sizeof(data));
    for(int i = 0; i < (sizeof(this->s) + sizeof(data)); i++){
      new_str[i] = data[i];
      if(i == sizeof(data)){
        new_str[i] = this->s[i - sizeof(data)];
      }
    }
    return;
  }

  void push(char data) override {
    Str* new_str = alloc.allocate(sizeof(this->s) + sizeof(char));
    new_str[0] = data;
    for (int i = 1; i < sizeof(s) + sizeof(char); i++){
      new_str[i] = s[i];
    }
  }

  bool isEmpty() override {
    return this->getSize() == 0;
  }

  // returns `NULL` if not sucsuessfull
  void *nuke() override {
    delete this;
    return nullptr;
  }

  String<Str> subString(int start, size_t size){
    char* substr = new char[size];
    for (int i = start; i < (start + size) && i < this->getSize(); i++){
      substr[i - start] = this->asCStr()[i]; 
    }
    return new String<Str>(substr);
  }

  
  option::Option<int*> find(Str c) override{
    Allocator<int> localalloc;
    int* a = localalloc.allocate(sizeof(int) * 10);
    option::Option<int*> arr(a);
    int count = 0;
    for (int i = 0; i < this->getSize(); i++){
      String<Str> substr = this->substring(i, sizeof(c));
      if(strcmp(c, substr.asCKStr())){
        arr.set_output(true);
        arr.unwrap()[count] = i;
        count++;
      } else{
        arr.set_output(false);
      }
    }
    return arr;
  }
  
  option::Option<int*> find(char e) override {
    Allocator<int> localalloc;
    int* a = localalloc.allocate(sizeof(int) * 10);
    option::Option<int*> arr(a);
    int count = 0;
    for(int i = 0; i < this->getSize(); i++){
      if(this->asCStr()[i] == e){
        arr.set_output(true);
        arr.unwrap()[count] = i; 
        count++;
      } else{
        arr.set_output(false);
      }
    }
    return arr;
  }

  size_t getMemImp(){
    return sizeof(s);
  }

  
  const char *asCKStr() { return (const char *)s; }

  char *asCStr() { return (char *)s; }

  std::string asCppString(){return std::string(this->asCKStr());}

  String<Str> operator=(const Str &s) { return new String<Str>((char *)s); }

  void operator=(Str& s){this->s = s;}

  void operator=(const std::string& s){ this->s = (char*)s.c_str();}

  friend std::ostream& operator<<(std::ostream& out, String<Str>& str){
    std::cout << str.asCKStr();
    return out;
  }

  void operator+(const String<Str>& s){
    Str* new_str = alloc.allocate(sizeof(this->s) + s.getMemImp());
    for (int i = 0; i < (s.getSize() + this->getSize()); i++){
      new_str[i] = this->asCKStr()[i];
      if(i == this->getSize()){
        new_str[i] = s.asCKStr()[i - this->getSize()];
      }
    }
    s = new_str;
    return;
  }

  friend std::istream& operator>>(std::istream& in, String<Str>& str){
    if(!str.isEmpty()){
      str.append(std::cin);
    } else{
      String<Str> s(std::cin);
    }
    return in;
  }

  ssize_t getline(std::ifstream& f, char delim = '\n'){
    Str* s = alloc.allocate(500);
    int i = 0;
    f.get(s, 500);
    for (i = 0; i < 500; i++){
      if(s[i] == delim){
        Str *str = alloc.allocate(i);
        for(int j = 0; j < i; j++){
          str[j] = s[i];
        }
        break;
      }
    }
    return i;
  }

  option::Option<int> findFirst(Str c) override{
    int p;
    option::Option<int> pos(p);
    for(int i = 0; i < this->getSize(); i++){
      
    }
    
  }

  option::Option<int> findFirst(char c) override{}

  void sort(u8 pol) override{}

  ~String(){
    alloc.deallocate(s);
  }
};

template <typename Str>
constexpr bool operator==(String<Str> &str1, String<Str> &str2) {
  return strcmp(str1.asCKStr(), str2.asCKStr());
}


// Custom String class for my compiler
typedef String<char *> str;

template<typename LinkType, typename Alloc = Allocator<LinkType>>
class LinkedList: public CollectionsBase<LinkType>{
  public:
  class Node{
    public:
    SmartPointer<Node> next;
    SmartPointer<Node> prev;
    LinkType data;
    Node(LinkType data){ this->data = data;}
    Node(){
      next = nullptr;
      prev = nullptr;
    }
  };
  
  private:

  SmartPointer<Node> first = nullptr;
  SmartPointer<Node> last = nullptr;

  Allocator<LinkedList<LinkType>> nodeAlloc;
  Allocator<LinkType> allocLink;

  typedef CollectionsBase<LinkType> Collections;

  Node** makeNodes(int size){
    return new Node*[size];
  }
  
  public:

  LinkedList(LinkType data){
    first = new Node(data);
    last = new Node();
    first->prev = nullptr;
    first->next = last;
    last->prev = first;
    last->next = nullptr;
  }
  LinkedList(){
    first = new Node();
    last = new Node();
  }

  LinkedList(LinkType data[], int size){
    SmartPointer<Node*> nodes = makeNodes(size - 1);
    front = new Node(data[0]);
    last = new Node();
    for(int i = 1; i < (size - 2); i++){
      nodes[i - 1]->data = data[i]
      nodes[i - 1]->prev = nodes[i - 2];
      nodes[i - 1]->next = nodes[i];
      if(i == 1){
        nodes[i]->prev = front;
      } 
    }
    nodes[size - 1]->prev = nodes[size - 2];
    nodes[size - 1]->data = data[size - 1];
    nodes[size - 1]->next = last;
  }


  size_t getSize() override{
    SmartPointer<Node> temp = first;
    size_t count = 0;
    while(temp != nullptr){
      temp = temp->next;
      count++;
    }
    delete temp;
    return count;
  }
  
  void forEach(Consumer<LinkType> c) override{
    SmartPointer<Node> temp = first;
    while(temp != nullptr){
      c.accept(temp->data);
      temp = temp->next;
    }
    return;
  }

  void append(LinkType data) override{
    SmartPointer<Node> new_node;
    new_node->data = data;
    new_node->prev = last;
    new_node->next = nullptr;
    last->next = new_node;
    last = new_node;
    return;
  }

  void insert(int pos, u8 pol, LinkType data) override{
    SmartPointer<Node> new_node;
    SmartPointer<Node> temp = first;
    for(int i = 0; i < pos - (pol == Collections::BEFORE) ?  1 : 0; i++){
      temp = temp->next;
    }
    new_node->data = data;
    new_node->prev = temp->prev;
    new_node->next = temp->next;
    temp->prev = new_node;
    return;
  }

  void push(LinkType data) override{
    SmartPointer<Node> new_node;
    new_node->prev = nullptr;
    new_node->next = first;
    first->prev = new_node;
    return;
  }

  bool isEmpty() override{
    return this->getSize() == 0;
  }

  void *nuke() override{
    SmartPointer<Node> node = first;
    SmartPointer<Node> temp;

    while(node != nullptr){
      temp = node;
      delete temp;
      node = node->next;
    }

    delete node;
    delete temp;
    delete this;
    return nullptr;
  }

  // Warning!!! only works on primitive types and any that override the operator
  // `==`
  option::Option<int*> find(LinkType c) override{
    int* a;
    option::Option<int*> arr;
    SmartPointer<Node> node = first;
    int i = 0;
    int j = 0;
    while(node != nullptr){
      arr.set_output(false);
      if(node->data == c){
        arr.set_output(true);
        arr[j] = i;
        j++;
      }
      i++;
    }
    return arr;
  }

  option::Option<int> findFirst(LinkType c) override{
    option::Option<int> pos;
    SmartPointer<Node> node = first;
    int i = 0;
    while(node != nullptr){
      if(c == node->data){
        pos.set_output(true);
        pos = i;
        return pos;
      }
      i++;
    }
    return pos;
  }

  //TODO
  void sort(u8 pol) override{}

  LinkType front(){
    return this->first->data;
  }

  LinkType back(){
    return this->last->data;
  }

  LinkType at(int pos){
    SpecialPointer<Node> node = front;
    int i = 0; 
    while (node != nullptr){
      if(i == pos){
        return node->data;
      }
      node = node->next;
      i++;
    }
    return nullptr;
  }

  Node* getNodeAt(int pos){
    SmartPointer<Node> node = first;
    int i = 0;
    while (node != nullptr) {
      if(i == pos){
        return node;
      }
      node = node->next;
      i++;
    }
    return nullptr;
  }

  Node* getFirstNode(){
    return first;
  }

  Node* getLastNode(){
    return last;
  }

  LinkType& operator[](int pos){
    return this->at(pos);
  }
};

template<typename LnkTpe>
constexpr bool operator==(const LinkedList<LnkTpe>& ll1, const LinkedList<LnkTpe>& ll2){
  for (int i = 0; ll1.getNodeAt(i) != nullptr || ll2.getNodeAt(i) != nullptr; i++){
    if(ll1.getNodeAt(i)->data != ll2.getNodeAt(i)->data){
      return false;
    }
  }
  return true;
}

class AbstractContext{
  public:
  static constexpr u8 INITIATORY_STATEMENT{4};
  static constexpr u8 SECOND_LEVEL{5};
  static constexpr u8 THIRD_LEVEL{6};
  static constexpr u8 FOURTH_LEVEL{7};

  u8 statementType; 

};


template<typename AbstractType, typename Alloc = Allocator<AbstractType>>
class AbstractSyntax: public CollectionsBase<AbstractType>{

  public:
    class AbstractNode{
      public:
      SmartPointer<AbstractNode> parent;
      LinkedList<SmartPointer<AbstractType>> children;
      AbstractType token;
      AbstractContext ctx;
    };
  private:
    LinkedList<AbstractType> firstLevel;
    LinkedList<AbstractType> secondLevel;
    LinkedList<AbstractType> thirdLevel;
    LinkedList<AbstractType> fourthLevel;
    LinkedList<AbstractType>& linkedList;
    
    int count;

  public:

  void forEach(Consumer<AbstractType> c) override {}
  size_t getSize() override{}
  void append(AbstractType data) override{}
  void insert(int pos, u8 pol, AbstractType data){}
  void push(AbstractType data) override{}
  bool isEmpty() override{}
  void* nuke() override{}
  option::Option<int*> find(AbstractType c) override{}
  option::Option<int*> findFirst(AbstractType e) override{}
  void sort(u8 pol) override{}
};




} // namespace util

#endif
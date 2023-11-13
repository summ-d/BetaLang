#ifndef collections_hpp
#define collections_hpp

#include "special/specialptr.hpp"
#include "special/smartarray.hpp"
#include <fstream>
#include <string>
#include <stdarg.h>
#include <functional>

namespace util {
typedef unsigned long size_t;
typedef unsigned char u8;

  //struct Helper{ static void NOT_IMPLEMENTED(); };
  //#define NOT_IMPLEMENTED() Helper::NOT_IMPLEMENTED();
  
/* 
  @brief Default Template Arguments for the `String<_String, Alloc>` class.
  This is probably stupid and whatever but I don't care at all.
  It makes my life waaay easier
*/
#define DEFAULT_TEMPLATE_STRING template<typename _String, typename Alloc>

/*
  @brief Same thing as `DEFAULT_TEMPLATE_STRING` but for the 
  `LinkedList<_Link, Alloc>` class. See `DEFAULT_TEMPLATE_STRING`
  for reason.
*/
#define DEFAULT_TEMPLATE_LIST template<typename _Link, typename Alloc>

/*
  @brief Same Thing for the other two but for the `Node<_Link>` class.
*/
#define DEF_NODE template<typename _Link>
  

#define DEFAULT_TEMPLATE_MAP template<typename ArOne, typename ArTwo, typename AllocArOne, typename AllocArTwo>

/*
  @brief Comparing 2 strings
  @param s1 The first String
  @param s2 The second String
  @return `bool` 
*/  
inline bool strcmp(const char *s1, const char *s2) {
  for (int i = 0; s1[i] != '\0'; i++) {
    if (s1[i] != s2[i] || s2[i] == '\0') {
      return false;
    }
  }
  return true;
}

template<typename T> concept is_number = std::is_arithmetic<T>::value;

template<is_number Num>
inline int getDigits(Num n){
  int digits = 0;
  Num num = n;
  do{
    num /= 10;
    digits++;
  } while (num != 0);
  
}

  int getSize(const char* str){
    const char* s;
    for(s = str; *s; ++s);
    return(s - str);
  }

template <typename Alloc> class Allocator {
public:
  using val_type = Alloc;

  using ptr_type = Alloc *;
  using kPtr_type = const Alloc *;
  using ref_type = Alloc &;
  using kRef_type = const Alloc &;

  ptr_type allocate(util::size_t size);
  ptr_type allocNum(int num);
  void deallocate(ptr_type a);

  ptr_type address(ref_type ref);
};


template<typename Alloc = Allocator<char>>
inline void strcpy(Alloc& a, char* src, char* dest){
  dest = a.allocate(getSize(src));
  for(int i = 0; i < getSize(src); i++){
    dest[i] = src[i];
  }
  return;
}

namespace assert {
struct AssErr {
  char *message;
  int line;
  bool is_exit;
};

template <typename Ass, typename Error = AssErr> class Assert {
  Error e;

public:
  static void assert(Ass a, bool is_exit) {}
};
} // namespace assert

namespace option {

template <typename Opt> class Option {
  bool enabled = false;

  enum class Options : Opt { Some, None };

public:
  Option(Opt o);
  void set(bool en);
  Opt unwrap();

  friend constexpr bool operator==(Option<Opt> &o1, Option<Opt> &o2) {
    if (o1.enabled != false || o2.enabled != false) {
      return o1.Options::Some == o2.Options::Some;
    }
    return false;
  }

  friend constexpr bool operator!=(Option<Opt> &o1, Option<Opt> &o2) {
    if (o1.enabled != false || o2.enabled != false) {
      return o1.Options::Some != o2.Options::Some;
    }
    return true;
  }
};
} // namespace option

template <typename _Iter> class Iterator {
  using ptr_type = _Iter *;
  using ref_type = _Iter &;
  using kpr = const _Iter *&;
  using kPtr = const _Iter *;
  using kRef = const _Iter &;

  _Iter *current;
  _Iter *previous;

public:
  Iterator() noexcept;
  Iterator(kpr ref) noexcept;

  virtual bool operator!=(const Iterator<_Iter> &other) const noexcept = 0;
  virtual bool operator==(const Iterator<_Iter> &other) const noexcept = 0;

  _Iter operator*() const noexcept { return this->current; }

  virtual Iterator<_Iter> &operator++() = 0;
  virtual Iterator<_Iter> &operator++(int) = 0;

  virtual Iterator<_Iter> begin() const noexcept = 0;
  virtual Iterator<_Iter> end() const noexcept = 0;

  virtual Iterator<_Iter>& operator+(const int& i) noexcept = 0;
  virtual Iterator<_Iter>& operator-(const int& i) noexcept = 0;

  virtual Iterator<_Iter> next() = 0;
  virtual Iterator<_Iter> prev() = 0;
  
};

template <typename _String, typename Alloc = Allocator<_String>>
class String : public virtual Iterator<_String> {
  friend class Iterator<_String>;
  _String *str;

  using type = _String;
  using ptr_type = _String *;
  using kPtr_type = const _String *;
  using ref_type = _String &;
  using kRef_type = const _String &;
  using iter_type = Iterator<_String>;

  Alloc allocator;
  static int count;
  size_t size = this->getSize();

  inline size_t getNonTermSize(ptr_type str) {
    kPtr_type s;
    for (s = str; *s; ++s)
      ;
    return (s - str);
  }

  inline int getArrSize(int *arr){
    const int *a
    for(a = arr; *a; ++a);
    return(a - arr);
  }

public:
  String();
  
  
  String(kPtr_type str) : Iterator<String>(str[0]) {
    if (str != nullptr) {
      size_t size = getNonTermSize((const char *)str);
      ptr_type s = allocator.allocate(size + 1);
      s[size] = '\0';
      this->str = s;
    } else {
      this->str = new type[1];
      this->str[0] = '\0';
    }
  }

  String(String<type> &str) : Iterator<_String>(str.at(0)) {
    size_t size = str.getSize();
    ptr_type s = allocator.allocate(size + 1);
    if (s[size] != '\0' || s[size - 1] != '\0') {
      s[size] = '\0';
      this->str = str.asCstr();
    } else {
      this->str = str.asCstr();
    }
  }

  String(String<type> &&str) : Iterator<_String>(str.at(0)) {
    size_t size = str.getSize();
    ptr_type s = allocator.allocate(size + 1);
    // checks if it is already null terminated
    if (s[size] != '\0' || s[size - 1] != '\0') {
      s[size] = '\0';
    }
    this->str = str.asCstr();
  }

  inline const char *asCstr() { return (const char *)this->str; }

  inline size_t getSize() {
    int count = 0;
    for (int count = 0; str[count] != '\0'; ++count)
      ;
    return count;
  }

  constexpr friend bool operator==( String<_String *> &s1,
                                    String<_String *> &s2) {
    return strcmp(s1.asCstr(), s2.asCstr());
  }

  void concat(String<_String> &s);

  String<_String> concat(String<_String> s);

  type at(int pos);

  ptr_type substr(int start, int end);

  String<_String> substr(int indStart, size_t size);
  String<_String> substr(int indStart, _String delim = ' ');

  int *findAll(_String val);
  int* findAll(ptr_type val);

  option::Option<int> findFirst(_String val);
  option::Option<int> findFirst(ptr_type val);

  Iterator<_String> &operator++() override {
    iter_type::prev = iter_type::current;
    iter_type::current = this->at(count);
    count++;
  }

  Iterator<_String> &operator++(int) override {
    iter_type temp = *this;
    ++*this;
    return temp;
  }

  bool operator!=(const Iterator<_String> &i2) const noexcept override {
    return iter_type::current != *i2;
  }

  bool operator==(const Iterator<_String> &other) const noexcept override {
    return iter_type::current == *other;
  }

  Iterator<_String> begin() const noexcept override{
    return this->str[0];
  }

  Iterator<_String> end() const noexcept override{
    return this->str[this->getSize() + 1];
  }

  Iterator<_String>& operator+(const int& i) noexcept override{
    return str[iter_type::current + i];
  }

  Iterator<_String>& operator-(const int& i) noexcept override{
    return str[iter_type::current - i];
  }

  type operator[](int pos);
  String<type>& operator=(kPtr_type& c);
  void operator=(const String<_String>& c);

  bool isEmpty(){ return this->str[0] == '\0'; }
  
  friend std::ostream& operator<<(std::ostream& o, const String<_String>& s){
    o << s.asCstr();
    return o;
  }
  friend std::istream& operator>>(std::istream& i, const String<_String>& s){
    const char* s2;
    i >> s2;
    for(int j = 0; j < getSize(s2); j++){
      s[j] = s2[j];
    }
    return i;
  }

  String<_String>& operator+(kPtr_type& str) noexcept;
  void operator+=(ptr_type& str) noexcept;


  // Documentation Time!!! This has become so F****ng complex that
  // I dont even know what the hell is going on here
  template<typename ...Args>
  void format(kPtr_type str, Args&& ...args){ // takes in the string and formatting arguments
    strcpy(allocator, str, this->str);
    int* arr = this->findAll("%s"); // finds the instances of the markers
    int* arr2 = this->findAll("%n");
    // First error handling, checks if either is a nullptr and gets the size
    // if either aren't
    if(arr != nullptr || arr2 != nullptr){
      int arrSize1 = getArrSize(arr);
      int arrSize2 = getArrSize(arr2);
    }
    // gets the sizeof the args and checks if its equal
    if(sizeof...(args) != (arrSize1 + arrSize2)){
      FormatError e;
      e.line = __LINE__;
      e.message = "The amount of arguments does not match";
      throw e;
      return;
    }
    // just declaring more local shit
    int countN = 0;
    int countS = 0;
    for(int i = 0; i < sizeof...(args); i++){
      // special shit for numbers
      if(std::is_arithmetic<args[i]>::value){
        int digits = getDigits(args[i]);
        // buncha allocator shit
        ptr_type new_str = allocator.allocNum((this->size + digits) - 2);
        for(int i = 0; i < (this->size + digits) - 2; i++){
          new_str[i] = this->str[i];
          if(arr2[countN] == i){
            // what the f**k
            new_str[i] = std::to_string(args[i]).c_str()[i - arr2[countN]];
            // incrementing the counter
            countN++;
          }
        }
        // basically a strcpy function inline
        strcpy(allocator, new_str, this->str);
      }
      if(std::is_same<args[i], std::string>::value){
        // More Allocations
        ptr_type s = allocator.allocNum(args[i].length());
        strcpy(allocator, args[i].data(), s);
        ptr_type new_str = allocator.allocNum((getSize(this->str) + args[i].length()) - 2);
        for(int i = 0; i < (getSize(this->str) + args[i].length()) - 2; i++){
          new_str[i] = this->str[i];
          if(arr[countS] == i){
            // modifed strcpy basically
            new_str[i] = s[i - arr[countS]];
            countS++;
          }
        }
        strcpy(allocator, new_str, this->str);
      }
      if(std::is_same<args[i], String<_String>>::value){
        ptr_type s = allocator.allocNum(args[i].getSize());
        strcpy(allocator, args[i].asStdStr().data(), s);
        ptr_type new_str = allocator.allocNum((getSize(this->str) + args[i].getSize()) - 2);
        for(int i = 0; i < (getSize(this->str) + args[i].getSize()) - 2; i++){
          new_str[i] = this->str[i];
          if(arr[countS] == i){
            new_str[i] = s[i - arr[countS]];
            countS++;
          }
        }
        strcpy(allocator, new_str, this->str);
      }
      if(std::is_same<args[i], const char*>::value){
        ptr_type s = allocator.allocNum(getSize(args[i]));
        strcpy(allocator, args[i], s);
        ptr_type new_str = allocator.allocNum((getSize(args[i]) + getSize(this->str)) - 2);
        for(int i = 0; i < (getSize(this->str) + getSize(args[i])) - 2; i++){
          new_str[i] = this->str[i];
          if(arr[countS] == i){
            new_str[i] = s[i - arr[countS]];
            countS++;
          }
        }
        strcpy(allocator, new_str, this->str);
      }
    }
  }

  template<typename ...Args>
  void format(Args&& ...args){ // takes in just args
    // why reinvent the wheel when you have a perfectly good function
    // already? 
    try{
    this->format((kPtr_type)this->str, args);
    } catch(FormatError e){
      throw e;
    }
  }

  std::string asStdStr();
  SmartPointer<std::ifstream> getline(std::ifstream& file, char delim = '\n');
  
  std::istringstream makeStream();

};

// @deprecated
typedef String<char> Str;

typedef String<char> string;

template<typename Consumee>
class Consumer{
  std::function<void(Consumee)> pConsume;

  public:
  template<class Eater> 
  Consumer<Consumee>(Eater consume): pConsume(consume){};

  void accept(Consumee c){
    pConsume(c);
  }

};

template<typename _Link>
struct Node{
  SmartPointer<Node> prev;
  _Link data;
  SmartPointer<Node> next;
  Node();
  Node(_Link data, SmartPointer<Node<_Link>> prev, SmartPointer<Node> next);
  Node(Node<_Link>& n);
  Node(Node<_Link>&& n);
  bool isLast(){
    return next.get()->next == nullptr;
  }
};

template <typename _Link, typename Alloc = Allocator<Node<_Link>>>
class LinkedList: public virtual Iterator<Node<_Link>> {
  friend class Iterator<Node<_Link>>;
  using ptr_type = _Link*;
  using kPtr = const _Link*;
  using ref_type = _Link&;
  using kRef = const _Link&;
  using kpr = const _Link*&;
  using node_type = Node<_Link>;
  using iter_type = Iterator<node_type>;

  size_t size = this->getSize();

  SmartPointer<node_type> head;
  SmartPointer<node_type> tail;

  static int count;

  public:

  LinkedList(): iter_type(nullptr){
    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
  }

  LinkedList(_Link data): iter_type(head){
    head = new Node<_Link>(data, nullptr, tail);
    tail = new Node<_Link>();
    tail->prev = head;
    tail->next = nullptr;
  }

  
  LinkedList(LinkedList<_Link>& ll): iter_type(ll.getFront()){
    int i = 0;
    while(ll.getAt(i)->next != nullptr){
      SmartPointer<node_type> _node = new Node<_Link>(ll.getAt(i));
      i++;
    }
  }

  LinkedList(LinkedList<_Link>&& ll): iter_type(ll.getFront()){
    int i = 0;
    while(ll.getAt(i)->next != nullptr){
      SmartPointer<node_type> _node = new Node<_Link>(ll.getAt(i));
      i++;
    }
  }


  void push(_Link data);
  void insertBefore(_Link data, int pos);
  void insertAfter(_Link data, int pos);
  void append(_Link data);

  _Link getFront();
  _Link getBack();
  _Link getAt(int pos);


  void deleteFirst();
  void deleteLast();
  void deletePos(int pos);

  size_t getSize();

  bool isEmpty();
  size_t getSize();
  
  _Link operator[](const int& i);

  LinkedList<_Link> operator=(const LinkedList<_Link>& ll) noexcept;
  void operator+=(const LinkedList<_Link>& ll) noexcept;

  void forEach(Consumer<node_type> c);

  
};



} // namespace util

#endif
#ifndef collections_hpp
#define collections_hpp

#include "special/specialptr.hpp"
#include "special/smartarray.hpp"
#include <fstream>
#include <string>
#include <stdarg.h>
#include <functional>
#include <type_traits>
#include <any>

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


  /*
    @class The default alllocator for the 
    `String<_String, Alloc>` and the `LinkedList<_Link, Alloc`
    classes
  */
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


/*
template<typename Alloc = Allocator<char>>
inline void strcpy(Alloc& a, char* src, char* dest){
  dest = a.allocate(getSize(src));
  for(int i = 0; i < getSize(src); i++){
    dest[i] = src[i];
  }
  return;
}
*/

template<typename Data, typename Alloc = Allocator<Data>>
void memcpy(Alloc& a, Data* src, Data* dest, int size, int offset = 0);

template<typename Data, typename Alloc = Allocator<Data>>
void memcpy_basedOnSrc(Alloc& a, Data* src, Data* dest, int src_size, int offset = 0);


/*
  
*/
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

struct FormatError{
  int line;
  const char* message;
};

template <typename _String, typename Alloc = Allocator<_String>>
class String{
  _String *str;

  using type = _String;
  using ptr_type = _String *;
  using kPtr_type = const _String *;
  using ref_type = _String &;
  using kRef_type = const _String &;

  Alloc allocator;
  static int count;
  size_t size = this->getSize();

  inline size_t getNonTermSize(ptr_type str) {
    kPtr_type s;
    for (s = str; *s; ++s)
      ;
    return (s - str);
  }

  int pLastPos;

public:
  String();

  String(kPtr_type str);

  String(String<type>& str);

  String(String<type>&& str);

  inline const char *asCstr() const { return (const char *)this->str; }
  inline const char *asCStr() { return  (const char*) this->str;}
  
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

  type operator[](int pos);
  String<type>& operator=(kPtr_type& c);
  void operator=(const String<_String>& c);

  bool isEmpty(){ return this->str[0] == '\0'; }
  
  friend std::ostream& operator<<(std::ostream& o, String<_String>& s){
    o << (char*)s.asCstr();
    return o;
  }

  String<_String>& operator+(kPtr_type& str) noexcept;
  void operator+=(ptr_type& str) noexcept;

  std::string asStdStr();
  SmartPointer<std::ifstream> getline(std::ifstream& file, char delim = '\n');
  
  //std::istringstream makeStream();

  int lastPos();

};

typedef String<char> Str;
typedef Str string;

#undef DEF_NODE

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
class LinkedList{
  using type = _Link;
  using ptr_type = _Link*;
  using kPtr = const _Link*;
  using ref_type = _Link&;
  using kRef = const _Link&;
  using kpr = const _Link*&;
  using node_type = Node<_Link>;

  size_t size = this->getSize();

  SmartPointer<node_type> head;
  SmartPointer<node_type> tail;

  static int count;

  public:

  LinkedList(){
    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
  }

  LinkedList(_Link data){
    head = new Node<_Link>(data, nullptr, tail);
    tail = new Node<_Link>();
    tail->prev = head;
    tail->next = nullptr;
  }

  LinkedList(LinkedList<type>& ll);
  LinkedList(LinkedList<type>&& ll);



  void push(_Link data);
  void insertBefore(_Link data, int pos);
  void insertAfter(_Link data, int pos);
  void append(_Link data);

  _Link getFront();
  _Link getBack();
  _Link getAt(int pos);

  SmartPointer<Node<_Link>> nodeAt(int pos);

  bool isLast(Node<_Link>* node){
    return node->next->next == nullptr;
  }

  SmartArray<int> find(_Link data);

  void deleteFirst();
  void deleteLast();
  void deletePos(int pos);

  size_t getSize();

  bool isEmpty();
  
  _Link operator[](const int& i);
  LinkedList<_Link>& operator=(const LinkedList<_Link>& ll) noexcept;
  void operator+=(const LinkedList<_Link>& ll) noexcept;
  void forEach(std::function<void(_Link)> c);

};

typedef LinkedList<int> intlist;
typedef LinkedList<util::string> stringlist;
typedef LinkedList<float> floatlist;

LinkedList<util::string> parse(util::string str, char delim = ' ');


template<typename ArOne, typename ArTwo, typename AllocArOne = Allocator<ArOne>, typename AllocArTwo = Allocator<ArTwo>>
class RelationalMap{
  
  ArOne* oneUnder;
  ArTwo* twoUnder;

  using tOne = ArOne*;
  using tTwo = ArTwo*;

  AllocArOne allocatorOne;
  AllocArTwo allocatorTwo;

  size_t pSize = this->size();

  public:
  
  struct RelationalData{
    ArOne dataOne;
    ArTwo dataTwo;
  };

  union Data{
    ArOne dataOne;
    ArTwo dataTwo;
  };
  
  RelationalMap();
  RelationalMap(int size);
  RelationalMap(ArOne data, ArTwo d);
  RelationalMap(RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>& rm);
  RelationalMap(RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>&& rm);
 
  void push(ArOne data, ArTwo d);
  void append(ArOne data, ArTwo d);
  
  RelationalData get(int index);
  RelationalData get(RelationalData* (function));

  void before(ArOne d, ArTwo dat, int pos);
  void after(ArOne d, ArTwo dat, int pos);

  ArOne* rawOne(){ return this->oneUnder;}
  ArTwo* rawTwo(){ return this->twoUnder;}
  
  void forEach(std::function<void(ArOne, ArTwo)> c);
  size_t size();

  RelationalData& operator[](int& i);
  void operator=(RelationalMap<ArOne, ArTwo> rm);

  // TODO: Convert this to a valid thing (Add argument)
  void operator+=(RelationalMap<ArOne, ArTwo>& rm);
  Data& operator()(int& idOne, int& idTwo);

  RelationalData front();
  RelationalData back();

  bool isEmpty();

};



} // namespace util

#endif
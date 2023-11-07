#ifndef collections_hpp
#define collections_hpp

#include "special/specialptr.hpp"
#include "special/smartarray.hpp"
#include <fstream>
#include <string>
#include <stdarg.h>
#include <functional>
#include <type_traits>

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

public:
  String();

  String(kPtr_type str);

  String(String<type>& str);

  String(String<type>&& str);

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

  type operator[](int pos);
  String<type>& operator=(kPtr_type& c);
  void operator=(const String<_String>& c);

  bool isEmpty(){ return this->str[0] == '\0'; }
  
  friend std::ostream& operator<<(std::ostream& o, String<_String>& s){
    o << (char*)s.asCstr();
    return o;
  }
  friend std::istream& operator>>(std::istream& i, const String<_String>& s){
    const char* s2;
    i >> (char*)s2;
    for(int j = 0; j < getSize(s2); j++){
      s[j] = s2[j];
    }
    return i;
  }

  String<_String>& operator+(kPtr_type& str) noexcept;
  void operator+=(ptr_type& str) noexcept;

  std::string asStdStr();
  SmartPointer<std::ifstream> getline(std::ifstream& file, char delim = '\n');
  
  //std::istringstream makeStream();

};

typedef String<char> Str;
typedef Str string;

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


  void deleteFirst();
  void deleteLast();
  void deletePos(int pos);

  size_t getSize();

  bool isEmpty();
  
  _Link operator[](const int& i);
  LinkedList<_Link>& operator=(const LinkedList<_Link>& ll) noexcept;
  void operator+=(const LinkedList<_Link>& ll) noexcept;
  void forEach(Consumer<node_type> c);

};



} // namespace util

#endif
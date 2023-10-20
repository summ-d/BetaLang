#ifndef collections_hpp
#define collections_hpp

#include "specialptr.hpp"
#include <fstream>
#include <string>
#include <stdarg.h>
#include <functional>

namespace util {
typedef unsigned long size_t;
typedef unsigned char u8;

  //struct Helper{ static void NOT_IMPLEMENTED(); };
  //#define NOT_IMPLEMENTED() Helper::NOT_IMPLEMENTED();
  

#define DEFAULT_TEMPLATE_STRING template<typename _String, typename Alloc>
#define DEFAULT_TEMPLATE_LIST template<typename _Link, typename Alloc>
#define DEF_NODE template<typename _Link>
  
inline bool strcmp(const char *s1, const char *s2) {
  for (int i = 0; s1[i] != '\0'; i++) {
    if (s1[i] != s2[i] || s2[i] == '\0') {
      return false;
    }
  }
  return true;
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

  constexpr friend bool operator==(const String<_String *> &s1,
                                   const String<_String *> &s2) {
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

  Iterator<_String> next() override;
  Iterator<_String> prev() override;

  String<_String>& operator+(kPtr_type& str) noexcept;
  void operator+=(ptr_type& str) noexcept;

  template<typename ...Args>
  void format(kPtr_type str, Args&& ...args);

  template<typename ...Args>
  void format(Args&& ...args);

  std::string asStdStr();
  SmartPointer<std::ifstream> getline(std::ifstream& file, char delim = '\n');
  
  
};

typedef String<char> Str;

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

  iter_type at(int pos);
  iter_type at(iter_type (*fun));
  iter_type front();
  iter_type back();

  SmartPointer<node_type> getFront();
  SmartPointer<node_type> getBack();
  SmartPointer<node_type> getAt(int pos);

  void deleteFirst();
  void deleteLast();
  void deletePos(int pos);

  size_t getSize();

  bool isEmpty();
  
  _Link operator[](const int& i);

  LinkedList<_Link> operator=(const LinkedList<_Link>& ll) noexcept;
  void operator+=(const LinkedList<_Link>& ll) noexcept;

  void forEach(Consumer<node_type> c);

  //inherited methods from `Iterator<_Iter>`
  bool operator!=(const Iterator<node_type>& i2) const noexcept override;
  bool operator==(const Iterator<node_type>& other) const noexcept override;
  
  Iterator<node_type> &operator++() override;
  Iterator<node_type> &operator++(int) override;

  Iterator<node_type> begin() const noexcept override;
  Iterator<node_type> end() const noexcept override;

  Iterator<node_type>& operator+(const int& i) noexcept override;
  Iterator<node_type>& operator-(const int& i) noexcept override;

  Iterator<node_type> next() override;
  Iterator<node_type> prev() override;

  

};



} // namespace util

#endif
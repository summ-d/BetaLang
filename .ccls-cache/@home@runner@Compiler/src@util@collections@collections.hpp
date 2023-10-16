#ifndef collections_hpp
#define collections_hpp

namespace util {
typedef unsigned long size_t;
typedef unsigned char u8;

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
  _Iter *prev;

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

  virtual Iterator<_Iter> operator+(const int& i) noexcept = 0;
  virtual Iterator<_Iter> operator-(const int& i) noexcept = 0;

  
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
  int count = 1;

  inline size_t getNonTermSize(const char *str) {
    const char *s;
    for (s = str; *s; ++s)
      ;
    return (s - str);
  }

public:
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

  Iterator<_String> begin();

  void concat(String<_String> &s);

  String<_String> concat(String<_String> s);

  type at(int pos);

  ptr_type substr(int start, int end);

  int *findAll(_String val);

  option::Option<int> findFirst(_String val);

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
};

typedef String<char> Str;

template <typename _Link, typename Alloc = Allocator<_Link>>
class LinkedList {};

} // namespace util

#endif
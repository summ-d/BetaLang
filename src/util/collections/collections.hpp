#ifndef collections_hpp
#define collections_hpp

namespace util{
  typedef unsigned long size_t;
  typedef unsigned char u8;

  inline bool strcmp(const char* s1, const char* s2){
    for(int i = 0; s1[i] != '\0'; i++){
      if(s1[i] != s2[i] || s2[i] == '\0'){
        return false;
      }
    }
    return true;
  }
  
  
  template<typename Alloc>
  class Allocator{
    public:
    using val_type = Alloc;
  
    using ptr_type = Alloc*;
    using kPtr_type = const Alloc*;
    using ref_type = Alloc&;
    using kRef_type = const Alloc&;
    

  
    ptr_type allocate(util::size_t size);
    ptr_type allocNum(int num);
    void deallocate(ptr_type a);

    ptr_type address(ref_type ref);
    
  
  
  };

  namespace assert{
      struct AssErr{
        char* message;
        int line;
        bool is_exit;
      };
    
      template<typename Ass, typename Error = AssErr>
      class Assert{
        Error e;
    
        public:
    
        static void assert(Ass a, bool is_exit){}
      };
  }

  namespace option{
    
    template<typename Opt>
    class Option{
      bool enabled = false;
    
      enum class Options: Opt {
        Some,
        None
      };

      public:
      Option(Opt o);
      void set(bool en);
      Opt unwrap();
    
      friend constexpr bool operator==(Option<Opt>& o1, Option<Opt>& o2){
        if(o1.enabled != false || o2.enabled != false){
          return o1.Options::Some == o2.Options::Some;
        }
        return false;
      }
    
      friend constexpr bool operator!=(Option<Opt>& o1, Option<Opt>& o2){
        if(o1.enabled != false || o2.enabled != false){
          return o1.Options::Some != o2.Options::Some;
        }
        return true;
      }
    };
  }


  template<typename _String, typename Alloc = Allocator<_String>> class String{
    _String* str;

    using type = _String;
    using ptr_type = _String*;
    using kPtr_type = const _String*;
    using ref_type = _String&;
    using kRef_type = const _String&;

    Alloc allocator;
  
    inline size_t getNonTermSize(const char* str){
        const char* s;  
        for(s = str; *s; ++s);
        return (s - str);
    }
  
  
    public:

    String(kPtr_type str){
      if(str != nullptr){
        size_t size = getNonTermSize((const char*)str);
        ptr_type s = allocator.allocate(size + 1);
        s[size] = '\0';
        this->str = s;
      } else{
        this->str = new type[1];
        this->str[0] = '\0';
      }
    }

    String(String<type>& str){
      size_t size = str.getSize();
      ptr_type s = allocator.allocate(size + 1);
      if(s[size] != '\0' || s[size - 1] != '\0'){
        s[size] = '\0';
        this->str = str.asCstr();
      } else{
        this->str = str.asCstr();
      }
    }

    String(String<type>&& str){
      size_t size = str.getSize();
      ptr_type s = allocator.allocate(size + 1);
      // checks if it is already null terminated
      if(s[size] != '\0' || s[size - 1]  != '\0'){
        s[size] = '\0';
      }
      this->str = str.asCstr();
    }

    inline const char* asCstr(){
      return (const char*)this->str;
    }

    inline size_t getSize(){
      int count = 0;
      for(int count = 0; str[count] != '\0'; ++count);
      return count;
    }

    constexpr friend bool operator==(const String<_String*>& s1, const String<_String*>& s2){
      return strcmp(s1.asCstr(), s2.asCstr());
    }

    void concat();
    type at(int pos);
    ptr_type substr(int start, int end);
    int* findAll();
    option::Option<int> findFirst();
  
  };
  

  typedef String<char> Str;
  
  template<typename _Link, typename Alloc = Allocator<_Link>>
  class LinkedList{};

  
}

#endif
#ifndef typediscriptors_hpp
#define typediscriptors_hpp

#include "collections/collections.hpp"

namespace beta{
  namespace td{
    enum NumberTypes{
      INTEGER,
      INT8,
      INT16,
      INT32,
      INT64,
      UINT8,
      UINT16,
      UINT32,
      UINT64,
      FLOAT,
      FLOAT8,
      FLOAT16,
      FLOAT32,
      FLOAT64,
      BOOLEAN
    };

    enum CharTypes{
      CHAR,
      CHAR16,
      STRING
    };

    enum OtherTypes{
      OBJ,
      COMP
    };
    
    struct Number_TypeDisciptor{
      int size;
      util::Str name;
      util::Str value;
      NumberTypes type;
    };

    struct Char_TypeDiscriptor{};
    
    struct String_Typediscriptor{};

    struct Object_TypeDiscriptor{};

    class TypeDiscriptor{
      public:
      TypeDiscriptor();
      
    };
    
  }
}

#endif

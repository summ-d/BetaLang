#ifndef abstractsyntax_hpp
#define abstractsyntax_hpp

#include "collections/collections.hpp"

namespace util{
  typedef unsigned char u8;

  struct Token {
    Str message;
    u8 childNum;
    static Token parse(Str line);
  };

  struct Types{
    static const u8 NO_CHILD{0};
    static const u8 ONE_CHILD{1};
    static const u8 TWO_CHILD{2};
    static const u8 THREE_CHILD{3};
    static const u8 FOUR_CHILD{4};
    static const u8 UNSPEC_CHILD{5};
    static int typeToInt(u8 type){
      switch (type){
        case NO_CHILD:
          return 0;
          break;
        case ONE_CHILD:
          return 1;
          break;
        case TWO_CHILD:
          return 2;
          break;
        case THREE_CHILD:
          return 3;
          break;
        case FOUR_CHILD:
          return 4;
          break;
        case UNSPEC_CHILD:
          return 5;
          break;
        default:
          return -1;
          break;
      }
    }
  };

  template<typename Syntax = Token>
  struct AbstractNode{
    Syntax token;
    SmartPointer<AbstractNode<Syntax>> parent;
    LinkedList<SmartPointer<AbstractNode<Syntax>>> children; 
    AbstractNode(AbstractNode<Syntax>& an);
    AbstractNode(AbstractNode<Syntax>&& an);
    AbstractNode(Syntax token, SmartPointer<AbstractNode<Syntax>> parent, LinkedList<SmartPointer<AbstractNode<Syntax>>> children);
  };

  
  template<typename Syntax = Token, typename Alloc = Allocator<Syntax>>
  class AbstractSyntax: public virtual Iterator<AbstractNode<Syntax>>{
    friend class Iterator<Syntax>;
    using abstract_type = AbstractNode<Syntax>;
    using iter_type = Iterator<AbstractNode<Syntax>>;
    
    
    public:

    AbstractSyntax();
    AbstractSyntax(Syntax s);
    AbstractSyntax(AbstractSyntax<Syntax, Alloc>& as);
    AbstractSyntax(AbstractSyntax<Syntax, Alloc>&& as);
    AbstractSyntax(LinkedList<Syntax> &linkedList);
    


    void createBranch(SmartPointer<AbstractNode<Syntax>>& node, Syntax token);
    void addToHead(Syntax token);
    iter_type at(int iterNum, int tokenNum);

    size_t getBranchSize();
    size_t getEntireSize();
    iter_type front();

    SmartPointer<abstract_type> getHead();

    Syntax& operator()(const int& xInd, const int& yInd);
  
    bool operator!=(const iter_type& other) const noexcept override;
    bool operator==(const iter_type& other) const noexcept override;

    iter_type &operator++() override;
    iter_type &operator++(int) override;
    
    iter_type begin() const noexcept override;
    iter_type end() const noexcept override;
  
    iter_type &operator+(const int& i) noexcept override;
    iter_type &operator-(const int& i) noexcept override;

    iter_type next() override;
    iter_type prev() override;
      
  };
    
  
    
    
  
  
  };
  
}
#endif
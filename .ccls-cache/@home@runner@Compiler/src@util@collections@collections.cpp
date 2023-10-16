#include "collections.hpp"

namespace util{

  template<typename Alloc>
  typename Allocator<Alloc>::ptr_type Allocator<Alloc>::allocate(util::size_t size){
      void* ptr = new u8[size];
      return (Alloc*)ptr;
  }

  template<typename Alloc>
  typename Allocator<Alloc>::ptr_type Allocator<Alloc>::allocNum(int num){
    return new Alloc[num];
  }

  template<typename Alloc>
  void Allocator<Alloc>::deallocate(ptr_type a){
    delete a;
  }

  template<typename Alloc>
  typename Allocator<Alloc>::ptr_type Allocator<Alloc>::address(ref_type ref){
      return &ref;
  }

  namespace option {
      template<typename Opt>
      Option<Opt>::Option(Opt o){
        Options::Some = o;
      }

      template<typename Opt>
      void Option<Opt>::set(bool en){
        if(en == this->enabled){
          return;
        } 
        en = this->enabled;
        return;
      }

      template<typename Opt>
      Opt Option<Opt>::unwrap(){
        if(this->enabled == true){
          return Options::Some;
        } else{
          return Options::None;
        }
      }
  }
  
}
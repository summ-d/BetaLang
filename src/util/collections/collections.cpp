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

  template<typename _Iter>
  Iterator<_Iter>::Iterator() noexcept{
    current = nullptr;
  }

  template<typename _Iter>
  Iterator<_Iter>::Iterator(kpr ref) noexcept{
    current = ref;
  }

  DEFAULT_TEMPLATE_STRING
  void String<_String, Alloc>::concat(String<_String> &s){
    ptr_type new_string = allocator.allocate(this->size + s.getSize());
    for(int i = 0; i < sizeof(new_string); i++){
      new_string[i] = str[i];
      if(i == this->size){
        new_string[i] = s.asCstr()[i - this->size];
      }
    }
    str = new_string;
  }

  DEFAULT_TEMPLATE_STRING
  String<_String> String<_String, Alloc>::concat(String<_String> s){
    ptr_type new_str = allocator.allocate(this->size + s.getSize());
    for(int i = 0; i < sizeof(new_str); i++){
      new_str[i] = str[i];
      if(i == this->size){
        new_str[i] = s.asCstr()[i - this->size];
      }
    }
    String<_String> new_string(new_str);
    return new_string;
  }

  DEFAULT_TEMPLATE_STRING
  typename String<_String, Alloc>::type String<_String, Alloc>::at(int pos){
    if(pos < this->size){
      return this->str[pos];
    }
    return '\0';
  }

  DEFAULT_TEMPLATE_STRING
  typename String<_String, Alloc>::ptr_type String<_String, Alloc>::substr(int start, int end){
    ptr_type new_str = allocator.allocate(end - start);
    for(int i = start; i < end; i++){
      new_str[i - start] = str[i];
    }
    return new_str;
  }

  DEFAULT_TEMPLATE_STRING
  String<_String> String<_String, Alloc>::substr(int indStart, size_t size){
    ptr_type new_str = allocator.allocate(size);
    for(int i = indStart; i < indStart + size; i++){
      new_str[i - indStart] = str[i];
    }
    String<_String> new_string = new_str;
  }

  DEFAULT_TEMPLATE_STRING
  int* String<_String, Alloc>::findAll(_String val){
    int* arr;
    int arrCount = 0;
    for(int i = 0; i < this->size; i++){
      if(str[i] == val){
        arr[arrCount] = i;
        arrCount++;
      }
    }
    if(arrCount == 0){
      return nullptr;
    }
    return arr;
  }

  DEFAULT_TEMPLATE_STRING
  int* String<_String, Alloc>::findAll(ptr_type val){
    size_t size = this->getNonTermSize(val);
    int* arr;
    int arrCount = 0;
    for(int i = 0; i < this->size - size; i++){
      ptr_type sub = this->substr(i, i + size);
      if(strcmp(sub, val)){
        arr[arrCount] = i;
        arrCount++;
      }
    } 
    if(arrCount == 0){
      return nullptr;
    }
    return arr;
  }

  DEFAULT_TEMPLATE_STRING
  option::Option<int> String<_String, Alloc>::findFirst(_String val){
    int index;
    option::Option<int> ind(index);
    for(int i = 0; i < this->size; i++){
      if(str[i] == val){
        index = i;
        ind.set(true);
        break;
      }
    }
    return ind;
  }

  DEFAULT_TEMPLATE_STRING
  option::Option<int> String<_String, Alloc>::findFirst(ptr_type val){
    int index = 0;
    option::Option<int> ind(index);
    for(int i = 0; i < this->size; i++){
      if(str[i] == val){
        index = i;
        ind.set(true);
        break;
      }
    }
    return ind;
  }

  DEFAULT_TEMPLATE_STRING
  typename String<_String, Alloc>::type String<_String, Alloc>::operator[](int pos){
    return this->at(pos);
  }

  DEFAULT_TEMPLATE_STRING
  String<_String> String<_String, Alloc>::operator=(kPtr_type& c){
    return new String<_String>(c);
  }

  DEFAULT_TEMPLATE_STRING 
  void String<_String, Alloc>::operator=(ptr_type& c){
    if(strcmp(c, str)){
      return;
    } else{
      str = c;
    }
  }

  DEFAULT_TEMPLATE_STRING
  Iterator<_String> String<_String, Alloc>::next(){
    return str[iter_type::current + 1];
  }

  DEFAULT_TEMPLATE_STRING
  Iterator<_String> String<_String, Alloc>::prev(){
    return str[iter_type::current - 1];
  }

  DEFAULT_TEMPLATE_STRING
  String<_String> &String<_String, Alloc>::operator+(kPtr_type& str) noexcept{
    size_t size = this->getNonTermSize(str);
    ptr_type new_str = allocator.allocate((this->size + size) / sizeof(_String));
    for(int i = 0; i < (this->size + size); i++){
      new_str[i] = this->str[i];
      if(i == this->size){
        new_str[i] = str[i - this->size];
      }
    }
    String<_String> new_string = new_str;
    return new_string;
  }

  DEFAULT_TEMPLATE_STRING
  void String<_String, Alloc>::operator+=(kPtr_type& str) noexcept{
      size_t size = this->getNonTermSize(str);
      ptr_type new_str = allocator.allocate((this->size + size) / sizeof(_String));
      for(int i = 0; i < (this->size + size); i++){
        new_str[i] = this->str[i];
        if(i == this->size){
          new_str[i] = str[i - this->size];
        }
      }
      str = new_str;
  }

  
  DEF_NODE
  Node<_Link>::Node(){
    prev = nullptr;
    next = nullptr;
  }

  DEF_NODE
  Node<_Link>::Node(_Link data, SmartPointer<Node<_Link>> prev, SmartPointer<Node<_Link>> next){
    this->data = data;
    this->next = next;
    this->prev = prev;
  } 

  DEF_NODE 
  Node<_Link>::Node(Node<_Link>& n){
    this->data = n.data;
    this->next = n.next;
    this->prev = n.prev;
  }

  DEF_NODE
  Node<_Link>::Node(Node<_Link>&& n){
    this->data = n.data;
    this->next = n.next;
    this->prev = n.prev;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::push(_Link data){
    
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::insertAfter(_Link data, int pos){
    
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::insertBefore(_Link data, int pos){
    
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::append(_Link data){
    
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::at(int pos){
    
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::at(iter_type (*fun)){
    return fun;
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::front(){
    
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::back(){
    
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::getFront(){
    
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::getBack(){
    
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::getAt(int pos){
    
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::deleteFirst(){
    
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::deleteLast(){
    
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::deletePos(int pos){
    
  }

  DEFAULT_TEMPLATE_LIST
  bool LinkedList<_Link, Alloc>::isEmpty(){
    
  }

  DEFAULT_TEMPLATE_LIST
  _Link LinkedList<_Link, Alloc>::operator[](const int& i){
    
  }

  DEFAULT_TEMPLATE_LIST
  bool LinkedList<_Link, Alloc>::operator!=(const Iterator<node_type>& other) const noexcept{
    
  }

  DEFAULT_TEMPLATE_LIST
  bool LinkedList<_Link, Alloc>::operator==(const Iterator<node_type>& other) const noexcept{
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> &LinkedList<_Link, Alloc>::operator++(){
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> &LinkedList<_Link, Alloc>::operator++(int){
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::begin() const noexcept{
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::operator+(const int& i) noexcept{
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::operator-(const int& i) noexcept{
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::next(){
    
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::prev(){
    
  }
  
}
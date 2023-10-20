#include "collections.hpp"


namespace util{

  DEFAULT_TEMPLATE_STRING
  int String<_String, Alloc>::count = 1;

  DEFAULT_TEMPLATE_LIST
  int LinkedList<_Link, Alloc>::count = 1;
  
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
  String<_String, Alloc>::String(){
    this->str = allocator.allocNum(1);
    str[0] = '\0';
    return;
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
  String<_String> String<_String, Alloc>::substr(int indStart, _String delim){
    int* arr = this->findAll(delim);
    if(arr != nullptr){
      int i = 0;
      while(arr[i] != -1){
        if(arr[i] < indStart){
          i++;
        } else if (arr[i] == indStart){
          return String<_String>(delim);
        } else{
          ptr_type str = allocator.allocNum(arr[i] - i);
          for (int j = indStart; j < arr[i]; j++){
            str[j - indStart] = this->str[j]; 
          }
          String<_String> ret(str);
          return ret;
        }
      }
    }
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
    arr[arrCount + 1] = -1;
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
  String<_String>& String<_String, Alloc>::operator=(kPtr_type& c){
    return new String<_String>(c);
  }

  DEFAULT_TEMPLATE_STRING 
  void String<_String, Alloc>::operator=(const String<_String>& c){
    this->str = c.asCstr();
  }

  DEFAULT_TEMPLATE_STRING
  std::ifstream& String<_String, Alloc>::getline(std::ifstream& file, char delim = '\n'){
    
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
  void String<_String, Alloc>::operator+=(ptr_type& str) noexcept{
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

  DEFAULT_TEMPLATE_STRING
  SmartPointer<std::ifstream> String<_String, Alloc>::getline(std::ifstream &file, char delim){
    char* c = new char[500];
    file.get(c, 500);
    int i = 0;
    int count = 0;
    while(c[i] != delim && i < 500){
      i++;
    }
    str = allocator.allocate(i);
    for(int j = 0; j < i; i++){
      str[j] = c[j];
    }
    SmartPointer<std::ifstream> ptr(&file);
    return ptr;
  }
  
  DEFAULT_TEMPLATE_STRING
  std::string String<_String, Alloc>::asStdStr(){
    return std::string(this->asCstr());
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
<<<<<<< HEAD:src/util/collections/collections.cpp
    SmartPointer<node_type> node = new node_type(data, head, head->next);
    head->next->prev = node;
    head->next = node;
=======
    SmartPointer<Node<_Link>> new_node = new Node<_Link>(data, head, head->next);
    head->next->prev = new_node;
    head->next = new_node;
>>>>>>> e9e0d95232fc36cd0360d6162ad807a7f501a218:src/compiler/util/collections/collections.cpp
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::insertAfter(_Link data, int pos){
    SmartPointer<Node<_Link>> temp = head;
    int i = 0;
    while(temp != nullptr && i < pos){
      temp = temp->next;
      i++;
    }
    SmartPointer<Node<_Link>> new_node = new Node<_Link>(data, temp, temp->next);
    temp->next->prev = new_node;
    temp->next = new_node;
    return;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::insertBefore(_Link data, int pos){
    SmartPointer<Node<_Link>> temp = head;
    int i = 0;
    while(temp != nullptr && i < pos){
      temp = temp->next;
      i++;
    }
    SmartPointer<node_type> new_node = new node_type(data, temp->prev, temp);
    temp->prev->next = new_node;
    temp->prev = new_node;
    return;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::append(_Link data){
    SmartPointer<node_type> new_node = new node_type(data, tail->prev, tail);
    tail->prev->next = new_node;
    tail->prev = new_node;
    return;
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::at(int pos){
    SmartPointer<node_type> temp = head;
    int i = 0;
    while(temp != nullptr && i < pos){
      temp = temp->next;
      i++;
    }
    return *temp.get();
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::at(iter_type (*fun)){
    return fun;
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::front(){
    return *head.get();
  }

  DEFAULT_TEMPLATE_LIST
  typename LinkedList<_Link, Alloc>::iter_type LinkedList<_Link, Alloc>::back(){
    return *tail.get();
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::getFront(){
    return head;
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::getBack(){
    return tail;
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::getAt(int pos){
    SmartPointer<Node<_Link>> temp = head;
    int i = 0;
    while(temp != nullptr && i < pos){
      temp = temp->next;
      i++;
    }
    return temp;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::deleteFirst(){
    SmartPointer<node_type> head_ref = head;
    head_ref.deletePtr();
    head->next->prev = nullptr;
    head = head->next;
    return;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::deleteLast(){
    SmartPointer<node_type> tail_ref = tail;
    tail_ref.deletePtr();
    tail->prev->next = nullptr;
    tail = tail->prev;
    return;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::deletePos(int pos){
    SmartPointer<node_type> node_ref = head;
    int i = 0;
    while(node_ref != nullptr && i < pos){
      node_ref = node_ref->next;
      i++;
    }
    node_ref->prev->next = node_ref->next->prev;
    node_ref->next->prev = node_ref->prev->next;
    return;
  }

  DEFAULT_TEMPLATE_LIST
  size_t LinkedList<_Link, Alloc>::getSize(){
    SmartPointer<Node<_Link>> temp = head;
    int count = 0;
    while(temp != nullptr){
      temp = temp->next;
      count++;
    }
    return count;
  }

  DEFAULT_TEMPLATE_LIST
  bool LinkedList<_Link, Alloc>::isEmpty(){
    return head->next->next == nullptr;
  }

  DEFAULT_TEMPLATE_LIST
  size_t LinkedList<_Link, Alloc>::getSize(){
    
  }

  DEFAULT_TEMPLATE_LIST
  _Link LinkedList<_Link, Alloc>::operator[](const int& i){
     return this->at(i); 
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::forEach(Consumer<node_type> c){
    for(int i = 0; i < this->size; i++){
      c.accept(this[i]);
    }
  }

  DEFAULT_TEMPLATE_LIST
  bool LinkedList<_Link, Alloc>::operator!=(const Iterator<node_type>& i2) const noexcept{
    return iter_type::current != *i2;
  }

  DEFAULT_TEMPLATE_LIST
  bool LinkedList<_Link, Alloc>::operator==(const Iterator<node_type>& other) const noexcept{
    return iter_type::current == *other;
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> &LinkedList<_Link, Alloc>::operator++(){
    iter_type::prev = iter_type::current;
    iter_type::current = this->at(count);
    count++;
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> &LinkedList<_Link, Alloc>::operator++(int){
    iter_type temp = *this;
    ++*this;
    return temp;
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::begin() const noexcept{
    return this[0];
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::end() const noexcept{
<<<<<<< HEAD:src/util/collections/collections.cpp

  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::operator+(const int& i) noexcept{
    
=======
    return tail->next;
>>>>>>> e9e0d95232fc36cd0360d6162ad807a7f501a218:src/compiler/util/collections/collections.cpp
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type>& LinkedList<_Link, Alloc>::operator+(const int& i) noexcept{
    return this[iter_type::current + i];
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type>& LinkedList<_Link, Alloc>::operator-(const int& i) noexcept{
    return this[iter_type::current - i];
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::next(){
    return this[iter_type::current + 1];
  }

  DEFAULT_TEMPLATE_LIST
  Iterator<typename LinkedList<_Link, Alloc>::node_type> LinkedList<_Link, Alloc>::prev(){
    return iter_type::prev;
  }
  
  
}
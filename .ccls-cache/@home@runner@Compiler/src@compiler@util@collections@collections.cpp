#include "collections.hpp"

namespace util{
  
  template<typename Alloc>
  Alloc* Allocator<Alloc>::allocate(util::size_t size){
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

  template<typename Data, typename Alloc>
  void memcpy(Alloc& a, Data* src, Data* dest, int size, int offset){
    dest = a.allocate(size + offset);
    for(int i = offset; i < size + offset; i++){
      dest[i] = src[i - offset];
    }
    return;
  }

  template<typename Data, typename Alloc>
  void memcpy_basedOnSrc(Alloc& a, Data* src, Data* dest, int src_size, int offset){
    for(int i = offset; i < src_size + offset; i++) dest[i] = src[i];
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

  template <typename _String, typename Alloc>
  String<_String, Alloc>::String(){
    this->str = allocator.allocNum(1);
    str[0] = '\0';
    return;
  }

  template <typename _String, typename Alloc>
  String<_String, Alloc>::String(kPtr_type str){

  }

  template<typename _String, typename Alloc>
  String<_String, Alloc>::String(String<_String>& str){

  } 

  template<typename _String, typename Alloc>
  String<_String, Alloc>::String(String<_String>&& str){

  }


  DEFAULT_TEMPLATE_STRING
  void String<_String, Alloc>::concat(String<_String> &s)
  {
      ptr_type new_string = allocator.allocate(this->size + s.getSize());
      for (int i = 0; i < sizeof(new_string); i++)
      {
          new_string[i] = str[i];
          if (i == this->size)
          {
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
          int j;
          for (j = indStart; j < arr[i]; j++){
            str[j - indStart] = this->str[j]; 
          }
          this->pLastPos = j;
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

  DEFAULT_TEMPLATE_STRING 
  int String<_String, Alloc>::lastPos(){
    return this->pLastPos;
  }

  /*
  DEFAULT_TEMPLATE_STRING
  std::istringstream String<_String, Alloc>::makeStream(){
    return std::istringstream(this->asStdStr());
  }
  */

  template<typename _Link>
  Node<_Link>::Node(){
    prev = nullptr;
    next = nullptr;
  }

  template<typename _Link>
  Node<_Link>::Node(_Link data, SmartPointer<Node<_Link>> prev, SmartPointer<Node<_Link>> next){
    this->data = data;
    this->next = next;
    this->prev = prev;
  } 

  template<typename _Link>
  Node<_Link>::Node(Node<_Link>& n){
    this->data = n.data;
    this->next = n.next;
    this->prev = n.prev;
  }

  template<typename _Link>
  Node<_Link>::Node(Node<_Link>&& n){
    this->data = n.data;
    this->next = n.next;
    this->prev = n.prev;
  }

  template<typename _Link, typename Alloc>
  LinkedList<_Link, Alloc>::LinkedList(LinkedList<type>& ll){

  }

  template<typename _Link, typename Alloc>
  LinkedList<_Link, Alloc>::LinkedList(LinkedList<type>&& ll){

  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::push(_Link data){
    SmartPointer<Node<_Link>> new_node = new Node<_Link>(data, head, head->next);
    head->next->prev = new_node;
    head->next = new_node;
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
  _Link LinkedList<_Link, Alloc>::getFront(){
    return this->head->data;
  }

  DEFAULT_TEMPLATE_LIST
  _Link LinkedList<_Link, Alloc>::getBack(){
    return this->tail->data;
  }

  DEFAULT_TEMPLATE_LIST
  _Link LinkedList<_Link, Alloc>::getAt(int pos){
    SmartPointer<node_type> temp = head;
    int i = 0;
    while (temp->next != nullptr && i < pos){
      temp = temp->next;
      i++;
    }
    return temp->data;
  }

  DEFAULT_TEMPLATE_LIST
  SmartArray<int> LinkedList<_Link, Alloc>::find(_Link data){
      SmartArray<int> arr();
      int count = 0;
      for(int i = 0; i < this->size; i++){
        if(data == this[i]){
            arr[count]= i; 
            count++;
        }
      }
      return arr;
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
  _Link LinkedList<_Link, Alloc>::operator[](const int& i){
    return this->getAt(i);
  }


  DEFAULT_TEMPLATE_LIST
  LinkedList<_Link>& LinkedList<_Link, Alloc>::operator=(const LinkedList<_Link>& ll) noexcept{
    LinkedList<_Link> linkedList;
    for(int i = 0; i < ll.getSize(); i++){
      linkedList.append(ll[i]);
    }
    return ll;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::operator+=(const LinkedList<_Link>& ll) noexcept{
    for(int i = 0; i < ll.getSize(); i++){
      this->append(ll[i]);
    }
    return;
  }

  DEFAULT_TEMPLATE_LIST
  void LinkedList<_Link, Alloc>::forEach(Consumer<node_type> c){
    for(int i = 0; i < this->size; i++){
      c.accept(this[i]);
    }
  }

  DEFAULT_TEMPLATE_LIST
  SmartPointer<Node> LinkedList<_Link, Alloc>::nodeAt(int pos){
    SmartPointer<Node> temp = head;
    int count = 0;
    while(temp != nullptr && count < pos){
      temp = temp->next;
      count++;
    }
    return temp;
  }
  
  LinkedList<util::string> parse(util::string str, char delim){
      util::string sub = str.substr(0, delim);
      util::stringlist ret;
      ret.append(sub);
      for(int i = sub.getSize(); i < str.size(); i+= sub.getSize()){
        sub = str.substr(i, delim);
        ret.append(sub);
      }
      return ret;
  }  

  void operator+=(RelationalMap<ArOne, ArTwo> &rm){
    tOne tempOne = this->allocatorOne.allocate(this->pSize + rm.pSize);
    tTwo tempTwo = this->allocatorTwo.allocate(this->pSize + rm.pSize);

    memcpy_basedOnSrc(allocatorOne, this->oneUnder, tempOne, this->pSize);
    memcpy_basedOnsrc(allocatorTwo, this->twoUnder, tempTwo, this->psize);

    memcpy_basedOnSrc(allocatorOne, this->oneUnder, rm.oneUnder, rm.pSize, this->pSize);
    memcpy_basedOnSrc(allocatorOne, this->twoUnder, rm.twoUnder, rm.pSize, this->pSize);

    this->pSize += rm.pSize;

    memcpy(allocatorOne, tempOne, this->oneUnder, this->pSize);
    memcpy(allocatorTwo, tempTwo, this->twoUnder, this->pSize);
  }

  template<typename ArOne, typename ArTwo, typename AllocArOne, typename AllocArTwo>
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalMap(){
    this->oneUnder = this->allocatorOne.allocate(sizeof(ArOne));
    this->twoUnder = this->allocatorTwo.allocate(sizeof(ArTwo));
    this->pSize = 0;
  }

  template<typename ArOne, typename ArTwo, typename AllocArOne, typename AllocArTwo>
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalMap(int size){
      this->oneUnder = this->allocatorOne.allocate(sizeof(ArOne) * size);
      this->twoUnder = this->allocatorTwo.allocate(sizeof(ArTwo) * size);
      this->pSize = size;
  }

  template<typename ArOne, typename ArTwo, typename AllocArOne, typename AllocArTwo>
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalMap(ArOne data, ArTwo d){
    this->oneUnder = this->allocatorOne.allocate(sizeof(ArOne));
    this->twoUnder = this->allocatorTwo.allocate(sizeof(ArOne));

    this->oneUnder[0] = data;
    this->twoUnder[0] = d; 
    this->pSize = 1;
  }  

  template<typename ArOne, typename ArTwo, typename AllocArOne, typename AllocArTwo>
  RelationalMap<ArOne, ArTwom AllocArOne, AllocArTwo>::RelationalMap(RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>& rm){
    this->oneUnder = this->allocatorOne.allocate(sizeof(ArOne)* rm.size());
    this->twoUnder = this->allocatorTwo.allocate(sizeof(ArTwo) *rm.size());
    for(int i = 0; i < rm.size(); i++){
      oneUnder[i] = rm(i, 0);
      oneUnder[i] = rm(i, 1);  
    }
    this->pSize = rm.size();
  }

  template<typename ArOne, typename ArTwo, typename AllocArOne, typename AllocArTwo>
  RelationalMap<ArOne, ArTwom AllocArOne, AllocArTwo>::RelationalMap(RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>&& rm){
    this->oneUnder = this->allocatorOne.allocate(sizeof(ArOne)* rm.size());
    this->twoUnder = this->allocatorTwo.allocate(sizeof(ArTwo) *rm.size());
    for(int i = 0; i < rm.size(); i++){
      oneUnder[i] = rm(i, 0);
      oneUnder[i] = rm(i, 1);  
    }
    this->pSize = rm.size();
  }


  DEFAULT_TEMPLATE_MAP
  void RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::push(ArOne data, ArTwo d){
    ArOne* tempOne = this->allocatorOne.allocate(this->pSize + 1);
    ArTwo* tempTwo = this->allocatorOne.allocate(this->pSize + 1);
    tempOne[0] = data;
    tempTwo[0] = d;
    memcpy(this->allocatorOne, tempOne, this->oneUnder, this->pSize, 1);
    memcpy(this->allocatorTwo, tempTwo, this->twoUnder, this->pSize, 1);
    this->pSize += 1;
  }
  
  DEFAULT_TEMPLATE_MAP
  void RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::append(ArOne data, ArTwo d){
    ArOne* tempOne = this->allocatorOne.allocate(this->pSize + 1);
    ArOne* tempTwo = this->allocatorTwo.allocate(this->pSize + 1);

    memcpy(this->allocatorOne, this->oneUnder, tempOne, this-pSize + 1);
    memcpy(this->allocatorTwo, this->twoUnder, tempTwo, this->pSize + 1);

    tempOne[this->pSize] = data;
    tempTwo[this->pSize] = d;

    this->pSize += 1;

    memcpy(this->allocatorOne, tempOne, this->oneUnder, this->pSize);
    memcpy(this->allocatorTwo, tempTwo, this->twoUnder, this->pSize);

    return;    

  }

  DEFAULT_TEMPLATE_MAP
  void RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::insert(void* (function)(ArOne)(ArTwo)(int), ArOne data, ArTwo d, int pos){
      function(data, d, pos);
      this->pSize += 1;
      return;
  }

  DEFAULT_TEMPLATE_MAP
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalData RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::get(int index){
    RelationalData rd;
    if(index < size){
      rd.dataOne = oneUnder[index];
      rd.dataTwo = oneUnder[index];
    }
    return rd;
  }

  DEFAULT_TEMPLATE_MAP
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalData RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::get(RelationalData* (function)){
    return function();
  }

  DEFAULT_TEMPLATE_MAP
  void RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::before(ArOne d, ArTwo dat, int pos){
    tOne tempOne = this->allocatorOne.allocate(this->pSize + 1);
    tTwo tempTwo = this->allocatorTwo.allocate(this->pSize + 1);

    for(int i = 0; i < this->pSize + 1; i++){
      tempOne[i] = this->underOne[i];
      tempTwo[i] = this->underTwo[i];
      if(i == pos - 1){
        tempOne[i] = d;
        tempTwo[i] = dat;
      }
    }

    memcpy(allocatorOne, tempOne, underOne, this->pSize + 1);
    memcpy(allocatorTwo, tempTwo, underTwo, this->pSize + 1);

    return;
  }


  DEFAULT_TEMPLATE_MAP
  void RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::after(ArOne d, ArTwo dat, int pos){
    tOne tempOne = this->allocatorOne.allocate(this->pSize + 1);
    tTwo tempTwo = this->allocatorTwo.allocate(this->pSize + 1);

    for(int i = 0; i < this->pSize + 1; i++){
      tempOne[i] = this->underOne[i];
      tempTwo[i] = this->underTwo[i];
      if(i == pos + 1){
        tempOne[i] = d;
        tempTwo[i] = dat;
      }
    }

    memcpy(allocatorOne, tempOne, underOne, this->pSize + 1);
    memcpy(allocatorTwo, tempTwo, underTwo, this->pSize + 1);

    return;
  }

  DEFAULT_TEMPLATE_MAP
  void RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::forEach(ConsumerTwo<ArOne, ArTwo> c){
    for(int i = 0; i < this->pSize; i++){
      c.accept(this->oneUnder[i], this->twoUnder[i]);
    }
  }

  DEFAULT_TEMPLATE_MAP
  size_t RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::size(){
    return this->pSize;
  }

  DEFAULT_TEMPLATE_MAP
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalData& RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::operator[](int &i){
    return this->get(i);
  }


  DEFAULT_TEMPLATE_MAP
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::Data& RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::operator()(int& idOne, int &idTwo){
    Data d;
    switch(indTwo){
      case 0:
        d.dataOne = this[indOne].dataOne;
        break;
      case 1:
        d.dataTwo = this[indOne].dataTwo;
        break;
      default:
        break;
    }
    return d;
  }

  DEFAULT_TEMPLATE_MAP
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalData RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::front(){
    return this->get(0);
  }

  DEFAULT_TEMPLATE_MAP
  RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::RelationalData RelationalMap<ArOne, ArTwo, AllocArOne, AllocArTwo>::back(){
    return this->get(this->pSize - 1);
  }



}
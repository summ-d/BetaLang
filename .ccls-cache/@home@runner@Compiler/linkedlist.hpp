

template<typename LinkType, typename Alloc = Allocator<LinkType>>
class LinkedList: public CollectionsBase<LinkType>{
  public:
  class Node{
    public:
    SmartPointer<Node> next;
    SmartPointer<Node> prev;
    LinkType data;
    Node(LinkType data){ this->data = data;}
    Node(){
      next = nullptr;
      prev = nullptr;
    }
  };
  
  private:

  SmartPointer<Node> first = nullptr;
  SmartPointer<Node> last = nullptr;

  Allocator<LinkedList<LinkType>> nodeAlloc;
  Allocator<LinkType> allocLink;

  typedef CollectionsBase<LinkType> Collections;

  Node** makeNodes(int size){
    return new Node*[size];
  }
  
  public:

  LinkedList(LinkType data){
    first = new Node(data);
    last = new Node();
    first->prev = nullptr;
    first->next = last;
    last->prev = first;
    last->next = nullptr;
  }
  LinkedList(){
    first = new Node();
    last = new Node();
  }

  LinkedList(LinkType data[], int size){
    SmartPointer<Node*> nodes = makeNodes(size - 1);
    front = new Node(data[0]);
    last = new Node();
    for(int i = 1; i < (size - 2); i++){
      nodes[i - 1]->data = data[i]
      nodes[i - 1]->prev = nodes[i - 2];
      nodes[i - 1]->next = nodes[i];
      if(i == 1){
        nodes[i]->prev = front;
      } 
    }
    nodes[size - 1]->prev = nodes[size - 2];
    nodes[size - 1]->data = data[size - 1];
    nodes[size - 1]->next = last;
  }


  size_t getSize() override{
    SmartPointer<Node> temp = first;
    size_t count = 0;
    while(temp != nullptr){
      temp = temp->next;
      count++;
    }
    delete temp;
    return count;
  }
  
  void forEach(Consumer<LinkType> c) override{
    SmartPointer<Node> temp = first;
    while(temp != nullptr){
      c.accept(temp->data);
      temp = temp->next;
    }
    return;
  }

  void append(LinkType data) override{
    SmartPointer<Node> new_node;
    new_node->data = data;
    new_node->prev = last;
    new_node->next = nullptr;
    last->next = new_node;
    last = new_node;
    return;
  }

  void insert(int pos, u8 pol, LinkType data) override{
    SmartPointer<Node> new_node;
    SmartPointer<Node> temp = first;
    for(int i = 0; i < pos - (pol == Collections::BEFORE) ?  1 : 0; i++){
      temp = temp->next;
    }
    new_node->data = data;
    new_node->prev = temp->prev;
    new_node->next = temp->next;
    temp->prev = new_node;
    return;
  }

  void push(LinkType data) override{
    SmartPointer<Node> new_node;
    new_node->prev = nullptr;
    new_node->next = first;
    first->prev = new_node;
    return;
  }

  bool isEmpty() override{
    return this->getSize() == 0;
  }

  void *nuke() override{
    SmartPointer<Node> node = first;
    SmartPointer<Node> temp;

    while(node != nullptr){
      temp = node;
      delete temp;
      node = node->next;
    }

    delete node;
    delete temp;
    delete this;
    return nullptr;
  }

  // Warning!!! only works on primitive types and any that override the operator
  // `==`
  option::Option<int*> find(LinkType c) override{
    int* a;
    option::Option<int*> arr;
    SmartPointer<Node> node = first;
    int i = 0;
    int j = 0;
    while(node != nullptr){
      arr.set_output(false);
      if(node->data == c){
        arr.set_output(true);
        arr[j] = i;
        j++;
      }
      i++;
    }
    return arr;
  }

  option::Option<int> findFirst(LinkType c) override{
    option::Option<int> pos;
    SmartPointer<Node> node = first;
    int i = 0;
    while(node != nullptr){
      if(c == node->data){
        pos.set_output(true);
        pos = i;
        return pos;
      }
      i++;
    }
    return pos;
  }

  //TODO
  void sort(u8 pol) override{}

  LinkType front(){
    return this->first->data;
  }

  LinkType back(){
    return this->last->data;
  }

  LinkType at(int pos){
    SpecialPointer<Node> node = front;
    int i = 0; 
    while (node != nullptr){
      if(i == pos){
        return node->data;
      }
      node = node->next;
      i++;
    }
    return nullptr;
  }

  Node* getNodeAt(int pos){
    SmartPointer<Node> node = first;
    int i = 0;
    while (node != nullptr) {
      if(i == pos){
        return node;
      }
      node = node->next;
      i++;
    }
    return nullptr;
  }

  Node* getFirstNode(){
    return first;
  }

  Node* getLastNode(){
    return last;
  }

  LinkType& operator[](int pos){
    return this->at(pos);
  }
};

template<typename LnkTpe>
constexpr bool operator==(const LinkedList<LnkTpe>& ll1, const LinkedList<LnkTpe>& ll2){
  for (int i = 0; ll1.getNodeAt(i) != nullptr || ll2.getNodeAt(i) != nullptr; i++){
    if(ll1.getNodeAt(i)->data != ll2.getNodeAt(i)->data){
      return false;
    }
  }
  return true;
}
enum ListErrors {
             ListOk        =  0,
         NullptrCaught     =  1,
    ErasementOfUnknownNode =  2,
};

class ListHead;

template <class Type> class ListNode {
    ListHead<Type> *head;

    ListNode<Type> *next;
    ListNode<Type> *prev;

    Type *object;

    public:
        ListNode(Type *object, ListNode<Type> *prev, ListNode<Type> *next):
               object (object),
                                   prev (prev),
                                                   next (next)
        {}

        ListErrors setPrev(ListNode<Type> *newPrev) {  this -> prev = newPrev;  }
        ListErrors setNext(ListNode<Type> *newNext) {  this -> next = newNext;  }

        ListNode<Type> *getPrev() {  return this -> prev;  }
        ListNode<Type> *getNext() {  return this -> next;  }

        ListHead *getHead() {  return this -> head;  }
};

template <class Type> class ListHead {
    
    ListNode<Type> *head;

    size_t size;

    public:
        ListHead():
        size (   0   ),
        head (nullptr)
        {}

        ListErrors  pushBack(Type *object);
        ListErrors pushFront(Type *object);

        ListErrors erase(ListNode<Type> *node);

        ListNode<Type>* getHead() { return this->head; }
};
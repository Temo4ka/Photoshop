enum ListErrors {
             ListOk        =  0,
         NullptrCaught     =  1,
    ErasementOfUnknownNode =  2,
};

template <class Type> class ListHead;

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

        void setPrev(ListNode<Type> *newPrev) {  this -> prev = newPrev;  }
        void setNext(ListNode<Type> *newNext) {  this -> next = newNext;  }

        ListNode<Type>  *getPrev () {  return this ->  prev ;  }
        ListNode<Type>  *getNext () {  return this ->  next ;  }

        ListHead<Type>  *getHead () {  return this ->  head ;  }

             Type      *getObject() {  return this -> object; }

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

#include "DSL.h"

template <class Type>
ListErrors ListHead<Type>::pushBack(Type *object) {
    catchNullptr(object, NullptrCaught);

    if (this -> head == nullptr) {

        this -> head = new ListNode<Type>(object, nullptr, nullptr);     
       (this -> head) -> setPrev(this -> head);
       (this -> head) -> setNext(this -> head);

       return ListOk;
    }

    ListNode<Type> *nodePrev = (this -> head) -> getPrev();
    ListNode<Type> *nodeNext =  this -> head;

    ListNode<Type>  *newNode = new ListNode<Type>(object, nodePrev, nodeNext);
    nodePrev -> setNext(newNode);
    nodeNext -> setPrev(newNode);

    (this -> size)++;

    return ListOk;
}

template <class Type>
ListErrors ListHead<Type>::pushFront(Type *object) {
    catchNullptr(object, NullptrCaught);

    ListErrors err = this -> pushBack(object);
    if (err) return err;

    this -> head = (this -> head) -> getPrev();

    return ListOk;
}

template <class Type>
ListErrors ListHead<Type>::erase(ListNode<Type> *node) {
    catchNullptr(node, NullptrCaught);

    if (node->getHead() != this) return ErasementOfUnknownNode;

    if (node -> getNext() == node) {
        delete node;
        node = nullptr;
        return ListOk;
    }

    ListNode<Type> *prev = node -> getPrev();
    ListNode<Type> *next = node -> getNext();

    delete node;
    node = nullptr;

    prev -> setNext(next);
    next -> setPrev(prev);

    (this -> size)--;

    return ListOk;
}
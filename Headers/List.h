#pragma once

#include <stdint.h>
#include "DSL.h"

enum ListErrors {
             ListOk        =  0,
         NullptrCaught     =  1,
    ErasementOfUnknownNode =  2,
};

template <class Type>
class ListHead;

template <class Type>
class ListNode {
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

        ~ListNode() { delete object; }
};

template <class Type>
class ListHead {
    
    ListNode<Type> *head;

    size_t size;

    public:
        ListHead():
        size (   0   ),
        head (nullptr)
        {}

        ListErrors  pushBack(Type *object);
        ListErrors pushFront(Type *object);

        ListErrors eraseNode(ListNode<Type> *node);
        ListErrors   erase  (Type *object);
        
        ListNode<Type>* getNode(Type *object);

        ListNode<Type>* getHead() { return head; }

        size_t getSize() {  return size;  }

        ~ListHead()
        {
            if (head == nullptr) return;

            ListNode<Type> *cur = head -> getNext();

            while (cur != head) {
                ListNode<Type> *next = cur -> getNext();
                delete cur;
                cur = next;
            }

            delete cur;
        }
};

template <class Type>
ListErrors ListHead<Type>::pushBack(Type *object) {
    catchNullptr(object, NullptrCaught);

    (this -> size)++;

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
ListErrors ListHead<Type>::erase(Type *object) {
    catchNullptr(object, NullptrCaught);

    ListNode <Type> *objectNode = getNode(object);
    if (objectNode == nullptr) return ListOk;

    return eraseNode(objectNode);
}

template <class Type>
ListErrors ListHead<Type>::eraseNode(ListNode<Type> *node) {
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

#include <cstring>

template <class Type>
ListNode<Type>* ListHead<Type>::getNode(Type *object) {
    catchNullptr(object, nullptr);

    ListNode <Type> *cur = head;

    if (cur == nullptr) return nullptr;

    do {
        if (!memcmp((cur ->getObject()), object, sizeof(Type)))
            return cur;

        cur = cur -> getNext();
    } while (cur != head);

    return nullptr;
}
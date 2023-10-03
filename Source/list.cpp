#include "../Headers/List.h"
#include "DSL.h"

ListErrors ListHead::pushBack(Type *object) {
    catchNullptr(object, NullptrCaught);

    if (this -> head == nullptr) {
        this -> head = new ListNode(object, nullptr, nullptr);     
       (this -> head) -> setPrev(this -> head);
       (this -> head) -> setNext(this -> head);

       return ListOk;
    }

    ListNode *nodePrev = (this -> head) -> getPrev();
    ListNode *nodeNext =  this -> head;

    ListNode *newNode = new ListNode(object, nodePrev, nodeNext);
    nodePrev -> setNext(newNode);
    nodeNext -> setPrev(newNode);

    (this -> size)++;

    return ListOk;
}

ListErrors ListHead::pushFront(Type *object) {
    catchNullptr(object, NullptrCaught);

    ListErrors err = this -> pushBack(object);
    if (err) return err;

    this -> head = (this -> head) -> getPrev();

    return ListOk;
}

ListErrors ListHead::erase(ListNode *node) {
    catchNullptr(node, NullptrCaught);

    if (node->getHead() != this) return ErasementOfUnknownNode;

    if (node -> getNext() == node) {
        delete node;
        node = nullptr;
        return ListOk;
    }

    ListNode *prev = node -> getPrev();
    ListNode *next = node -> getNext();

    delete node;
    node = nullptr;

    prev -> setNext(next);
    next -> setPrev(prev);

    (this -> size)--;

    return ListOk;
}
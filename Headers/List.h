enum ListErrors {
             ListOk        =  0,
         NullptrCaught     =  1,
    ErasementOfUnknownNode =  2,
};

class ListHead;

class ListNode {
    ListHead *head;

    ListNode *next;
    ListNode *prev;

    void *object;

    public:
        ListNode(void *object, ListNode* prev, ListNode *next):
               object (object),
                                   prev (prev),
                                                   next (next)
        {}

        ListErrors setPrev(ListNode *newPrev) {  this -> prev = newPrev;  }
        ListErrors setNext(ListNode *newNext) {  this -> next = newNext;  }

        ListNode *getPrev() {  return this -> prev;  }
        ListNode *getNext() {  return this -> next;  }

        ListHead *getHead() {  return this -> head;  }
};

class ListHead {
    ListNode *head;

    size_t size;

    public:
        ListHead():
        size (   0   ),
        head (nullptr)
        {}

        ListErrors  pushBack(void *object);
        ListErrors pushFront(void *object);

        ListErrors erase(ListNode *node);
};
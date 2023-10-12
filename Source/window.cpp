#include "../Headers/Widgets.h"

int Window::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    (rt->getWindow())->draw(*(this->getSprite()));

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Window::addChild(Widget *widget) {
    catchNullptr(widget, EXIT_FAILURE);

    ListHead<Widget> *list = this -> getList();
    list -> pushBack(widget);

    return EXIT_SUCCESS;
}

int Window::removeChild(Widget *widget) {
    catchNullptr(widget, EXIT_FAILURE);

    ListHead<Widget> *list = this -> getList();
    ListNode<Widget> *cur  = list -> getHead();
    do {
        if (cur -> getObject() == widget) {
            list ->erase(cur);
            break;
        }
    } while (cur != list -> getHead());

    return EXIT_SUCCESS;
}

int Window::onMouseClick(Vect &mouse) {
    // if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
    //     POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y )
    //     return EXIT_SUCCESS;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> onMouseClick(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Window::onMouseMove(Vect &mouse) {
    // if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
    //     POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y )
    //     return EXIT_SUCCESS;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> onMouseMove(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Window::onMouseReleased(Vect &mouse) {
    // if (POSITION.x > mouse.x || POSITION.x + SIZE.x < mouse.x ||
    //     POSITION.y > mouse.y || POSITION.y + SIZE.y < mouse.y )
    //     return EXIT_SUCCESS;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> onMouseReleased(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}
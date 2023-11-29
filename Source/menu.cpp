#include "../Headers/Widgets.h"

int Menu::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);

    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);

        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
        
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Menu::onMousePress(Vect &mouse) {
    if (POSITION.x > mouse.x || POSITION.x + THIS_SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + THIS_SIZE.y < mouse.y || getStatus() == Disable)
        return EXIT_SUCCESS;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> onMousePress(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Menu::onMouseMove(Vect &mouse) {
    if (POSITION.x > mouse.x || POSITION.x + THIS_SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + THIS_SIZE.y < mouse.y )
        return EXIT_SUCCESS;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> onMouseMove(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Menu::onMouseRelease(Vect &mouse) {
    if (POSITION.x > mouse.x || POSITION.x + THIS_SIZE.x < mouse.x ||
        POSITION.y > mouse.y || POSITION.y + THIS_SIZE.y < mouse.y )
        return EXIT_SUCCESS;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> onMouseRelease(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

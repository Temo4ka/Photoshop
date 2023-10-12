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
        // fprintf(log, "%p Here!!!\n", cur);
        
    } while (cur != (this -> getList()) -> getHead());

    // fclose(log);

    return EXIT_SUCCESS;
}

int Menu::onMouseClick(Vect &mouse) {
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

int Menu::onMouseMove(Vect &mouse) {
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

int Menu::onMouseReleased(Vect &mouse) {
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

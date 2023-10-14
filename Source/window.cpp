#include "../Headers/Widgets.h"

int Window::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    for (int i = 0; i < this->getRegionSet()->getSize(); i++) {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();

        (this->getSprite())->setTextureRect(sf::IntRect(curPos.x - POSITION.x, curPos.y - POSITION.y, curSize.x, curSize.y));

        (this->getSprite())->setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(*(this->getSprite()));

        curRegionNode = curRegionNode -> getNext();
    }

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

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
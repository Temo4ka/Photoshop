#include "../Headers/Widgets.h"
#include <cmath>

Window::Window(Vect pos, Vect size, sf::Texture *texture, sf::Sprite *sprite):
        Widget(pos, size, texture, TEST_PIC_WIDTH, TEST_PIC_HEIGHT, sprite),
        status(Status::Still),
        lastPoint(Vect(0, 0))
{

}

int Window::draw(RenderTarget *rt) {
    catchNullptr(rt, EXIT_FAILURE);
    if (this -> getStatus() == Disable) return EXIT_SUCCESS;

    ListNode<Region> *curRegionNode = ((this->getRegionSet())->getHead())->getHead();
    do {
        Region *curRegion = curRegionNode->getObject();

        Vect curPos  = curRegion->getPos();
        Vect curSize = curRegion->getSize();
        Vect  scale  = this -> getScale();

        (this->getSprite())->setTextureRect(sf::IntRect((curPos.x - POSITION.x) / scale.x, (curPos.y - POSITION.y) / scale.y,
                                                        ceil(curSize.x / scale.x), ceil(curSize.y / scale.y)));

        (this->getSprite())->setPosition(curPos.x, curPos.y);

        (rt->getWindow())->draw(*(this->getSprite()));

        curRegionNode = curRegionNode -> getNext();
    } while (curRegionNode != ((this->getRegionSet())->getHead())->getHead());

    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);

        (cur -> getObject()) -> draw(rt);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Window::onMousePress(Vect &mouse) {
    if (mouse.y < POSITION.y + PANEL_HEIGHT * getScale().y) {
        lastPoint = mouse;
         status   = Status::OnMove;
    }
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        if ((cur -> getObject()) -> isInWidgetArea(mouse))
            (cur -> getObject()) -> onMousePress(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Window::onMouseMove(Vect &mouse) {
    if (status == Status::OnMove) {
        // setPosition(getPosition() + mouse - lastPoint);
        move(mouse - lastPoint);
        lastPoint = mouse;
    }
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);
        if ((cur -> getObject()) -> isInWidgetArea(mouse))
            (cur -> getObject()) -> onMouseMove(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

int Window::onMouseRelease(Vect &mouse) {
    status = Status::Still;
    
    ListNode<Widget>* cur = (this -> getList()) -> getHead();
    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        catchNullptr(cur -> getObject(), EXIT_FAILURE);

        if ((cur -> getObject()) -> isInWidgetArea(mouse))
            (cur -> getObject()) -> onMouseRelease(mouse);

        cur = cur -> getNext();
    } while (cur != (this -> getList()) -> getHead());

    return EXIT_SUCCESS;
}

bool Widget::isInWidgetArea(Vect point) {
    if (point.x < position.x || point.x > position.x + size.x ||
        point.y < position.y || point.y > position.y + size.y   )
        return false;

    return true;
}

bool Widget::isInWidgetRegion(Vect point) {

    ListNode<Region> *curNode = set -> getHead() -> getHead();
    do {
        catchNullptr(curNode, false);
        Region *curRegion = curNode -> getObject();
        catchNullptr(curRegion, false);

        if ( (point.x >= curRegion->getPos().x && point.x <= curRegion->getPos().x + curRegion->getSize().x) &&
             (point.y >= curRegion->getPos().y && point.y <= curRegion->getPos().y + curRegion->getSize().y)   )
            return true;

        curNode = curNode -> getNext();
    } while (curNode != set -> getHead() -> getHead());

    return false;
}
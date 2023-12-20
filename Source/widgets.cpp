#include "../Headers/Widgets.h"

int Widget::deleteWidget() {
    ListNode<Widget>* curNode = (getList()) -> getHead();
    if (curNode == nullptr) return EXIT_FAILURE;

    do {
        catchNullptr(curNode -> getObject(), EXIT_FAILURE);

        (curNode -> getObject()) -> deleteWidget();

        curNode = curNode -> getNext();
    } while (curNode != (getList()) -> getHead());

    delete this;

    return EXIT_SUCCESS;
}

int Widget::pushBackSubWidget(Widget *widget) {
    catchNullptr(widget , EXIT_FAILURE);

    // RegionSet *subSet = widget->getRegionSet();
    // RegionSet *newSet =  set->subRegions(subSet);

    // delete set;
    // set = newSet;


    ListHead<Widget> *list = this -> getList();
    list -> pushBack(widget);

    return EXIT_SUCCESS;
}

int Widget::pushFrontSubWidget(Widget *widget) {
    catchNullptr(widget , EXIT_FAILURE);

    // RegionSet *subSet = widget->getRegionSet();
    // RegionSet *newSet =  set->subRegions(subSet);

    // delete set;
    // set = newSet;


    ListHead<Widget> *list = this -> getList();
    list -> pushFront(widget);

    return EXIT_SUCCESS;
}

void Widget::move(Vect delta) {
    position += delta;

    ListNode<Widget>* curNode = (getList()) -> getHead();
    if (curNode == nullptr) return;

    do {
        catchNullptr(curNode -> getObject(), );

        (curNode -> getObject()) -> move(delta);

        curNode = curNode -> getNext();
    } while (curNode != (getList()) -> getHead());

    return;
}

int Widget::removeSubWidget(Widget *widget) {
    catchNullptr(widget , EXIT_FAILURE);

    ListHead<Widget> *list = this -> getList();
    ListNode<Widget> *cur  = list -> getHead();

    if (cur == nullptr) {
        EXECUTE_ERROR(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    do {
        if (cur -> getObject() == widget) {
            RegionSet *subSet = widget->getRegionSet(); 
            set -> unionRegions(subSet);

            list ->eraseNode(cur);
            break;
        }
    } while (cur != list -> getHead());

    return EXIT_SUCCESS;
}

int Widget::clipRegions() {
    ListHead<Widget> *list = this -> getList();
    ListNode<Widget> *cur  = list -> getHead();

    if (cur == nullptr) return EXIT_SUCCESS;

    do {
        if (cur == nullptr) {
            EXECUTE_ERROR(EXIT_FAILURE);
            return EXIT_FAILURE;
        }

        Widget *curWidget = cur->getObject();

        if (curWidget -> getStatus() == Disable) {
            cur = cur -> getNext();
            continue;
        }

        delete curWidget -> getRegionSet();
        RegionSet *subSet =  new RegionSet();
        subSet -> addRegion(new Region(curWidget->getPosition(), curWidget ->  getSizeVect ()));

        RegionSet *newSet = set -> crossRegions(subSet);
        delete subSet;
        subSet = newSet;


        newSet = set -> subRegions(subSet);
        // MESSAGE("%lg, %lg", set -> getHead() -> getHead() -> getObject() -> getSize().x,
        //                 set -> getHead() -> getHead() -> getObject() -> getSize().y);
        delete set;
        set = newSet;
        curWidget -> setRegionSet(subSet);

        curWidget -> clipRegions();

        cur = cur -> getNext();
    } while (cur != list -> getHead());

    return EXIT_SUCCESS;
}

void Widget::dumpRegions(sf::RenderWindow *window) {
    set -> dump(window);

    ListNode<Widget> *cur = subWidgets->getHead();
    do {
        if (cur == nullptr) return;

        if (cur -> getObject() -> getStatus() == Disable) {
            cur = cur ->getNext();
            continue;
        }

        cur -> getObject() -> getRegionSet() -> dump(window);
        cur -> getObject() -> dumpRegions(window);
        cur = cur ->getNext();
    } while(cur != subWidgets -> getHead());

    return;
}

bool Widget::onMouseMove(plugin::MouseContext context) {
    Vect pos = Vect(context.position.x, context.position.y);

    this -> onMouseMove(pos);   

    return true;
}

bool Widget::onMouseRelease (plugin::MouseContext context) {
    Vect pos = Vect(context.position.x, context.position.y);

    this -> onMouseRelease(pos);

    return true;
}

bool Widget::onMousePress(plugin::MouseContext context) {
    Vect pos = Vect(context.position.x, context.position.y);

    this -> onMousePress(pos);

    return true;
}

void Widget::registerSubWidget  (plugin::WidgetI* object) {
    
    return;
}

void Widget::unregisterSubWidget(plugin::WidgetI* object) {

    return;
}
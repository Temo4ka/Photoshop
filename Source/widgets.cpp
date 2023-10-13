#include "../Headers/Widgets.h"

int Widget::addSubWidget(Widget *widget) {
    catchNullptr(widget , EXIT_FAILURE);

    RegionSet *subSet = widget->getRegionSet();
    RegionSet *newSet =  set->subRegions(subSet);

    delete set;
    set = newSet;

    ListHead<Widget> *list = this -> getList();
    list -> pushBack(widget);

    return EXIT_SUCCESS;
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

            list ->erase(cur);
            break;
        }
    } while (cur != list -> getHead());

    return EXIT_SUCCESS;
}

int Widget::clipRegions() {

    ListHead<Widget> *list = this -> getList();
    ListNode<Widget> *cur  = list -> getHead();

    if (cur == nullptr) {
        EXECUTE_ERROR(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    delete set;
    set = new RegionSet;
    set -> addRegion(new Region(position, size));

    do {
        if (cur == nullptr) {
            EXECUTE_ERROR(EXIT_FAILURE);
            return EXIT_FAILURE;
        }

        Widget *curWidget = cur->getObject();

        RegionSet *subSet =  new RegionSet();
        subSet -> addRegion(new Region(curWidget->getPosition(), curWidget -> getSize())); 
        set -> subRegions(subSet);
        curWidget -> set = subSet;
        
        curWidget->clipRegions();

    } while (cur != list -> getHead());

    return EXIT_SUCCESS;
}
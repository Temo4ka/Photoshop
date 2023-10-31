#include "../Headers/Events.h"
#include "../Headers/Widgets.h"
#include "../Headers/UI.h"
#include <stdlib.h>

int EventManager::executeEvent(Events event, sf::RenderWindow *window) {
    ListNode <Widget> *curNode = scene -> getHead();

    do {
        catchNullptr(curNode, EXIT_FAILURE);
        Widget *curWidget = curNode -> getObject();
        catchNullptr(curWidget, EXIT_FAILURE);

        if (curWidget -> getPriority() < this -> getPriority()) {
            curNode = curNode -> getNext();
            continue;
        }
        
        switch (event) {

            case Events::MouseLeftClick: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                curWidget -> onMouseClick(pos);
                clipRegions((Window *) curWidget);
                break;
            }
            
            case Events::MouseLeftRelease: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                curWidget -> onMouseReleased(pos);
                clipRegions((Window *) curWidget);
                break;
            }
            
            case Events::MouseMove: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                curWidget -> onMouseMove(pos);
                clipRegions((Window *) curWidget);
                break;
            }
            
            default:
                break;
        }

        curNode = curNode -> getNext();
    } while (curNode != scene -> getHead());

    return EXIT_SUCCESS;
}

int EventManager::addWidget(Widget *widget) {
    catchNullptr(widget, EXIT_FAILURE);

    scene -> pushBack(widget);

    return EXIT_SUCCESS;
}
#include "../Headers/Events.h"
#include "../Headers/Widgets.h"
#include "../Headers/UI.h"
#include <stdlib.h>

int EventManager::executeEvent(Events event, sf::RenderWindow *window) {
    ListNode <plugin::EventProcessableI> *curNode = scene -> getHead();

    do {
        catchNullptr(curNode, EXIT_FAILURE);
        plugin::EventProcessableI *curWidget = curNode -> getObject();
        catchNullptr(curWidget, EXIT_FAILURE);

        if (curWidget -> getPriority() < priority) {
            curNode = curNode -> getNext();
            continue;
        }
        
        switch (event) {

            case Events::MouseLeftClick: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                curWidget -> onMousePress(pos);
                clipRegions((Window *) curWidget);
                break;
            }
            
            case Events::MouseLeftRelease: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                Vect pos = Vect(mousePos.x, mousePos.y);
                curWidget -> onMouseRelease(pos);
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

void EventManager::registerObject(plugin::EventProcessableI *object) {
    catchNullptr(object, );

    scene -> pushBack(object);

    return;
}


void EventManager::unregisterObject(plugin::EventProcessableI *object) {
    catchNullptr(object, );

    scene -> erase(object);

    return;
}

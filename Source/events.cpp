#include "../Headers/Events.h"
#include "../Headers/Widgets.h"
#include "../Headers/UI.h"
#include <stdlib.h>

int EventManager::executeEvent(Events event, sf::RenderWindow *window, plugin::KeyboardContext key) {
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

                plugin::Vec2 pos = Vec2(mousePos.x, mousePos.y);
                plugin::MouseContext context = MouseContext(pos, MouseButton::Left);

                curWidget -> onMousePress(context);
                clipRegions((Window *) curWidget);
                break;
            }
            
            case Events::MouseLeftRelease: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                plugin::Vec2 pos = Vec2(mousePos.x, mousePos.y);
                plugin::MouseContext context = MouseContext(pos, MouseButton::Left);

                curWidget -> onMouseRelease(context);

                clipRegions((Window *) curWidget);
                break;
            }
            
            case Events::MouseMove: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                plugin::Vec2 pos = Vec2(mousePos.x, mousePos.y);
                plugin::MouseContext context = MouseContext(pos, MouseButton::Left);

                curWidget -> onMouseMove(context);
                
                clipRegions((Window *) curWidget);
                break;
            }
            
            case Events::KeyPressed {
                curWidget -> onKeyPressed(key);
                
                clipRegions((Window *) curWidget);
                break;
            }

            case Events::KeyReleased {
                curWidget -> onKeyReleased(key);
                
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

#pragma once

#include "List.h"
#include <SFML/Graphics.hpp>

class Widget;

class EventProcessible {
    unsigned priority;

    public:

        enum Events {
             MouseLeftClick   = 1,
            MouseLeftRelease  = 2,
                MouseMove     = 3,
            MouseRightRelease = 4,
             MouseRightClick  = 5,

            KeyESC   = 6,
            KeySPACE = 7
        } event;

        EventProcessible(unsigned priority):
                        priority (priority)
        {}

        void setPriority(unsigned priority) { this->priority = priority; }

        unsigned getPriority() { return priority; }
};

class EventManager : public EventProcessible { 
    ListHead <Widget> *scene;
    
    public:
        EventManager():
        EventProcessible(0),
        scene(new ListHead<Widget>())
        {}

        int executeEvent(Events event, sf::RenderWindow *window);

        int addWidget(Widget *widget);

        ~EventManager() { delete scene; }
};
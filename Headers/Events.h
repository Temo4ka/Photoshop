#pragma once

#include "Config.h"
#include "List.h"
#include <SFML/Graphics.hpp>
#include "plugin.h"

class Widget;

class EventProcessible : plugin::EventProcessableI {
    uint8_t priority;

    public:
        EventProcessible(unsigned priority):
                        priority (priority)
        {}

        void setPriority(unsigned priority) { this->priority = priority; }

        uint8_t getPriority() { return priority; }

        virtual bool onMouseMove    (plugin::MouseContext context) = 0;
        virtual bool onMouseRelease (plugin::MouseContext context) = 0;
        virtual bool onMousePress   (plugin::MouseContext context) = 0;

        virtual bool onKeyboardPress  (plugin::KeyboardContext context) = 0;
        virtual bool onKeyboardRelease(plugin::KeyboardContext context) = 0;

        bool onClock(uint64_t delta) {return false;}

};

class EventManager : public plugin::EventManagerI {
    uint8_t priority;

    ListHead <plugin::EventProcessableI> *scene;
    
    public:

        enum Events {
            MouseLeftClick   = 1,
            MouseLeftRelease  = 2,
                MouseMove     = 3,
            MouseRightRelease = 4,
            MouseRightClick  = 5,

            KeyPressed    = 6,
            KeyReleased   = 7,
        };

        EventManager():
        scene(new ListHead <plugin::EventProcessableI>())
        {
            priority = LOW_PRIORITY;
        }

        int executeEvent(Events event, sf::RenderWindow *window, plugin::KeyboardContext key);

        void registerObject(plugin::EventProcessableI *object);
        
        void unregisterObject(plugin::EventProcessableI *object);

        void setPriority(plugin::EventType, uint8_t priority) { this->priority = priority; }

        ~EventManager() { delete scene; }
};
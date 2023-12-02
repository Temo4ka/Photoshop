#pragma once

#include "Widgets.h"
#include <string>

class EditBox : public Widget {
    std::string curString;

    sf::Font *font;

    bool isWriting;

    bool isPeriodPlaced;

    enum BoxType {
        Text = 0,
        Num  = 1
    } type;

    public:

        EditBox(Vect pos, Vect size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite):
        Widget(pos, size, texture, texW, texH, sprite),
          curString   (std::string()),
          isWriting   (false),
        isPeriodPlaced(false),
        font(new sf::Font()),
        type(BoxType::Num)
        {
            font->loadFromFile("./Font/arial.ttf");
        }

        void addNewLetter(const char *letter);
        void  eraseLetter();

        const char* translateLetter(plugin::KeyboardContext letter); 

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease (Vect &pos);

        bool onKeyboardPress  (plugin::KeyboardContext context) override;
        bool onKeyboardRelease(plugin::KeyboardContext context) override;

        void setType(BoxType newType) { type = newType; }

	    uint8_t getPriority() { return HIGH_PRIORITY; }

        const char* getString() { return curString.c_str(); }

        double getNum() { return (type == BoxType::Num)? atof(curString.c_str()) : 0; }
};

class ModalWindow : public Window {
    EventManager *eventManager;
    plugin::Interface *object;

    plugin::Array<const char*> paramNames;
    plugin::Array<  double   >   params  ;
    

    public:
        ModalWindow(plugin::Interface *object, sf::Texture *texture,
                    const signed texW = WINDOW_WIDTH, const signed texH = WINDOW_HEIGHT, sf::Sprite *sprite = new sf::Sprite):
        Window(Vect(0, 0), Vect(WINDOW_WIDTH, WINDOW_HEIGHT), texture, texW, texH, sprite),
        object (object),
        eventManager (nullptr)
        {}

        virtual int draw(RenderTarget *rt);

        void setParamNames(plugin::Array<const char *> paramNames);

        plugin::Array<double> getParams();

        uint8_t getPriority() { return HIGH_PRIORITY; }

        bool onKeyboardPress  (plugin::KeyboardContext context) override;
        bool onKeyboardRelease(plugin::KeyboardContext context) override;

        plugin::Interface *getInterface() { return object; }

        EventManager* getEventManager() { return eventManager; }
 
        void setEventManager(EventManager *eventManager) { this -> eventManager = eventManager; }
};

int modalWindowButton(Button *button);
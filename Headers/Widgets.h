#pragma once

#include <SFML/Graphics.hpp>
#include "Vect.h"
#include "List.h"

enum WidgetStatus {
    Disable = 0,
    Enable  = 1
};

enum ButtonStatus {
    Released = 0,
    Pointed  = 1,
    Pressed  = 2
};

class RenderTarget {
    sf::RenderWindow *window;

    public:
        RenderTarget(sf::RenderWindow *window):
                               window (window)
        {}

        sf::RenderWindow *getWindow() { return window; }
};

class Widget {
    Vect position;
    Vect   size  ;

    sf::Sprite  *sprite;
    sf::Texture *texture;

    WidgetStatus  status;

    public:
        Widget(Vect &pos, Vect &size, sf::Texture *texture, sf::Sprite *sprite):
           position (pos),
                          size (size),
                                          texture (texture),
                                                                sprite (sprite),
        status(Disable)
        {
            if (texture != nullptr) (this->sprite)->setTexture(*texture);
            if (sprite  != nullptr) (this->sprite)->setPosition(pos.x, pos.y); 
        }

        void turnOn() { this -> status = Enable; }

        sf::Sprite* getSprite() { return this -> sprite; }

        // virtual int  onMouseCLick  (double x, double y) = 0;
        // virtual int   onMouseMove  (double x, double y) = 0;
        // virtual int onMouseReleased(double x, double y) = 0;

        // virtual int onKeyPressed () = 0;
        // virtual int onKeyReleased() = 0;

        // virtual int addObject(Widget &object) = 0;

        virtual int draw(RenderTarget *rt) = 0;

        Vect   getSize  () { return this ->   size  ; }
        Vect getPosition() { return this -> position; }

        WidgetStatus getStatus() { return this -> status; }
};


class Window : public Widget {
    ListHead<Widget> *subWidgets;

    public:
        Window(Vect pos, Vect size, sf::Texture *texture, sf::Sprite *sprite):
        Widget(pos, size, texture, sprite),
        subWidgets (new ListHead<Widget>())
        {}

        int draw(RenderTarget *rt);

        ListHead<Widget> *getList() { return this -> subWidgets; }

};

class Button : public Widget {
    ButtonStatus buttonsStatus;

    sf::Text *text;
    sf::Font *font;

    public:
        Button(Vect pos, Vect size, const char *text, sf::Font *font, sf::Texture *texture, sf::Sprite *sprite);

        int onMouseClick();

        int draw(RenderTarget *rt);
};

class Menu : public Widget {
    ListHead<Widget> *buttons;

    public:
        Menu(Vect pos, Vect size):
        Widget(pos, size, nullptr, nullptr),
        buttons (new ListHead<Widget>())
        {}

        int draw(RenderTarget *rt);

        ListHead<Widget> *getList() { return this -> buttons; }

};
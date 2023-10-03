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

class Widget {
    Vect position;
    Vect   size  ;

    sf::Sprite *sprite;

    WidgetStatus  status;

    public:
        Widget(Vect &pos, Vect &size, sf::Sprite *sprite):
           position (pos),
                          size (size),
                                         sprite (texture),
        status(Disable)
        { this -> sprite.setPosition(pos.x, pos.y); }

        void turnOn() { this -> status = Enable; }

        sf::Sprite* getSprite() { return this -> sprite; }

        virtual int  onMouseCLick  (double x, double y) = 0;
        virtual int   onMouseMove  (double x, double y) = 0;
        virtual int onMouseReleased(double x, double y) = 0;

        virtual int onKeyPressed () = 0;
        virtual int onKeyReleased() = 0;

        virtual int addObject(Widget &object) = 0;

        virtual int draw(RenderTarget *rt) = 0;
};


class Window : public Widget {
    ListHead subWidgets;

    public:
        Window(Vect &pos, Vect &size):
        Widget(pos, size),
        subWidgets (ListHead())
        {}

        int draw(RenderTarget *rt);

        ListHead getList() { return this -> subWidgets; }

};

class Button : public Widget {
    ButtonStatus buttonsStatus;

    sf::Text text;

    public:
        Button(Vect &pos, Vect &size, const char *text, sf::Font *font);

        int onMouseClick();

        int draw(RenderTarget *rt);
};

class Menu : public Widget {
    ListHead buttons;

    public:
        Menu(Vect &pos, Vect &size):
        Widget(pos, size),
        buttons (ListHead())
        {}

        int draw(RenderTarget *rt);
};

class RenderTarget {
    sf::Texture texture;

    sf::RenderWindow *window;
};
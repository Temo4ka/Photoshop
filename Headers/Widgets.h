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

    WidgetStatus  status;

    public:
        Widget(Vect &pos, Vect &size):
           position (pos),
                          size (size),
        status(Disable)
        {}

        void turnOn() { this -> status = Enable; }

        virtual int  onMouseCLick  (double x, double y) = 0;
        virtual int   onMouseMove  (double x, double y) = 0;
        virtual int onMouseReleased(double x, double y) = 0;

        virtual int onKeyPressed () = 0;
        virtual int onKeyReleased() = 0;

        virtual int addObject(Widget &object) = 0;
};


class Window : public Widget {
    ListHead subWidgets;

    public:
        Window(Vect &pos, Vect &size):
        Widget(pos, size),
        subWidgets (ListHead())
        {}


};

class Button : public Widget {
    ButtonStatus buttonsStatus;

    public:
        Button(Vect &pos, Vect &size):
        Widget(pos, size),
        {}
};

class Menu : public Widget {
    ListHead buttons;

    public:
        Window(Vect &pos, Vect &size):
        Widget(pos, size),
        buttons (ListHead())
        {}
};

class RenderTarget {
    sf::Texture texture;

    sf::RenderWindow *window;
};
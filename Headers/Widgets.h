#pragma once

#include <SFML/Graphics.hpp>
#include "Vect.h"
#include <list>

enum Status {
    Disable = 0,
    Enable  = 1
};

class Widget {
    Vect position;
    Vect   size  ;

    bool  status ;

    public:
        Widget(Vect &pos, Vect &size):
           position (pos),
                          size (size),
        status(Disable)
        {}

        void turnOn() { this -> status = Enable; }
};


class Window : public Widget {
    std::list <Widget> subWidgets;

    public:
        Window(Vect &pos, Vect &size, list <Widget> &subWidgets):


}
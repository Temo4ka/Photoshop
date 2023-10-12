#pragma once

#include <SFML/Graphics.hpp>
#include "../Headers/Config.h"
#include "Vect.h"
#include "List.h"

enum WidgetStatus {
    Disable = 0,
    Enable  = 1
};

<<<<<<< HEAD
class RenderTarget {
    sf::RenderWindow *window;

    public:
        RenderTarget(sf::RenderWindow *window):
                               window (window)
        {}

        sf::RenderWindow *getWindow() { return window; }
=======
enum ButtonStatus {
    Released = 0,
    Pointed  = 1,
    Pressed  = 2
>>>>>>> parent of 03800ab (MainScreen added)
};

class Widget {
    Widget *parent;

    ListHead<Widget> *subWidgets;

    Vect position;
    Vect   size  ;

    sf::Sprite *sprite;

    WidgetStatus  status;

    public:
<<<<<<< HEAD
        Widget(Vect &pos, Vect &size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite, Widget *parent = nullptr):
           position (pos),
                          size (size),
                                          texture (texture),
                                                                sprite (sprite),
                                                                                parent (parent),
        subWidgets (new ListHead<Widget>()),
        status(Disable)
        {
            if (texture != nullptr) (this->sprite)->setTexture(*texture);
            if (sprite  != nullptr) (this->sprite)->setPosition(pos.x, pos.y); 
            if (sprite  != nullptr) (this->sprite)->setTextureRect(sf::IntRect(0, 0, texW, texH));
            // FILE *logFile = fopen("logFile.txt", "a");
            // fprintf(logFile, "%s -> %lg <-> %lg\n",  __PRETTY_FUNCTION__, size.x / double(texW), size.y / double(texH));
            // fclose(logFile);
            if (sprite  != nullptr) (this->sprite)->setScale(size.x / double(texW), size.y / double(texH));
        }
=======
        Widget(Vect &pos, Vect &size, sf::Sprite *sprite):
           position (pos),
                          size (size),
                                         sprite (texture),
        status(Disable)
        { this -> sprite.setPosition(pos.x, pos.y); }
>>>>>>> parent of 03800ab (MainScreen added)

        void changeStatus() { this -> status = (this -> status == Enable)? Disable : Enable; }

        sf::Sprite* getSprite() { return this -> sprite; }

<<<<<<< HEAD
        virtual int   onMouseMove  (Vect &pos) = 0;
        virtual int  onMouseClick  (Vect &pos) = 0;
        virtual int onMouseReleased(Vect &pos) = 0;
=======
        virtual int  onMouseCLick  (double x, double y) = 0;
        virtual int   onMouseMove  (double x, double y) = 0;
        virtual int onMouseReleased(double x, double y) = 0;
>>>>>>> parent of 03800ab (MainScreen added)

        virtual int onKeyPressed () = 0;
        virtual int onKeyReleased() = 0;

        virtual int addObject(Widget &object) = 0;

        virtual int draw(RenderTarget *rt) = 0;
<<<<<<< HEAD

        Vect   getSize  () { return this ->   size  ; }
        Vect getPosition() { return this -> position; }

        WidgetStatus getStatus() { return this -> status; }

        ListHead<Widget> *getList() { return this -> subWidgets; }
=======
>>>>>>> parent of 03800ab (MainScreen added)
};


class Window : public Widget {
<<<<<<< HEAD

    public:
        Window(Vect pos, Vect size, sf::Texture *texture, sf::Sprite *sprite):
        Widget(pos, size, texture, TEST_PIC_WIDTH, TEST_PIC_HEIGHT, sprite)
=======
    ListHead subWidgets;

    public:
        Window(Vect &pos, Vect &size):
        Widget(pos, size),
        subWidgets (ListHead())
>>>>>>> parent of 03800ab (MainScreen added)
        {}

        int draw(RenderTarget *rt);

<<<<<<< HEAD
        int  addChild  (Widget *widget);
=======
        ListHead getList() { return this -> subWidgets; }
>>>>>>> parent of 03800ab (MainScreen added)

        int removeChild(Widget *widget);

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);
};


<<<<<<< HEAD
class Button : public Widget {
    sf::Text *text;
    sf::Font *font;

    int (*run)(Button *button);
=======
    sf::Text text;

    public:
        Button(Vect &pos, Vect &size, const char *text, sf::Font *font);
>>>>>>> parent of 03800ab (MainScreen added)

    public:
        enum Status {
            Pressed  = 0,
            Released = 1,
            Pointed  = 2
        } status;

        Button(Vect pos, Vect size, const char *text, sf::Font *font, sf::Texture *texture, sf::Sprite *sprite, int (*run)(Button *Button) = nullptr);

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);

        int draw(RenderTarget *rt);
};

class Menu : public Widget {
    ListHead buttons;

    public:
<<<<<<< HEAD
        Menu(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr),
        buttons (new ListHead<Widget>())
=======
        Menu(Vect &pos, Vect &size):
        Widget(pos, size),
        buttons (ListHead())
>>>>>>> parent of 03800ab (MainScreen added)
        {}

        int draw(RenderTarget *rt);
};

<<<<<<< HEAD
        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);

        ListHead<Widget> *getList() { return this -> buttons; }

};

#include "./Tool.h"

class Canvas: public Widget {
    sf::RenderTexture *texture;

    TMan tm;

    sf::Color color;

    public:
        enum Tool {
            None   = 0,
            Pen    = 1,
            Brush  = 2,
            Rubber = 3,
        } tool;

        enum Status {
            Released = 0,
              Hold   = 1,
        } status;

        Canvas(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr),
        tool(None),
        status(Released),
        color(sf::Color::Blue),
        texture (new sf::RenderTexture)
        { 
            texture->create(size.x, size.y);
            tm.t = new B;
        }

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);

        int draw(RenderTarget *rt);

        void setColor(sf::Color newColor) { this -> color = newColor; }
};

int addWidget(Window *parent, Widget *child);

int removeWidget(Window *parent, Widget *child);
=======
class RenderTarget {
    sf::Texture texture;

    sf::RenderWindow *window;
};
>>>>>>> parent of 03800ab (MainScreen added)

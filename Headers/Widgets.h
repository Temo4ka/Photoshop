#pragma once

#include <SFML/Graphics.hpp>
#include "ClippingRegion.h"
#include "../Headers/Config.h"
#include "Vect.h"
#include "List.h"

enum WidgetStatus {
    Disable = 0,
    Enable  = 1
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
    Widget *parent;

    ListHead<Widget> *subWidgets;

    RegionSet *set;

    Vect position;
    Vect   size  ;

    sf::Sprite  *sprite;
    sf::Texture *texture;

    WidgetStatus  status;

    public:
        Widget(Vect &pos, Vect &size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite, Widget *parent = nullptr):
           position (pos),
                          size (size),
                                          texture (texture),
                                                                sprite (sprite),
                                                                                parent (parent),
        subWidgets (new ListHead<Widget>()),
        status(Disable)
        {
            set = new RegionsSet();
            set -> addRegion(new Region(pos, size));
            if (texture != nullptr) (this->sprite)->setTexture(*texture);
            if (sprite  != nullptr) (this->sprite)->setPosition(pos.x, pos.y); 
            if (sprite  != nullptr) (this->sprite)->setTextureRect(sf::IntRect(0, 0, texW, texH));
            // FILE *logFile = fopen("logFile.txt", "a");
            // fprintf(logFile, "%s -> %lg <-> %lg\n",  __PRETTY_FUNCTION__, size.x / double(texW), size.y / double(texH));
            // fclose(logFile);
            if (sprite  != nullptr) (this->sprite)->setScale(size.x / double(texW), size.y / double(texH));
        }

        void changeStatus() { this -> status = (this -> status == Enable)? Disable : Enable; }

        sf::Sprite* getSprite() { return this -> sprite; }

        virtual int   onMouseMove  (Vect &pos) = 0;
        virtual int  onMouseClick  (Vect &pos) = 0;
        virtual int onMouseReleased(Vect &pos) = 0;

        int  addSubWidget  (Widget *widget);
        int removeSubWidget(Widget *widget);

        int clipRegions();

        // virtual int onKeyPressed () = 0;
        // virtual int onKeyReleased() = 0;

        // virtual int addObject(Widget &object) = 0;

        virtual int draw(RenderTarget *rt) = 0;

        Vect   getSize  () { return this ->   size  ; }
        Vect getPosition() { return this -> position; }

        WidgetStatus getStatus() { return this -> status; }

        ListHead<Widget> *getList() { return this -> subWidgets; }

        RegionSet *getRegionSet() { return set; }
};


class Window : public Widget {

    public:
        Window(Vect pos, Vect size, sf::Texture *texture, sf::Sprite *sprite):
        Widget(pos, size, texture, TEST_PIC_WIDTH, TEST_PIC_HEIGHT, sprite)
        {}

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);
};


class Button : public Widget {
    sf::Text *text;
    sf::Font *font;

    int (*run)(Button *button);

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
    ListHead<Widget> *buttons;

    public:
        Menu(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr),
        buttons (new ListHead<Widget>())
        {}

        int draw(RenderTarget *rt);

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

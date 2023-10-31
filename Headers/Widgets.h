#pragma once

#include <SFML/Graphics.hpp>
#include "ClippingRegion.h"
#include "../Headers/Config.h"
#include "Vect.h"
#include "List.h"
#include "Events.h"

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

class Widget : public EventProcessible {
    Widget *parent;

    ListHead<Widget> *subWidgets;

    RegionSet *set;

    Vect position;
    Vect   size  ;
    Vect  scale  ;

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
        set (new RegionSet()),
        scale(Vect(size.x / double(texW), size.y / double(texH))),
        status(Disable),
        EventProcessible(1)
        {
            set -> addRegion(new Region(pos, size));
            if (texture != nullptr) (this->sprite)->setTexture(*texture);
            if (sprite  != nullptr) (this->sprite)->setPosition(pos.x, pos.y); 
            if (sprite  != nullptr) (this->sprite)->setTextureRect(sf::IntRect(0, 0, texW, texH));
            if (sprite  != nullptr) (this->sprite)->setScale(scale.x, scale.y);
            // FILE *logFile = fopen("logFile.txt", "a");
            // fprintf(logFile, "%s -> %lg <-> %lg\n",  __PRETTY_FUNCTION__, size.x / double(texW), size.y / double(texH));
            // fclose(logFile);
        }

        void changeStatus() { this -> status = (this -> status == Enable)? Disable : Enable; }

        sf::Sprite* getSprite() { return this -> sprite; }

        virtual int   onMouseMove  (Vect &pos) = 0;
        virtual int  onMouseClick  (Vect &pos) = 0;
        virtual int onMouseReleased(Vect &pos) = 0;

        int  addSubWidget  (Widget *widget);
        int removeSubWidget(Widget *widget);

        virtual int clipRegions();

        // virtual int onKeyPressed () = 0;
        // virtual int onKeyReleased() = 0;

        // virtual int addObject(Widget &object) = 0;

        virtual int draw(RenderTarget *rt) = 0;

        Vect   getSize  () { return this ->   size  ; }
        Vect getPosition() { return this -> position; }
        Vect   getScale () { return this ->   scale ; }

        WidgetStatus getStatus() { return this -> status; }

        ListHead<Widget> *getList() { return this -> subWidgets; }

        RegionSet *getRegionSet() { return set; }

        virtual void dumpRegions(sf::RenderWindow *window);

        void setRegionSet(RegionSet *newSet) { set = newSet; }

        void setPosition(Vect pos) { position = pos; }

        bool  isInWidgetArea (Vect point);
        bool isInWidgetRegion(Vect point);

        ~Widget() { delete sprite; }
};


class Window : public Widget {
    enum Status {
            Still      = 0,
            OnMove     = 1,
         OnResizeLeft  = 2,
         OnResizeRight = 4,
        OnResizeBottom = 8,
    } status;

    Vect lastPoint;

    public:
        Window(Vect pos, Vect size, sf::Texture *texture, sf::Sprite *sprite):
        Widget(pos, size, texture, TEST_PIC_WIDTH, TEST_PIC_HEIGHT, sprite),
        status(Status::Still),
        lastPoint(Vect(0, 0))
        {}

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);
        // Status getStatus() { return status; }
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

        void dumpRegions(sf::RenderWindow *window);

        int clipRegions();
};

class Menu : public Widget {
    public:
        Menu(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr)
        {}

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);
};

#include "./Tool.h"

class Canvas: public Widget {
    sf::RenderTexture *texture;
    sf::RenderTexture *  temp ;

    ToolManager toolManager;

    public:
        enum Status {
            Released = 0,
              Hold   = 1,
        } status;

        Canvas(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr),
        status(Released),
        texture (new sf::RenderTexture),
          temp  (new sf::RenderTexture)
        { 
            texture->create(size.x, size.y);
            texture->clear(sf::Color::White);
            toolManager.tool = new Circle;
        }

        int   onMouseMove  (Vect &pos);
        int  onMouseClick  (Vect &pos);
        int onMouseReleased(Vect &pos);

        int draw(RenderTarget *rt);

        void setColor(sf::Color newColor) { toolManager.color = newColor; }

        void setTool(Tool *tool) { 
            delete toolManager.tool;
            toolManager.tool = tool;
        }
};
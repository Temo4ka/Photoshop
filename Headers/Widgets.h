#pragma once

#include <SFML/Graphics.hpp>
#include "plugin.h"
#include "RenderTarget.h"
#include "ClippingRegion.h"
#include "../Headers/Config.h"
#include "Vect.h"
#include "List.h"
#include "Events.h"

enum WidgetStatus {
    Disable = 0,
    Enable  = 1
};

class Widget : public EventProcessible, plugin::WidgetI {
    plugin::WidgetI *parent;

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
        EventProcessible(BASE_PRIORITY)
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
        virtual int  onMousePress  (Vect &pos) = 0;
        virtual int onMouseRelease (Vect &pos) = 0;

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

        void move(Vect delta) { position += delta; }

        ~Widget() { delete sprite; }

    /*------------------------------for plugins-----------------------------------*/

    void registerSubWidget  (plugin::WidgetI* object);
    void unregisterSubWidget(plugin::WidgetI* object);

    plugin::Vec2 getSize() { return plugin::Vec2(size.x, size.y); }
    plugin::Vec2 getPos() { return plugin::Vec2(pos.x, pos.y); }


    void setSize(plugin::Vec2 size) { size = Vect(size.x, size.y); }
    void setPos (plugin::Vec2 pos)  { pos  = Vect(size.x, size.y); }

    bool isExtern() { return false; }

    void setParent(WidgetI *root) { parent = root; }

    WidgetI *getParent() { return root;}

    void move(Vec2 shift) { move(Vect(shift.x, shift.y)); }

    bool getAvailable() { return (status == Enable)? true : false};

    void setAvailable(bool newStatus) { status = (newStatus)? Enable: Disable; }

    void render(RenderTargetI* rti) { draw((RenderTarget *) rt) }                               //CRINGE!!!
    void recalcRegion() { clipRegions(); }

    ~WidgetI() { ~Widget() };

    /*----------------------------------------------------------------------------*/

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

        Window(Vect pos, Vect size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite):
        Widget(pos, size, texture, texW, texH, sprite),
        status(Status::Still),
        lastPoint(Vect(0, 0))
        {}

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease(Vect &pos);
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
        int  onMousePress  (Vect &pos);
        int onMouseRelease(Vect &pos);

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
        int  onMousePress  (Vect &pos);
        int onMouseRelease(Vect &pos);
};

#include "./Tool.h"
#include "./Filter.h"

class Canvas: public Widget {
    sf::RenderTexture *texture;
    sf::RenderTexture *  temp ;

     ToolManager  *  toolManager;
    FilterManager *filterManager;

    public:
        enum Status {
            Released = 0,
              Hold   = 1,
        } status;

        Canvas(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr),
        status(Released),
           texture   (new sf::RenderTexture),
            temp     (new sf::RenderTexture),
         toolManager (new ToolManager),
        filterManager(new FilterManager)
        { 
            texture->create(size.x, size.y);
            texture->clear(sf::Color::White);
            toolManager -> tool = new Circle;

            filterManager -> lastFilter = new ReverseFilter;
        }

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease(Vect &pos);

        int draw(RenderTarget *rt);

        void setColor(sf::Color newColor) { toolManager -> color = newColor; }

        void setTool(Tool *tool) { 
            delete toolManager -> tool;
            toolManager -> tool = tool;
        }

        void setFilter(Filter *filter) { 
            delete filterManager -> lastFilter;

            filterManager -> lastFilter = filter;
            filterManager ->   active   = true;
        }

        void activateFilter() { filterManager -> active = true; }
};

struct KeyBoard {
    enum Key {
    Unknown = -1 ,
    A , B , C ,
    D , E , F , G ,
    H , I , J , K ,
    L , M , N , O ,
    P , Q , R , S ,
    T , U , V , W ,
    X , Y , Z , Num0 ,
    Num1 , Num2 , Num3 , Num4 ,
    Num5 , Num6 , Num7 , Num8 ,
    Num9 , Escape , LControl , LShift ,
    LAlt , LSystem , RControl , RShift ,
    RAlt , RSystem , Menu , LBracket ,
    RBracket , Semicolon , Comma , Period ,
    Apostrophe , Slash , Backslash , Grave ,
    Equal , Hyphen , Space , Enter ,
    Backspace , Tab , PageUp , PageDown ,
    End , Home , Insert , Delete ,
    Add , Subtract , Multiply , Divide ,
    Left , Right , Up , Down ,
    Numpad0 , Numpad1 , Numpad2 , Numpad3 ,
    Numpad4 , Numpad5 , Numpad6 , Numpad7 ,
    Numpad8 , Numpad9 , F1 , F2 ,
    F3 , F4 , F5 , F6 ,
    F7 , F8 , F9 , F10 ,
    F11 , F12 , F13 , F14 ,
    F15
    } key;
};

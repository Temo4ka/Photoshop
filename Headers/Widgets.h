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

class Widget : public plugin::WidgetI, public plugin::EventProcessableI {
    plugin::WidgetI *parent;
    Widget *root;

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
        status(Disable)
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

        int  pushBackSubWidget  (Widget *widget);
        int  pushFrontSubWidget (Widget *widget);
        int removeSubWidget(Widget *widget);

        virtual int clipRegions();

        // virtual int onKeyPressed () = 0;
        // virtual int onKeyReleased() = 0;

        // virtual int addObject(Widget &object) = 0;

        virtual int draw(RenderTarget *rt) = 0;

        Vect getSizeVect() { return this ->   size  ; }
        Vect getPosition() { return this -> position; }
        Vect   getScale () { return this ->   scale ; }

        WidgetStatus getStatus() { return this -> status; }

        ListHead<Widget> *getList() { return this -> subWidgets; }

        void clearList() { delete this -> subWidgets; this -> subWidgets = new ListHead<Widget>(); }

        RegionSet *getRegionSet() { return set; }

        virtual void dumpRegions(sf::RenderWindow *window);

        void setRegionSet(RegionSet *newSet) { set = newSet; }

        void setPosition(Vect pos ) {  position  = pos ; }
        void setSizeVect(Vect size) {
            this->scale.x = this->scale.x * size.x / this->size.x; 
            this->scale.y = this->scale.y * size.y / this->size.y; 
            this->size = size;
            sprite -> setScale(scale.x, scale.y);
        }

        bool  isInWidgetArea (Vect point);
        bool isInWidgetRegion(Vect point);

        virtual void move(Vect delta);

        void    setRoot(Widget *root) { this -> root = root; }
        Widget* getRoot(            ) {      return root;    }

        ~Widget() {
            delete sprite;
            delete texture;
            delete set;
        }

    /*------------------------------for plugins-----------------------------------*/

    bool onMouseMove    (plugin::MouseContext context);
    bool onMouseRelease (plugin::MouseContext context);
    bool onMousePress   (plugin::MouseContext context);

    virtual bool onKeyboardPress  (plugin::KeyboardContext context) { return false; }
    virtual bool onKeyboardRelease(plugin::KeyboardContext context) { return false; }

    virtual bool onClock(uint64_t delta) { return false; }

    virtual uint8_t getPriority() { return LOW_PRIORITY; }

    void registerSubWidget  (plugin::WidgetI* object);
    void unregisterSubWidget(plugin::WidgetI* object);

    plugin::Vec2 getSize() { return plugin::Vec2(    size.x,     size.y); }
    plugin::Vec2 getPos () { return plugin::Vec2(position.x, position.y); }


    void setSize(plugin::Vec2 sz )  {   size   = Vect( sz.x,  sz.y); }
    void setPos (plugin::Vec2 pos)  { position = Vect(pos.x, pos.y); }

    bool isExtern() { return false; }

    void setParent(WidgetI *root) { parent = root; }

    WidgetI *getParent() { return parent;}

    void move(Vec2 shift) { move(Vect(shift.x, shift.y)); }

    bool getAvailable() { return (status == Enable)? true : false; }

    void setAvailable(bool newStatus) { status = (newStatus)? Enable: Disable; }

    virtual void render(plugin::RenderTargetI* rti) {
        MSG("You cannot use render(plugin::RenderTargetI *) for App Widgets :_(\n Use draw(RenderTarget*) instead!\n");
    }        

    virtual void recalcRegion() { clipRegions(); }

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
        Window(Vect pos, Vect size, sf::Texture *texture, sf::Sprite *sprite);

        Window(Vect pos, Vect size, sf::Texture *texture, const signed texW, const signed texH, sf::Sprite *sprite):
        Widget(pos, size, texture, texW, texH, sprite),
        status(Status::Still),
        lastPoint(Vect(0, 0))
        {}

        virtual int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease (Vect &pos);
        // Status getStatus() { return status; }
};


class Button : public Widget {
    EventManager *eventManager;

    sf::Text *text;
    sf::Font *font;

    int (*run)(Button *button);

    unsigned CharacterSize = 15;

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

        void move(Vect delta) override;

        void dumpRegions(sf::RenderWindow *window);

        void setEventManager(EventManager *eventMgr) { eventManager = eventMgr; }

        EventManager* getEventManager() { return eventManager; }

        void setCharacterSize(unsigned size) { CharacterSize = size; }

        sf::Text *getText() { return text; }

        int clipRegions();
};

struct HostApp;

class PluginButton : public Button {
    plugin::Plugin *buttPlugin;

    HostApp *app;

    public:
        PluginButton(plugin::Plugin *buttPlugin,
                    Vect pos, Vect size, const char *text, sf::Font *font, sf::Texture *texture, sf::Sprite *sprite, int (*run)(Button *Button) = nullptr):
             Button(     pos,      size,             text,           font,              texture,             sprite,       run),
            buttPlugin (buttPlugin),
            app( nullptr  )
        {}

        plugin::Plugin *getPlugin() { return buttPlugin; }

        void setApp(HostApp *app) { this -> app = app; }

        HostApp* getApp() { return app; }
};

class Menu : public Widget {
    public:
        Menu(Vect pos, Vect size):
        Widget(pos, size, nullptr, 0, 0, nullptr)
        {}

        int draw(RenderTarget *rt);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease (Vect &pos);
};

#include "./Tool.h"
#include "./Filter.h"

class Canvas: public Widget {
    RenderTarget *texture;
    RenderTarget *  temp ;

    HostApp *app;

    public:
        enum Status {
            Released = 0,
              Hold   = 1,
        } status;

        Canvas(Vect pos, Vect size, HostApp *app);

        int   onMouseMove  (Vect &pos);
        int  onMousePress  (Vect &pos);
        int onMouseRelease (Vect &pos);

        int draw(RenderTarget *rt);

        void setColor(sf::Color newColor);

        void setTool(ToolI *tool);

        void activateFilter();

        void setFilter(plugin::FilterI *filter);

        void paint(sf::Sprite *sprite) { texture -> paint(sprite);}

        Texture *getImage() { return texture->getTexture(); }
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

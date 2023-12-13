#pragma once

#include <cinttypes>
#include <algorithm>

/*
    Запрещаем плагину иметь свои Widget и RenderTargetI

    для виджетов есть createWidget
    для RenderTargetI есть угол чтобы поплакать
*/

namespace plugin {
    enum class InterfaceType {
        Tool,
        Filter,
        System // системный плагин, мб обертка
    };

/// @warning [UPD] Array владеющая структура
    template<class T>
    struct Array {
        uint64_t size;
        T* data;

        Array(uint64_t _size, T* _data): size(_size), data(new T[_size]) {
            std::copy(_data, _data + _size, data);
        }

        Array(const Array<T>& other): Array(other.size, other.data) {}

        Array() {
            size = 0;
            data = nullptr;
        }
        
        Array& operator=(const Array<T>& other) {
            size = other.size;
            delete data;
            data = new T[other.size];
            std::copy(other.data, other.data + other.size, data);

	    return *this;
        }

        Array(Array<T>&& other) {
            std::swap(size, other.size);
            std::swap(data, other.data);
        }

        Array& operator=(Array<T>&& other) {
            std::swap(size, other.size);
            std::swap(data, other.data);

	    return *this;
        }

        ~Array() {
            delete[] data;
        }
    };

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
                   r (r),
                              g (g),
                                         b (b),
                                                    a (a)
        {}
    };

    struct Texture {
        uint64_t height;
        uint64_t width;

        Color *pixels;

        virtual ~Texture() {
		delete[] pixels;
	};
    };

    struct Vec2 {
        double x;
        double y;
    
        Vec2(double x, double y):
                 x (x),
                           y (y)
        {}
    };

    enum class MouseButton {
        Left,
        Right,
        Unknown
    };

    /// @note см про относительность координат
    struct MouseContext {
        Vec2 position;
        MouseButton button;

        MouseContext(Vec2 pos, MouseButton button):
                position (pos),
                                    button(button)
        {}
    };

    enum class Key {
        Unknown = -1, 
        A = 0,        
        B,            
        C,            
        D,            
        E,            
        F,            
        G,            
        H,            
        I,            
        J,            
        K,            
        L,            
        M,            
        N,            
        O,            
        P,            
        Q,            
        R,            
        S,            
        T,            
        U,            
        V,            
        W,            
        X,            
        Y,            
        Z,            
        Num0,         
        Num1,         
        Num2,         
        Num3,         
        Num4,         
        Num5,         
        Num6,         
        Num7,         
        Num8,         
        Num9,         
        Escape,       
        LControl,     
        LShift,       
        LAlt,         
        LSystem,      
        RControl,     
        RShift,       
        RAlt,         
        RSystem,      
        Menu,         
        LBracket,     
        RBracket,     
        Semicolon,    
        Comma,        
        Period,       
        Apostrophe,   
        Slash,        
        Backslash,    
        Grave,        
        Equal,        
        Hyphen,       
        Space,        
        Enter,        
        Backspace,    
        Tab,          
        PageUp,       
        PageDown,     
        End,          
        Home,         
        Insert,       
        Delete,       
        Add,          
        Subtract,     
        Multiply,     
        Divide,       
        Left,         
        Right,        
        Up,           
        Down,         
        Numpad0,      
        Numpad1,      
        Numpad2,      
        Numpad3,      
        Numpad4,      
        Numpad5,      
        Numpad6,      
        Numpad7,      
        Numpad8,      
        Numpad9,      
        F1,           
        F2,           
        F3,           
        F4,           
        F5,           
        F6,           
        F7,           
        F8,           
        F9,           
        F10,          
        F11,          
        F12,          
        F13,          
        F14,          
        F15,          
        Pause,        
        
        KeyCount,     
    };

    struct KeyboardContext {
        bool alt;
        bool shift;
        bool ctrl;

        Key key;
    };

    struct RenderTargetI {
        /**
         * point -- левый верхний угол
         * size  -- размер ограничивающего прямоугольника
         * */

        virtual void setPixel(Vec2 pos, Color color) = 0;
        virtual void drawLine(Vec2 point1, Vec2 point2, Color color) = 0;
        virtual void drawRect(Vec2 pos, Vec2 size, Color color) = 0;
        virtual void drawEllipse(Vec2 pos, Vec2 size, Color color) = 0;
        virtual void drawTexture(Vec2 pos, Vec2 size, const Texture *texture) = 0;
        virtual void drawText(Vec2 pos, const char *content, uint16_t char_size, Color color) = 0;

        // Возвращает аллоцированную структуру типа Texture* 
        virtual Texture *getTexture() = 0;
        virtual void setTexture(Texture *) = 0;

        /// как в RenderTexture::display
        virtual void display() = 0;

        /// clear
        virtual void clear() = 0;
        virtual void clear(Color color) = 0;
    };

    struct RenderableI {
        virtual void render(RenderTargetI* texture) = 0;
        virtual ~RenderableI() = default;
    };

    struct Interface {
        virtual Array<const char *> getParamNames() = 0;
        
        // в том же порядке, что getParamNames 
        virtual Array<double> getParams() = 0;
        virtual void setParams(Array<double> params) = 0;

        virtual ~Interface() = default;
    };

    struct Plugin {
        /* где-то тут лежит App*, но это дело автора плагина */
        uint64_t id;
        const char *name;
        InterfaceType type;

        virtual Interface *getInterface() = 0;

        // плагин выбрали
        // [UPD]: только для системных
        virtual void selectPlugin() = 0;

        virtual ~Plugin() = default;
    };

    enum class EventType {
        MousePress,
        MouseRelease,
        MouseMove,
        KeyPress,
        KeyRelease,
	    Clock,
	    NumOfEvents
    };

    struct EventProcessableI {
        // MouseContext хранит в себе координаты относительно позиции RT из GuiI::getRenderTarget.
        // Мотивация: если RT это не весь экран, а RT в каком-то окне (как идейно и планировалось), то, 
        // строго говоря, плагин не знает где в реальном мире находится RT (его могли перетаскивать и проч)
        // и не может пересчитать их в локальные.
        
	    // true = перехватил, false = надо продолжать
        virtual bool onMouseMove(MouseContext context) = 0;
        virtual bool onMouseRelease(MouseContext context) = 0;
        virtual bool onMousePress(MouseContext context) = 0;
        virtual bool onKeyboardPress(KeyboardContext context) = 0;
        virtual bool onKeyboardRelease(KeyboardContext context) = 0;

        /// @brief clock event
        /// @param context microseconds
        virtual bool onClock(uint64_t delta) = 0;

	    virtual uint8_t getPriority() = 0;

        virtual ~EventProcessableI() = default;
    };

    struct EventManagerI {
        virtual void registerObject(EventProcessableI *object)   = 0;

        // 0 минимальный, ивенты приходят только объектам с их priority >= установленной по этому типу
        // 0 -- default
        virtual void setPriority(EventType, uint8_t priority)    = 0;
        virtual void unregisterObject(EventProcessableI *object) = 0;

        virtual ~EventManagerI() = default;
    };

    struct WidgetI {
        virtual void registerSubWidget(WidgetI* object) = 0;
        virtual void unregisterSubWidget(WidgetI* object) = 0;

        virtual Vec2 getSize() = 0;
        virtual void setSize(Vec2) = 0;

        virtual Vec2 getPos() = 0;
        virtual void setPos(Vec2) = 0;

        virtual WidgetI *getParent() = 0;
        virtual void setParent(WidgetI *root) = 0;

        virtual void move(Vec2 shift) = 0;

        // Жив ли виджет
        // Если true, то это идейно равносильно вызову деструктору, то есть его не надо рендерить, ему не надо передавать 
        // ивенты и тд и тп
        virtual bool getAvailable() = 0;
        virtual void setAvailable(bool) = 0;

        virtual ~WidgetI() = default;
    };

    struct PluginWidgetI: public EventProcessableI, public RenderableI {
        WidgetI* host;
    };

    struct ToolI: public Interface {
        virtual const Texture *getIcon() = 0;

        virtual void paintOnPress(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
        virtual void paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
        virtual void paintOnMove(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
        virtual void disable(RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;

        virtual ~ToolI() = default;
    };

    struct FilterI: public Interface {
        virtual void apply(RenderTargetI *data) = 0;

        virtual ~FilterI() = default;
    };

    struct GuiI {
        /**
         * @brief Get the root widget of widget tree
         * 
         * @return WidgetI* root
         */
        virtual WidgetI* getRoot() = 0;

        /**
         * @brief Create a host WidgetI from PluginWidgetI and set `host` field in widget
         */
        virtual void createWidgetI(PluginWidgetI* widget) = 0;

        // плагин через это у хоста запрашивает, есть ли плагин c таким id. nullptr если нет
        virtual Plugin *queryPlugin(uint64_t id) = 0;

        // принимает имя файла
        // например, если у хоста все asset'ы этого плагина валяются в assets/shit/<filename>, то 
        // сюда надо передавать только filename
        virtual Texture *loadTextureFromFile(const char *filename) = 0;

        virtual ~GuiI() = default;
    };

    struct App {
        GuiI *root;
        EventManagerI *event_manager;
    };
}

#define DllExport  extern "C" __declspec( dllexport )

DllExport plugin::Plugin* getInstance(plugin::App *app);
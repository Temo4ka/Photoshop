#pragma once
#include "Vect.h"
#include <SFML/Graphics.hpp>
#include "plugin.h"

using namespace plugin;

struct Tool : public ToolI {
    Array<const char *> paramNames;
    Array<   double   >   params  ;

    Vect startPoint;
    Vect lastPoint;

    enum Drawing {
        Disable = 0,
         Enable = 1
    } drawing;

    Tool():
    startPoint (Vect(-1, -1)),
    lastPoint  (Vect(-1, -1)),
    drawing    (  Disable   )
    {}

    const Texture *getIcon() { return nullptr; }

    virtual void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
    virtual void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
    virtual void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
    virtual void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;

    Array<const char *> getParamNames()  { return paramNames; }
    Array<  double    >    getParams()   { return   params  ; }

    void setParams(Array<double> params) { this -> params = params; }
};


struct ToolManager : public ToolManagerI {
    ToolI* tool;
    Color color;

    ToolManager ():
    tool(nullptr),
    color({0, 255, 0, 255})
    {}

    void  paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context);
    void  paintOnPress (RenderTargetI *data, RenderTargetI *tmp, MouseContext context);
    void paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context);
    void  disableTool  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context);

    void setColor(Color color) { this -> color = color; }
    void setTool (ToolI *tool) { this -> tool  = tool;  }

    ToolI *getTool()  { return tool; }
    Color  getColor() { return color; }
};
// struct Sl : public Tool {

//     void p(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void  onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
// }


struct Polyline : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Brush : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Pen : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

// struct F : public Tool {

//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void  onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
// }

struct Eraser : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Fill : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Square : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Circle : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Elipse : public Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void     disable    (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

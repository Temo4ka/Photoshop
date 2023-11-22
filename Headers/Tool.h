#pragma once
#include "Vect.h"
#include <SFML/Graphics.hpp>
#include "plugin.h"

using namespace plugin;

struct Tool;

struct ToolManager : ToolManagerI {
    Tool* tool;
    Color color;

    ToolManager ():
    tool(nullptr),
    color(Color(0, 255, 0, 255))
    {}

    void  paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context);
    void  paintOnPress (RenderTargetI *data, RenderTargetI *tmp, MouseContext context);
    void paintOnRelease(RenderTargetI *data, RenderTargetI *tmp, MouseContext context);
    //TODO: void  disableTool  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context);

    void setColor(Color color) { this -> color = color; }
    void setTool (ToolI *tool) { this -> tool  = (Tool *) tool; }

    ToolI *getTool()  { return tool; }
    Color  getColor() { return color; }
};

struct Tool : ToolI {
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

    virtual void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
    virtual void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;
    virtual void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color) = 0;

    Array<const char *> getParamNames()  { return paramNames; }
    Array<  double    >    getParams()   { return   params  ; }

    void setParams(Array<double> params) { this -> params = params; }
};

// struct Sl : Tool {

//     void p(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void  onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
// }


struct Polyline : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Brush : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Pen : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

// struct F : Tool {

//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void  onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
// }

struct Eraser : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Fill : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Square : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Circle : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

struct Elipse : Tool {
    void  paintOnPress  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void   paintOnMove  (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
    void paintOnRelease (RenderTargetI *data, RenderTargetI *tmp, MouseContext context, Color color);
};

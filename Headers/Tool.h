#pragma once
#include "Vect.h"
#include <SFML/Graphics.hpp>

struct Tool;

struct ToolManager {
    Tool* tool;
    sf::Color color;

    ToolManager ():
    tool(nullptr),
    color(sf::Color::Blue)
    {}

    void  onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPosurPosition);
    void   onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPosurPosition);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPosurPosition);
};

struct Tool {
    Vect startPoint;
    Vect lastPoint;

    enum Drawing {
        Disable = 0,
         Enable = 1
    } drawing;

    Tool():
    startPoint (Vect(-1, -1)),
    lastPoint  (Vect(-1, -1)),
    drawing (Disable)
    {}

    virtual void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color) = 0;
    virtual void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color) = 0;
    virtual void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color) = 0;
};

// struct Sl : Tool {

//     void p(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void  onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
// }


struct Polyline : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

struct Brush : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

struct Pen : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

// struct F : Tool {

//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void  onMouseMove  (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
//     void onMousePressed(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
// }

struct Eraser : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

struct Fill : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

struct Square : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

struct Circle : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};

struct Elipse : Tool {
    void onMousePressed (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void  onMouseMove   (sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
    void onMouseReleased(sf::RenderTexture *rt, sf::RenderTexture *temp, Vect curPos, sf::Color color);
};